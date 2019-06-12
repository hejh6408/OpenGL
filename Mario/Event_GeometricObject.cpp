#include "Event_GeometricObject.hpp"

namespace Mario 
{
	Event_GeometricObject::Event_GeometricObject(GeometricObject & object, const Collision * collision)
		: GeometricObject(object), _collision(collision), _life(-1), _eventState(Event_Number::NONE), _direction(0)
		, _border(sf::Vector2f(-1000.f, -1000.f), sf::Vector2f(2000.f, 2000.f))
	{
		;
	}

	Event_GeometricObject::~Event_GeometricObject()
	{
		;
	}

	Event_Number Event_GeometricObject::Event(const Collision * collision)
	{
		if(collision == _collision && _life >= 0)
		{
			Set_EventState(_functions[_life--]());
			return Get_EventState();
		}
		return Event_Number::NONE;
	}
	void Event_GeometricObject::Reset_Life(void)
	{
		_life = _functions.size() - 1;
	}
	void Event_GeometricObject::Set_Life(int life)
	{
		_life = life;
	}
	int Event_GeometricObject::Get_Life(void)
	{
		return _life;
	}
	void Event_GeometricObject::Push_Event(Event_Number(*func)(void))
	{
		if (func == nullptr) return;

		_functions.push_back(func);
		_life++;
	}
	void Event_GeometricObject::Set_EventState(Event_Number _state)
	{
		_eventState = _state;
	}
	Event_Number Event_GeometricObject::Get_EventState(void)
	{
		return this->_eventState;
	}
	void Event_GeometricObject::Reset_Clock(void)
	{
		this->_moveClock.restart();
	}
	sf::Clock Event_GeometricObject::Get_Clock(void)
	{
		return this->_moveClock;
	}
	void Event_GeometricObject::Set_Direction(int direction)
	{
		_direction = direction;
	}
	int Event_GeometricObject::Get_Direction(void)
	{
		return _direction;
	}
	void Event_GeometricObject::Set_Border(sf::FloatRect border)
	{
		_border = border;
	}

	sf::FloatRect Event_GeometricObject::Get_Border(void)
	{
		return this->_border;
	}
	void Event_GeometricObject::Move(sf::Vector2f dpos)
	{
		GeometricObject::Move(dpos);
		_movingDistance += dpos;
	}
	sf::Vector2f Event_GeometricObject::Get_MoveDistance(void)
	{
		return _movingDistance;
	}
}