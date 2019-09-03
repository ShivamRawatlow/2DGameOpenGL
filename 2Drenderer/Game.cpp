#include "Game.h"

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{	
	spriteCounter = 1;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	Level = 1;
	
	Gravity = 150.0f;
	
	canJump = true;

	canTouchDown = true;

	xCamOffset = 0.0f;
	
	followCam.leftConstrain = 100.0f;
	followCam.rightConstrain = 500.0f;


	jumpDecelerate = 1.0f;	
	//Init();
}

Game::~Game()
{
	delete levelOne;
	delete myPlayer;
}

void Game::Init()
{
	/////////Loading Level///////////
	levelOne = new GameLevel();
	levelOne->width = 3100;
	levelOne->height = this->Height;
	levelOne->Load("Levels/A few small gaps.txt");

	ResourceManager::LoadShader("Shaders/Level_V.glsl", "Shaders/Level_F.glsl", nullptr, "level");

	ResourceManager::GetShader("level").Use();

	ResourceManager::LoadTexture("Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("Textures/block.png", GL_FALSE, "block_solid");


	//// Load shaders
	ResourceManager::LoadShader("Shaders/Character_V.glsl", "Shaders/Character_F.glsl", nullptr, "character");
	//// Configure shaders
	ResourceManager::GetShader("character").Use();

	myPlayer = new GameCharacter(glm::vec2(800, 560));
	//enemy = new GameCharacter(glm::vec2(800, 560));

	myPlayer->rotation = 0.0f;
	myPlayer->position = glm::vec2(1, -300);

	//enemy->position = glm::vec2(1, 50);
	
	//enemy walk
	//enemy->LoadAnimationTexture("Textures/enemyCharacter/walk/w", "enemyWalkSprite_", 4);

	//enemy idle
	//enemy->LoadAnimationTexture("Textures/enemyCharacter/idle/i", "enemyIdleSprite_", 1);

	//runnig sprite
	myPlayer->LoadAnimationTexture("Textures/mainCharacter/run/k", "characterRunSprite_", 8);

	//attack sprite
	myPlayer->LoadAnimationTexture("Textures/mainCharacter/attack/a", "characterAttackSprite_", 13);

	//idle sprite
	myPlayer->LoadAnimationTexture("Textures/mainCharacter/idle/i", "characterIdleSprite_", 2);

	//idle sprite
	myPlayer->LoadAnimationTexture("Textures/mainCharacter/jump/j", "characterJumpSprite_", 1);

}

void Game::ProcessInput()
{

	int delay = 0;
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = CHARACTER_VELOCITY * deltaTime;

		if (this->Keys[GLFW_KEY_D] && myPlayer->characterDirection.RIGHT)
		{
			std::tuple<GLboolean, Direction> result = CheckLevelCollision();
			GLboolean collisionResult = std::get<0>(result);
			Direction directionResult = std::get<1>(result);

				if (collisionResult)
				{
					if (directionResult == Direction::RIGHT)
					{
						std::cout << "\t\t\t\tRight stop" << std::endl;
						myPlayer->characterDirection.RIGHT = false;
						return;
					}
				}
			

			if (myPlayer->position.x >= followCam.rightConstrain)
			{
				followCam.leftConstrain += velocity;
				followCam.rightConstrain += velocity;

				followCam.xOffset += velocity;
			}

			myPlayer->rotation = 0;
			myPlayer->position.x += velocity;
			myPlayer->characterState.RUN = true;
			
		}
/////////////////////

		if (this->Keys[GLFW_KEY_A] && myPlayer->characterDirection.LEFT)
		{
			std::tuple<GLboolean, Direction> result = CheckLevelCollision();
			GLboolean collisionResult = std::get<0>(result);
			Direction directionResult = std::get<1>(result);

			
				if (collisionResult)
				{
					//glm::vec2 difference = glm::vec2(glm::vec2(box.position.x - box.size.x, box.position.y) - myPlayer->position);
					if (directionResult == Direction::LEFT)
					{
						std::cout << "\t\tLeft stop" << std::endl;
						myPlayer->characterDirection.LEFT = false;
						return;
					}
				}
			
			if (myPlayer->position.x <= followCam.leftConstrain)
			{
				followCam.leftConstrain -= velocity;
				followCam.rightConstrain -= velocity;
				followCam.xOffset -= velocity;
			}

			myPlayer->rotation = glm::radians(180.0f);
			myPlayer->position.x -= velocity;
			myPlayer->characterState.RUN = true;
		}

///////////////////////

		if (this->Keys[GLFW_KEY_SPACE] && myPlayer->characterDirection.BOTTOM)
		{
			std::tuple<GLboolean, Direction> result = CheckLevelCollision();
			GLboolean collisionResult = std::get<0>(result);
			Direction directionResult = std::get<1>(result);
	
				if (collisionResult)
				{
					//glm::vec2 difference = glm::vec2(box.position.x, (box.position.y)) - myPlayer->position;

					if (directionResult == Direction::DOWN)
					{
						std::cout << "\t\t\t\t\t\tBottom stop" << std::endl;
						myPlayer->characterDirection.BOTTOM = false;
						return;
					}
				}
			
			if (myPlayer->canJump)
			{
				if (jumpDecelerate > 0.0)
				{
					myPlayer->position.y -= velocity * 3 * jumpDecelerate;
					jumpDecelerate -= 0.007;
				}
				else
				{
					Gravity = 150.0f;
					myPlayer->canJump = false;
				}
				myPlayer->characterState.JUMP = true;
			}
		}


		if (this->Keys[GLFW_KEY_F])
		{
			myPlayer->characterState.ATTACK = true;
		}

//////////////////////////////////

		if(!(this->Keys[GLFW_KEY_A]) && !(this->Keys[GLFW_KEY_D]))
		{
			myPlayer->characterState.RUN = false;
			myPlayer->characterDirection.RIGHT = true;
			myPlayer->characterDirection.LEFT = true;
			myPlayer->characterState.IDLE = true;			
		}
		if (!this->Keys[GLFW_KEY_SPACE])
		{
			myPlayer->characterDirection.BOTTOM = true;
			myPlayer->canJump = true;
			jumpDecelerate = 1.0f;
		}

		if (!this->Keys[GLFW_KEY_F])
		{
			myPlayer->characterState.ATTACK = false;
		}

	}
		
}

/////////////////////////////////Main Render////////////////////////////////////////////////////////

void Game::Render()
{
///draw level////////	

	glm::mat4 projection = glm::ortho(0.0f + followCam.xOffset, static_cast<GLfloat>(this->Width + followCam.xOffset), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("level").SetMatrix4("projection", projection);

	levelOne->Draw();


///draw character ////////////////////////


	// projection = glm::ortho(0.0f + followCam.xOffset, static_cast<GLfloat>(this->Width + followCam.xOffset), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("character").SetMatrix4("projection", projection);

	myPlayer->inAir = true;

	if (this->State == GAME_ACTIVE)
	{		
		std::tuple<GLboolean,Direction> result = CheckLevelCollision();
		GLboolean collisionResult = std::get<0>(result);
		Direction directionResult = std::get<1>(result);

		if(collisionResult == true)
		{
		
			if (directionResult == Direction::UP)//when character touches ground
			{
				myPlayer->inAir = false;
				myPlayer->characterState.JUMP = false;
				Gravity = 150.0f;
			}
		}
		
		if (myPlayer->inAir)
		{
			//std::cout << "Executing" << std::endl;
			myPlayer->position.y = (double)(myPlayer->position.y + Gravity * deltaTime);
			Gravity += 5.0f;
		}

		if (myPlayer->characterState.JUMP)
		{
			myPlayer->MakeCharacter("characterJumpSprite_", deltaTime, 0.08, 1);
			return;
		}
		if (myPlayer->characterState.ATTACK)
		{
			myPlayer->MakeCharacter("characterAttackSprite_", deltaTime, 0.08, 13);
			return;
		}
		if (myPlayer->characterState.RUN)
		{
			//std::cout <<"RunExecuting"<<std::endl;
			myPlayer->MakeCharacter("characterRunSprite_", deltaTime, 0.08, 8);
			return;
		}
		if (myPlayer->characterState.IDLE)
		{
			//std::cout << "IdleExecuting" << std::endl;
			myPlayer->MakeCharacter("characterIdleSprite_", deltaTime, 0.2, 2);
			return;
		}
		//enemy->MakeCharacter("enemyWalkSprite_", deltaTime, 0.2, 4);		
	}
}
/////////////////////////////////Main Render////////////////////////////////////////////////////////


void Game::CalculateDeltaTime()
{
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	glfwPollEvents();	
}


Direction Game::CollisionDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}



std::tuple<GLboolean, Direction> Game::CheckLevelCollision()
{
	GLfloat ignore = -70.0f;//because image size is bigger than the character size
	GLboolean collisionFlag = false;
	glm::vec2 collisionPosition;
	for(glm::vec2 position : ResourceManager::tilePositionsVector)
	{
		bool collisionX = myPlayer->position.x + myPlayer->size.x + ignore >= position.x &&
			position.x + ResourceManager::tileSize.x + ignore >= myPlayer->position.x;
		// Collision y-axis?
		bool collisionY = myPlayer->position.y + myPlayer->size.y >= position.y &&
			position.y + ResourceManager::tileSize.y >= myPlayer->position.y;
		// Collision only if on both axes
		if(collisionX == true && collisionY == true)
		{
			collisionFlag = true;
			collisionPosition = position;
			break;
		}

	}

	return { collisionFlag,CollisionDirection(collisionPosition - myPlayer->position) };
}


GLboolean Game::CheckCollision(GameObject& obj)
{
	GLfloat ignore = -70.0f;//because image size is bigger than the character size
	//ignore = 0.0f;
	// Collision x-axis?
	bool collisionX = myPlayer->position.x + myPlayer->size.x +ignore >= obj.position.x &&
		obj.position.x + obj.size.x + ignore >= myPlayer->position.x;
	// Collision y-axis?
	bool collisionY = myPlayer->position.y + myPlayer->size.y >= obj.position.y &&
		obj.position.y + obj.size.y >= myPlayer->position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

