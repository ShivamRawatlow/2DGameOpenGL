#include "GameObject.h"



GameObject::GameObject()
	: position(0, 0), size(1, 1), color(1.0f), rotation(0.0f), sprite(), isSolid(false), destroyed(false), velocity(glm::vec2(0))
{
	renderer = new SpriteRenderer(ResourceManager::GetShader("level"));
	  
}

//GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, GLfloat rotation, glm::vec3 color, glm::vec2 velocity)
//	: position(pos), size(size), velocity(velocity), color(color), rotation(rotation), sprite(sprite), isSolid(false), destroyed(false)
//{
//	renderer = new SpriteRenderer(ResourceManager::GetShader("level"));
//}

void GameObject::DrawLevel(Texture2D sprite, glm::vec3 color)
{
	if (renderer)
	{
		renderer->DrawInstance(sprite,color);
	}

	else
	{
		std::cout << "Renderer object empty";
	}
}

void GameObject::DrawAnimation(Texture2D texSprite, glm::vec2 texPos, glm::vec2 texSize, GLfloat texRotation)
{
	if (renderer)
	{
		//std::cout << "Draw command initilalised" << std::endl;
		renderer->DrawSprite(texSprite, texPos, texSize, texRotation, this->color);
	}
	else
	{
		std::cout << "Renderer object empty";
	}	
}


