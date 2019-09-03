#pragma once
#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:
	
	GLfloat xOffset;
	GLfloat leftConstrain;
	GLfloat rightConstrain;


	Camera();
	~Camera();
};

