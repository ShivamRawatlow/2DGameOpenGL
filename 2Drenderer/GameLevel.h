#pragma once

#include <vector>
#include <fstream>
#include <sstream>


#include <glew.h>
#include <glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameLevel
{
public:

	GLuint height;
	GLuint width;
	GameObject Brick;
	// Constructor
	GameLevel();
	void Draw();
	void Load(const GLchar *file);
private:
	// Initialize level from tile data
	void  init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

