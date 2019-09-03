#include "GameLevel.h"

GameLevel::GameLevel()
{
	width = 100;
	height = 100;
}

void GameLevel::Draw()
{
	Brick.DrawLevel(ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
}


void GameLevel::Load(const GLchar *file)
{
	// Clear old data
	//this->Brick.clear();
	// Load from file
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);

			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, width, height);
	}
}


void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	// Calculate dimensions
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;
	ResourceManager::tileSize = glm::vec2(unit_width, unit_height);
	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			// Check block type from level data (2D level array)
			if (tileData[y][x] == 1) // Solid
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				ResourceManager::tilePositions.push_back(pos.x);
				ResourceManager::tilePositions.push_back(pos.y);
				ResourceManager::tilePositionsVector.push_back(glm::vec2(pos.x, pos.y));
			}
		}
	}

	//GameObject obj(glm::vec2(pos.x, pos.y), size, ResourceManager::GetTexture("block_solid"), 0.0f, glm::vec3(0.8f, 0.8f, 0.7f));
}

