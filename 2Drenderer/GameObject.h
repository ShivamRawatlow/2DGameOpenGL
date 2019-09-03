#pragma once

#include <glew.h>
#include <glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameObject
{
public:
	// Object state
	glm::vec2   position, size;
	glm::vec3   color;
	GLfloat     rotation;
	GLboolean   isSolid;
	GLboolean   destroyed;
	glm::vec2 velocity;

	SpriteRenderer* renderer = nullptr;

	// Render state
	Texture2D   sprite;
	//SpriteRenderer renderer(ResourceManager::GetShader("sprite"));

	// Constructor(s)
	GameObject();
	void DrawLevel(Texture2D sprite, glm::vec3 color);
	// Draw sprite
	 void DrawAnimation(Texture2D texSprite, glm::vec2 texPos, glm::vec2 texSize, GLfloat texRotation);
};

