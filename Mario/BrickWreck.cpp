#include "BrickWreck.hpp"
#include <iostream>
namespace Mario
{
	BrickWreck::BrickWreck(GameDataRef data, sf::Texture& texture, float radius)
		: _data(data)
	{
		_circle.setTexture(&texture);
		_circle.setRadius(radius);
		
		_clock.restart();
	}
	BrickWreck::BrickWreck(const BrickWreck & object)
		:_data(object._data), _circle(object._circle), _velocity(object._velocity)
	{
		_clock.restart();
	}
	void BrickWreck::Init(const BrickWreck & object)
	{
		_data = object._data;
		_circle = object._circle;
		_velocity = object._velocity;
		_clock.restart();
	}
	
	BrickWreck::~BrickWreck()
	{
	}
	void BrickWreck::Set_Pos(sf::Vector2f pos)
	{
		_circle.setPosition(pos);
	}

	void BrickWreck::Set_Velocity(sf::Vector2f velocity)
	{
		_velocity = velocity;
	}

	void BrickWreck::Update(float dt)
	{
		/*_velocity.y += dt * GRAVITY;*/
		_velocity.y += GRAVITY_ACCELERATION;
		_velocity.y = std::min(_velocity.y, CAMERA_SPEED);
		_circle.rotate(30.f * dt);

		_circle.move(_velocity * dt);
	}
	sf::Clock BrickWreck::Get_Clock(void)
	{
		return _clock;
	}
	void BrickWreck::Draw(void)
	{
		this->_data->window.draw(_circle);
	}
}