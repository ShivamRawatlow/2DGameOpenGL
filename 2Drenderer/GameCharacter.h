#pragma once
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include <sstream>  // for string streams 
#include <string>  // for string 


class GameCharacter :
	public GameObject
{
	public:

		struct 
		{
			bool IDLE;
			bool RUN;
			bool JUMP;
			bool ATTACK;
		}characterState;
		struct
		{
			bool LEFT;
			bool RIGHT;
			bool BOTTOM;
		}characterDirection;

		bool canJump;
		bool inAir;
		bool onGround;
		
	GLfloat velocity;
	void LoadAnimationTexture(std::string textureLocation, std::string tagname, GLuint noOfSprites);
	void MakeCharacter(std::string texturename, GLfloat deltaTime, GLfloat frameControlLimit, GLuint spriteCount);

	GLfloat frameControl;
	GLint spriteCounter;
	GLfloat jumpAcceleration;

	GameCharacter(glm::vec2 characterSize);
	void run(GLfloat deltatime);
	void attack();
	void jump(GLfloat deltatime, GLfloat gravity);

};

