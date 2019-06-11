#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Collision.hpp"
#include <vector>

namespace Mario
{
	class GeometricObject
	{
	public:
		GeometricObject(GameDataRef data);
		GeometricObject(const GeometricObject& object);
		~GeometricObject();
		
		void Init(sf::Texture& _texture, int _r, int _c);
		void Init(std::vector<std::vector<sf::Texture*>> & _texture);

		void Set_Pos(sf::Vector2f);
		sf::Vector2f Get_Pos();
		void Move(sf::Vector2f);

		void Draw(void);

		Collision Get_Collision(void);
		void Set_Collision_Pos(sf::Vector2f);

		sf::Vector2f Get_Size(void);
	protected:
		std::vector<sf::Sprite> _sprites;
	private:
		GameDataRef _data;
		sf::Vector2f _pos;

		Collision* _collision;

		sf::Vector2u _unitSize;
		sf::Vector2f _size;
	};
}