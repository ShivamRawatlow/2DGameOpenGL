#pragma once

#include<tuple>
#include <iostream>
#include <vector>
 
#include <sstream>  // for string streams 
#include <string>  // for string 

#include <glew.h>
#include <glfw3.h>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "GameCharacter.h"
#include "Camera.h"




enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

//typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

//Direction VectorDirection(glm::vec2 target);

class Game
{
public:
	// Game state
	GameState  State;
	GLboolean  Keys[1024];
	GLuint	   Width, Height;
	GLuint spriteCounter;

	GLfloat xCamOffset;
	//GLfloat yCamOffset;


	GLboolean canJump;
	GLboolean canTouchDown;


	GLfloat Gravity;

	std::vector<GameLevel> Levels;
	GLuint Level;


	glm::vec2 mainCharacterPosition;
	
	const GLfloat CHARACTER_VELOCITY = 500.0f;

	Camera followCam;




	Game(GLuint width, GLuint height);
	~Game();


	GameCharacter* myPlayer = nullptr;
	GameLevel*  levelOne = nullptr;

	void Init();

	// GameLoop
	void ProcessInput();
	void Render();
	
	void CalculateDeltaTime();
	Direction CollisionDirection(glm::vec2 target);

	
	GLfloat jumpDecelerate;

	GLfloat deltaTime;
	GLfloat lastFrame;

	std::tuple<GLboolean, Direction> CheckLevelCollision();
	GLboolean CheckCollision(GameObject &obj1);
	//GLboolean CheckCollision(glm::vec2 one, glm::vec2 two);
	
};

