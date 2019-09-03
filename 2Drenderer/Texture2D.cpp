#include "Texture2D.h"
#include <iostream>


Texture2D::Texture2D()
	: Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data)
{
	this->Width = width;
	this->Height = height;

	// Create Texture
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);

	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

//void Texture2D::GenerateArrayTexture(GLuint width, GLuint height, unsigned char * data)
//{
//
//	this->Width = width;
//	this->Height = height;
//
//	//Generate an array texture
//	//glGenTextures(1, &gArrayTexture);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
//
//	//Create storage for the texture. (100 layers of 1x1 texels)
//	glTexStorage3D(GL_TEXTURE_2D_ARRAY,
//		1,                    //No mipmaps as textures are 1x1
//		GL_RGB8,              //Internal format
//		12, 6,                 //width,height
//		100                   //Number of layers
//	);
//
//	for (unsigned int i(0); i != 100; ++i)
//	{
//
//
//		//Specify i-essim image
//		glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
//			0,                     //Mipmap number
//			0, 0, i,                 //xoffset, yoffset, zoffset
//			width, height, 0,                 //width, height, depth
//			GL_RGBA,                //format
//			GL_UNSIGNED_BYTE,      //type
//			data);                //pointer to data
//	}
//
//	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}