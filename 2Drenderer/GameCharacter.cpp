#include "GameCharacter.h"

GameCharacter::GameCharacter(glm::vec2 characterSize)
{
	size = characterSize;
	size.x /= 4;
	size.y /= 4;
	rotation = 0.0f;

	frameControl = 0.0f;
	spriteCounter = 1;
	jumpAcceleration = 1.0f;
	velocity = 0;

	canJump = true;
	inAir = true;

	characterState.ATTACK == false;
	characterState.IDLE == false;
	characterState.RUN == false;
	characterState.JUMP == false;
	characterDirection.RIGHT = true;
	characterDirection.LEFT = true;
}

void GameCharacter::run(GLfloat deltatime)
{
	position.x += velocity * deltatime;
}

void GameCharacter::attack()
{

}

void GameCharacter::jump(GLfloat deltatime, GLfloat gravity)
{
	if (jumpAcceleration > 0)
	{
		position.y -= jumpAcceleration;
		jumpAcceleration -= deltatime * gravity;
	}
}

void playRunAnimation()
{

}

void GameCharacter::LoadAnimationTexture(std::string textureLocation, std::string tagname, GLuint noOfSprites)
{
	std::string Location = textureLocation;
	for (int i = 1; i <= noOfSprites; i++)
	{
		std::ostringstream stream;
		std::string Temp = Location;
		stream << i;
		std::string add = stream.str();
		Temp = Temp + add;

		Temp = Temp + std::string(".png");

		std::string spritename = tagname;
		spritename += add;
		
		
		if (textureLocation[9] == 'm')
		{
			std::cout << Temp << "\t" << spritename << "\t" << Temp.length() << std::endl;	
			ResourceManager::LoadMainCharacterTexture(Temp.c_str(), GL_TRUE, spritename);
		}

		else if(textureLocation[9] == 'e')
		{
			std::cout << Temp << "\t" << spritename << "\t" << Temp.length() << std::endl;

			
			ResourceManager::LoadEnemyCharacterTexture(Temp.c_str(), GL_TRUE, spritename);
		}
		else
		{
			std::cout << "Wrong animation name prameter";
		}
	}
} 

void GameCharacter::MakeCharacter(std::string texturename, GLfloat deltaTime, GLfloat frameControlLimit, GLuint spriteCount)
{
	std::ostringstream stream;
	stream << spriteCounter;
	std::string add = stream.str();
	frameControl = frameControl + deltaTime;

	std::string spriteAction = texturename;
	spriteAction += add;

	//std::cout << texturename<<std::endl;
	if (texturename[0] == 'e')//if enemy
	{
		//std::cout << "Executig" << std::endl;
		this->DrawAnimation(ResourceManager::EnemyCharacterTextures[spriteAction], this->position, this->size, this->rotation);
	}
	if (texturename[0] == 'c')//if main character
	{
		//std::cout << "Executig" << std::endl;
		//std::cout << size.x << size.y<<std::endl;
		this->DrawAnimation(ResourceManager::MainCharacterTextures[spriteAction], this->position, this->size, this->rotation);
	}
			
	if (frameControl > frameControlLimit)
	{
		spriteCounter++;
		frameControl = 0.0f;
	}

	if (spriteCounter > spriteCount)
	{
		spriteCounter = 1;
	}
}