#include "Mario.hpp"
#include "DEFINITIONS.hpp"
#include "Collision.hpp"
#include <iostream>

namespace Mario
{
	Mario::Mario(GameDataRef data)
		: _data(data), _marioState(MarioState::STOP_RIGHT), _UpDown(-1)
		, _pos(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2))
		, _maxSpeed(CAMERA_SPEED, CAMERA_SPEED), _velocity(0, 0)
	{
		this->_bottomCollision  = new Collision(data);
		this->_bodyCollision = new Collision(data);
		this->_headCollision = new Collision(data);
	}
	Mario::~Mario()
	{
		;
	}

	void Mario::Init(sf::Texture & texture)
	{	
		/*sf::Vector2i pos(UNIT_SIZE * 10 + UNIT_SIZE * (1.29) * 1, UNIT_SIZE * 1); 
		sf::Vector2i size(UNIT_SIZE * (1.28), UNIT_SIZE * 2);*/

		sf::Vector2i pos(UNIT_SIZE * 1 + UNIT_SIZE * (0) * 3, UNIT_SIZE * 3);
		sf::Vector2i size(UNIT_SIZE * 1, UNIT_SIZE * 1);
		sf::IntRect rect(pos, size);
		sp.setTextureRect(rect);

		sp.setTexture(texture);

		sp.setPosition(
			_pos.x - size.x / 2,
			_pos.y - size.y / 2
		);

		this->_bottomCollision->Init(
			sf::Vector2f(_pos.x + size.x / 4, _pos.y + size.y - BOTTOM_COLLISION_THICKNESS / 2),
			sf::Vector2f(size.x / 2, BOTTOM_COLLISION_THICKNESS)
		);

		this->_bodyCollision->Init(
			sf::Vector2f(_pos.x /*- BOTTOM_COLLISION_THICKNESS / 2*/, _pos.y + BOTTOM_COLLISION_THICKNESS / 2 ),
			sf::Vector2f(size.x /*+ BOTTOM_COLLISION_THICKNESS * 1*/, size.y - BOTTOM_COLLISION_THICKNESS * 1)
		);

		this->_headCollision->Init(
			sf::Vector2f(_pos.x + size.x / 3, _pos.y - BOTTOM_COLLISION_THICKNESS / 2),
			sf::Vector2f(size.x / 3, BOTTOM_COLLISION_THICKNESS)
		);
	}

	void Mario::Set_Move(int direction)
	{
		_marioState = direction;
	}

	int Mario::Get_Move(void)
	{
		return _marioState;
	}


	void Mario::Draw()
	{
		this->_data->window.draw(sp);
	}

	void Mario::Update(float dt)
	{
		if(_marioState == MarioState::MOVE_RIGHT)
		{
			if (_UpDown == 0) 
			{
				Accelerate_Velocity(
					sf::Vector2f(WALK_ACCELERATION, 0)
				);
			}
			else
			{
				if(Get_Velocity().x < WALK_ACCELERATION * (2 + 0.5))
				{
					Set_Velocity(
						sf::Vector2f(WALK_ACCELERATION * (2 + 0.5), Get_Velocity().y)
					);
				}
			}
		}
		if (_marioState == MarioState::MOVE_LEFT)
		{
			if (_UpDown == 0)
			{
				Accelerate_Velocity(
					sf::Vector2f(-WALK_ACCELERATION, 0)
				);
			}
			else
			{
				if (Get_Velocity().x > -WALK_ACCELERATION * (2 + 0.5))
				{
					Set_Velocity(
						sf::Vector2f(-WALK_ACCELERATION * (2 + 0.5), Get_Velocity().y)
					);
				}
			}
		}
		if(this->_UpDown < 0)
		{
			Accelerate_Velocity(
				sf::Vector2f(0, -GRAVITY_ACCELERATION * _UpDown)
			);
		}
		else if(this->_UpDown > 0)
		{
			_velocity.y = -JUMP_SPEED * _UpDown;
			this->Set_UpDown(-1);

			/*if(this->_jumpClock.getElapsedTime().asSeconds() <= JUMP_DURATION)
			{
				_velocity.y = -JUMP_SPEED * _UpDown;
			}
			else
			{
				this->Set_UpDown(-1);
				Accelerate_Velocity(
					sf::Vector2f(0, -GRAVITY_ACCELERATION * _UpDown)
				);
			}*/
		}
		else
		{
			_velocity.y = 0;
		}

		this->Move(_velocity * dt);
	}
	sf::Vector2f Mario::Get_Pos(void)
	{
		return _pos;
	}
	
	void Mario::Set_UpDown(int state)
	{
		if (state > 0 && this->_UpDown <= 0)
		{
			this->_jumpClock.restart();
		}
		this->_UpDown = state;
	}

	int Mario::Get_UpDown(void)
	{
		return this->_UpDown;
	}

	Collision Mario::Get_Bottom_Collision(void)
	{
		return Collision(*(this->_bottomCollision));
	}

	Collision Mario::Get_Body_Collsion(void)
	{
		return Collision(*(this->_bodyCollision));
	}

	Collision Mario::Get_Head_Collsion(void)
	{
		return Collision(*(this->_headCollision));
	}

	const Collision * Mario::Get_Bottom_Collision_Ref(void)
	{
		return this->_bodyCollision;
	}

	const Collision * Mario::Get_Body_Collision_Ref(void)
	{
		return this->_bodyCollision;
	}

	const Collision * Mario::Get_Head_Collision_Ref(void)
	{
		return this->_headCollision;
	}

	void Mario::Set_Pos(sf::Vector2f pos)
	{
		_pos = pos;
		this->_bottomCollision->Set_Pos(
			pos
		);

		this->_bodyCollision->Set_Pos(
			pos
		);
		this->_headCollision->Set_Pos(
			pos
		);
		sp.setPosition(
			_pos
		);
	}

	void Mario::Move(sf::Vector2f _d_pos)
	{
		_pos += _d_pos;

		this->_bottomCollision->Set_Pos(
			_bottomCollision->Get_Pos() + _d_pos
		);

		this->_bodyCollision->Set_Pos(
			_bodyCollision->Get_Pos() + _d_pos
		);
		this->_headCollision->Set_Pos(
			_headCollision->Get_Pos() + _d_pos
		);
		sp.setPosition(
			_pos
		);
	}
	int Mario::Get_State(void)
	{
		return this->_marioState;
	}
	void Mario::Accelerate_Velocity(sf::Vector2f d_Velocity)
	{
		if((_velocity + d_Velocity).x > _maxSpeed.x)
		{
			_velocity.x = _maxSpeed.x;
		}
		else if ((_velocity + d_Velocity).x < -_maxSpeed.x)
		{
			_velocity.x = -_maxSpeed.x;
		}
		else
		{
			_velocity.x += d_Velocity.x;
		}

		if ((_velocity + d_Velocity).y > _maxSpeed.y)
		{
			_velocity.y = _maxSpeed.y;
		}
		else
		{
			_velocity.y += d_Velocity.y;
		}
	}
	void Mario::Set_Velocity(sf::Vector2f velocity)
	{
		_velocity = velocity;
	}
	sf::Vector2f Mario::Get_Velocity(void)
	{
		return _velocity;
	}
}