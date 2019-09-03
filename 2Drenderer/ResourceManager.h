#pragma once

#include <map>
#include <string>

#include <glew.h>
#include <glew.h>
#include <glm.hpp>
#include <vector>

#include "Texture2D.h"
#include "Shader.h"

class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Texture2D> MainCharacterTextures;
	static std::map<std::string, Texture2D> EnemyCharacterTextures;
	static std::vector<GLfloat> tilePositions;
	static std::vector<glm::vec2> tilePositionsVector;
	static glm::vec2 tileSize;



	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static void   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	// Retrieves a stored sader
	static Shader   GetShader(std::string name);
	// Loads (and generates) a texture from file
	static void LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static void LoadMainCharacterTexture(const GLchar* file, GLboolean alpha, std::string name);
	static void LoadEnemyCharacterTexture(const GLchar* file, GLboolean alpha, std::string name);
	static Texture2D GetMainCharacterTexture(std::string name);
	static Texture2D GetEnemyCharacterTexture(std::string name);
	static Texture2D GetTexture(std::string name);
	// Properly de-allocates all loaded resources
	static void Clear();
private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha, std::string);
};

