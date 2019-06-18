#include "Animation_Object.hpp"

namespace Mario 
{
	Anim_Object::Anim_Object(GeometricObject & object, const Collision * collision, float animDuration)
		: Event_GeometricObject(object, collision), _displayed_sprite(0)
		, _animDuration(animDuration), _num_draw_cycle(-1), _num_draw(0)
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
			
			// _displayed_sprite 는 이미 draw 한 sprite 를 나타낸다.
			if(_displayed_sprite >= _sprites.size() && _num_draw_cycle > 0)
			{
				_num_draw_cycle--;
			}
			_displayed_sprite %= _sprites.size();
			_animTimer.restart();
		}
	}
	void Anim_Object::Draw(void)
	{
		_data->window.draw(_sprites[_displayed_sprite]);
	}

	void Anim_Object::Push_Texture(sf::Texture* texture)
	{
		sf::Sprite sp(*texture);
		sf::Vector2f pos(GeometricObject::Get_Pos());
		sp.setPosition(pos);
		_sprites.push_back(sp);
	}
	void Anim_Object::Update(float dt)
	{
		Texture_Change();
	}
	int Anim_Object::Get_Num_DrawCycle(void)
	{
		return _num_draw_cycle;
	}
	void Anim_Object::Set_Num_DrawCycle(int cycle)
	{
		_num_draw_cycle = cycle;
	}
}
