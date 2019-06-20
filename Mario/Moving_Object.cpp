#include "Moving_Object.hpp"
#include <cmath>

namespace Mario
{
	Moving_Object::Moving_Object(GeometricObject & object, const Collision * collision, float animDuration)
		: Anim_Object(object, collision, animDuration), _velocity(sf::Vector2f(30.f, 0))
	{
		_headCollision = new Collision(this->_data);
		_bodyCollision = new Collision(this->_data);
		_bottomCollision = new Collision(this->_data);
	}
	Moving_Object::Moving_Object(Anim_Object & obj)
		: Anim_Object(obj), _velocity(sf::Vector2f(30.f, 0))
	{
		_headCollision = new Collision(this->_data);
		_bodyCollision = new Collision(this->_data);
		_bottomCollision = new Collision(this->_data);
	}

	Moving_Object::~Moving_Object()
	{
	}
	void Moving_Object::Set_Velocity(sf::Vector2f vel)
	{
		_velocity = vel;
	}
	void Moving_Object::Accelerate(sf::Vector2f dv)
	{
		_velocity += dv;
	}
	void Moving_Object::Init(void)
	{
		_bottomCollision->Init(
			sf::Vector2f(_pos.x + _size.x / 3, _pos.y + _size.y - BOTTOM_COLLISION_THICKNESS),
			sf::Vector2f(_size.x / 3, BOTTOM_COLLISION_THICKNESS)
		);

		this->_bodyCollision->Init(
			sf::Vector2f(_pos.x, _pos.y + BOTTOM_COLLISION_THICKNESS),
			sf::Vector2f(_size.x, _size.y - BOTTOM_COLLISION_THICKNESS * 2)
		);

		this->_headCollision->Init(
			sf::Vector2f(_pos.x + _size.x / 3, _pos.y - BOTTOM_COLLISION_THICKNESS),
			sf::Vector2f(_size.x / 3, BOTTOM_COLLISION_THICKNESS)
		);
	}
	void Moving_Object::Move(sf::Vector2f dpos)
	{
		_bottomCollision->Move(dpos);
		_bodyCollision->Move(dpos);
		_headCollision->Move(dpos);

		Event_GeometricObject::Move(dpos);
	}
	void Moving_Object::Set_Pos(sf::Vector2f pos)
	{
		sf::Vector2f dpos = _pos - pos;

		_bottomCollision->Move(dpos);
		_bodyCollision->Move(dpos);
		_headCollision->Move(dpos);

		Event_GeometricObject::Move(dpos);
	}
	void Moving_Object::Handle_Collision(GeometricObject & obj)
	{
		Collision obj_collision(obj.Get_Collision());

		bool is_bottom_collision = _bottomCollision->CheckCollision(obj_collision);
		bool is_body_collision = _bodyCollision->CheckCollision(obj_collision);
		bool is_head_collision = _headCollision->CheckCollision(obj_collision);

		if(is_bottom_collision)
		{
			float dh = obj.Get_Pos().y - (_bottomCollision->Get_Pos().y + _bottomCollision->Get_Box().height);
			
			this->Move(sf::Vector2f(0, dh / 4));
			_velocity.y = -JUMP_SPEED * 1.3;
			/*_velocity.y = 0;*/
		}
		
		if(is_body_collision)
		{
			_velocity.x = -_velocity.x;
		}

		if(is_head_collision)
		{
			float dh = obj.Get_Pos().y + obj.Get_Size().y - _headCollision->Get_Pos().y;
			this->Move(sf::Vector2f(0, dh));
			_velocity.y = 0;
		}
	}
	void Moving_Object::Update(float dt)
	{
		Anim_Object::Update(dt);
		
		this->Move(dt * _velocity);
		_velocity.y = std::min(_velocity.y + GRAVITY_ACCELERATION, CAMERA_SPEED);
	}
}