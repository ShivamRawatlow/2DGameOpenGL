#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);	
}

void SpriteRenderer::DrawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{		
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 1.0f, 0.0f)); // Then rotate
	
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size.x,size.y,1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::DrawInstance(Texture2D texture, glm::vec3 color)
{	
	this->shader.Use();
	glm::mat4 model ;
	//model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	//model = glm::rotate(model, rotate, glm::vec3(0.0f, 1.0f, 0.0f)); // Then rotate

	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(ResourceManager::tileSize.x, ResourceManager::tileSize.y, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	unsigned int noOfInstance = (ResourceManager::tilePositions.size() / 2);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,noOfInstance);
	//std::cout<<noOfInstance<<std::endl;
	glBindVertexArray(0);
}


void SpriteRenderer::initRenderData()
{
	GLfloat vertices[] = {

		//pos      //texcord
		//top left triangle
		0.0f, 1.0f, 0.0f, 1.0f, //0
		1.0f, 0.0f, 1.0f, 0.0f, //1
		0.0f, 0.0f, 0.0f, 0.0f, //2

		//bottom right triangle
		1.0f, 1.0f, 1.0f, 1.0f //3	
	};

	GLuint indices[] = {
		0,1,2,
		0,3,1
	};
	
	GLuint VBO, EBO;
	

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	
	glBindVertexArray(this->quadVAO);	
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	
	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/////level instancing /////////////////////////////////////////////

	unsigned int instanceVBO;
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, (ResourceManager::tilePositions.size()*sizeof(GLfloat)),ResourceManager::tilePositions.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);// this line must come before vertex attrib divisor i dont know why
	glVertexAttribDivisor(1, 1);
	
}



