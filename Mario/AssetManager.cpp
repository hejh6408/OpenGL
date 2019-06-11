#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

#include <iostream>

namespace Mario
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			/*std::cout << name << ": [" << tex.getSize().x << ", " <<tex.getSize().y << "]" << std::endl;*/

			this->_textures[name] = tex;
		}
	}

	void AssetManager::LoadTexture(std::string name, std::string fileName, int r, int c, int N)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			float unit_size = tex.getSize().x / N;

			sf::IntRect rect(unit_size * c, unit_size * r, unit_size, unit_size);

			tex.loadFromFile(fileName, rect);
			std::cout << name << ": [" << tex.getSize().x << ", " << tex.getSize().y << "]" << std::endl;
			this->_textures[name] = tex;
		}
	}

	std::vector<sf::Texture> AssetManager::Parse_Texture(std::string fileName, int r, int c)
	{
		std::vector<sf::Texture> ret;

		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			float unit_size = tex.getSize().x / (float)c;

			for(int i = 0; i < r; i++)
			{
				for(int j = 0; j < c; j++)
				{
					sf::IntRect rect(unit_size * j, unit_size * i, unit_size, unit_size);

					tex.loadFromFile(fileName, rect);

					ret.push_back(tex);
				}
			}
		}

		return ret;
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
}