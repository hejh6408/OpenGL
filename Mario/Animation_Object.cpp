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
	void Anim_Object::Texture_Change(void)
	{
		if (_animTimer.getElapsedTime().asSeconds() < _animDuration)
		{
			return;
		}
		else 
		{
			_displayed_sprite++;
			_displayed_sprite %= _sprites.size();
			_animTimer.restart();
		}
	}
	void Anim_Object::Draw(void)
	{
		_data->window.draw(_sprites[_displayed_sprite]);
		Texture_Change();
	}

	void Anim_Object::Push_Texture(sf::Texture* texture)
	{
		sf::Sprite sp(*texture);
		sf::Vector2f pos(GeometricObject::Get_Pos());
		sp.setPosition(pos);
		_sprites.push_back(sp);
	}
}
