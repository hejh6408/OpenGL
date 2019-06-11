#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace Mario
{
	class AssetManager
	{
	public:
		AssetManager() { }
		~AssetManager() { }

		void LoadTexture(std::string name, std::string fileName);
		void LoadTexture(std::string name, std::string fileName, int r, int c, int N);
		std::vector<sf::Texture> Parse_Texture(std::string fileName, int r, int c);
		
		sf::Texture &GetTexture(std::string name);


		void LoadFont(std::string name, std::string fileName);
		sf::Font &GetFont(std::string name);

	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
	};
}
