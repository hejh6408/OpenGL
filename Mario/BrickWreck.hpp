#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
namespace Mario
{
	class BrickWreck
	{
	public:
		BrickWreck(GameDataRef data, sf::Texture& texture, float radius);
		BrickWreck(const BrickWreck& object);
		void Init(const BrickWreck& object);
		~BrickWreck();

		void Set_Pos(sf::Vector2f pos);
		void Set_Velocity(sf::Vector2f _velocity);
		void Update(float dt);
		sf::Clock Get_Clock(void);

		void Draw(void);
	private:
		sf::CircleShape _circle;
		sf::Vector2f _velocity;
		sf::Clock _clock;
		GameDataRef _data;
	};
}