#include "Collision.hpp"
#include <algorithm>

namespace Mario
{
	Collision::Collision(GameDataRef data)
		: _data(data)
	{
		;
	}
	Collision::~Collision()
	{
		;
	}
	
	void Collision::Init(sf::Vector2f pos, sf::Vector2f size)
	{
		_box.left = pos.x;
		_box.top = pos.y;

		_box.width = size.x;
		_box.height = size.y;
	}
	sf::FloatRect Collision::Get_Box() const
	{
		return _box;
	}
	bool Collision::CheckCollision(Collision & comp_box) const
	{
		if(_box.intersects(comp_box.Get_Box()))
		{
			return true;
		}
		return false;
	}
	void Collision::Set_Pos(sf::Vector2f pos)
	{
		_box.left = pos.x;
		_box.top = pos.y;
	}
	sf::Vector2f Collision::Get_Pos() const
	{
		return sf::Vector2f(_box.left, _box.top);
	}

	sf::FloatRect Collision::Collision_Area(Collision & comp_box)
	{
		sf::FloatRect ret;

		ret.left = std::max(this->_box.left, comp_box.Get_Box().left);
		ret.top = std::max(this->_box.top, comp_box.Get_Box().top);

		ret.width = std::min(this->_box.left + this->_box.width, comp_box.Get_Box().left + comp_box.Get_Box().width) - ret.left;
		ret.height = std::min(this->_box.top + this->_box.height, comp_box.Get_Box().top + comp_box.Get_Box().height) - ret.top;

		return ret;
	}
	void Collision::Move(sf::Vector2f _dpos)
	{
		_box.left += _dpos.x;
		_box.top += _dpos.y;
	}
}