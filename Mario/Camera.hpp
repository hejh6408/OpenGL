#pragma once
#include "Game.hpp"
#include <SFML/Graphics.hpp>
namespace Mario
{
	class Camera
	{
	public:
		Camera(GameDataRef data);
		~Camera();

		void Set_Pos(sf::Vector2f& pos);
		sf::Vector2f Get_Pos();

	private:
		GameDataRef _data;
		sf::View _view;
	};
}