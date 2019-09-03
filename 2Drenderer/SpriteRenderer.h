#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"


class SpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRenderer(Shader shader);
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawInstance(Texture2D texture, glm::vec3 color);

private:
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

