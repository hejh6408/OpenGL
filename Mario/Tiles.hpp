#pragma once
#include "Game.hpp"
#include <vector>

namespace Mario
{
	class Tile
	{
	public:
		Tile(GameDataRef data);
		~Tile();
		
		void Draw();
		const std::vector<sf::Sprite> &GetSprites() const;
		void MoveTiles(float dt);
	private:
		GameDataRef _data;

		std::vector<sf::Texture> _tileTexture;
		std::vector<sf::Sprite> _tiles;

		float SPAWN_ROW_BASE;
	};
}