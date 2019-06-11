#include "Animation_Object.hpp"

namespace Mario 
{
	Anim_Object::Anim_Object(GeometricObject & object, const Collision * collision, float animDuration)
		: Event_GeometricObject(object, collision), _displayed_sprite(0)
		, _animDuration(animDuration)
	{
		_animTimer.restart();
	}
	Anim_Object::~Anim_Object()
	{
	}
	void Anim_Object::Change_Sprite(void)
	{
		if (_animTimer.getElapsedTime().asSeconds() < _animDuration)
		{
			return;
		}
		else 
		{
			_displayed_sprite++;
			_displayed_sprite %= _sprites.size();
		}
	}
	void Anim_Object::Draw(void)
	{
		_sprites[_animDuration];
	}
	void Anim_Object::Push_Sprite(sf::Sprite sp)
	{
		_sprites.push_back(sp);
	}
}
