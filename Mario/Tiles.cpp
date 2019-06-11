#include "Tiles.hpp"
#include "DEFINITIONS.hpp"

#include <fstream>
namespace Mario
{
	Tile::Tile(GameDataRef data)
		:_data(data)
	{
		float unit_size = this->_data->assets.GetTexture("Tiles").getSize().x / TILES_COL;

		for(int i = 0; i < TILES_ROW; i++)
		{
			for(int j = 0; j < TILES_COL; j++)
			{
				sf::IntRect rect(unit_size * j, unit_size * i, unit_size, unit_size);
				sf::Texture txt;
				txt.loadFromFile(TILES_PATH, rect);
				_tileTexture.push_back(txt);

			}
		}
		
		std::ifstream cin(MAP_1_1_PATH);

		int N, M;
		cin >> N >> M;

		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < M; j++)
			{
				int t;
				cin >> t;
				sf::Sprite sp(_tileTexture[t]);
				sp.setPosition(unit_size * j, unit_size * i);
				_tiles.push_back(sp);
			}
		}

		cin.close();
	}

	void Tile::MoveTiles(float dt)
	{
		for (int i = 0; i < _tiles.size(); i++)
		{
			if (_tiles.at(i).getPosition().x < 0 - _tiles.at(i).getLocalBounds().width)
			{
				_tiles.erase(_tiles.begin() + i);
			}
			else
			{
				sf::Vector2f position = _tiles.at(i).getPosition();
				float movement = CAMERA_SPEED * dt;

				_tiles.at(i).move(-movement, 0);
			}
		}
	}

	Tile::~Tile()
	{
	}
	void Tile::Draw()
	{
		for(auto & tile : _tiles)
		{
			this->_data->window.draw(tile);
		}
	}
	const std::vector<sf::Sprite>& Tile::GetSprites() const
	{
		return _tiles;
	}
}