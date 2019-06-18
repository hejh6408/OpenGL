#pragma once

#include "Game.hpp"
namespace Mario
{
	class Collision
	{
	public:
		Collision(GameDataRef data);
		~Collision();
		
		void Init(sf::Vector2f pos, sf::Vector2f size);
		
		sf::FloatRect Get_Box() const;
		bool CheckCollision(Collision& comp_box) const;
		
		void Set_Pos(sf::Vector2f pos);
		sf::Vector2f Get_Pos() const;

		sf::FloatRect Collision_Area(Collision& comp_box);

		void Move(sf::Vector2f _dpos);

	private:
		GameDataRef _data;
		sf::FloatRect _box;
	};
}