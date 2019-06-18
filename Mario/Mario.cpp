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
		, _idx_motion(0), _isJumping(false)
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

		sf::Vector2i pos(UNIT_SIZE * 0, UNIT_SIZE * 3);
		sf::Vector2i size(UNIT_SIZE * 1, UNIT_SIZE * 1);
		sf::IntRect rect(pos, size);
		/*sp.setTextureRect(rect);

		sp.setTexture(texture);

		sp.setPosition(
			_pos.x + size.x / 2,
			_pos.y
		);
		sp.setOrigin(
			sf::Vector2f(sp.getGlobalBounds().width / 2, 0)
		);*/

		this->_bottomCollision->Init(
			sf::Vector2f(_pos.x + size.x / 4, _pos.y + size.y - BOTTOM_COLLISION_THICKNESS / 2),
			sf::Vector2f(size.x / 2, BOTTOM_COLLISION_THICKNESS)
		);

		this->_bodyCollision->Init(
			sf::Vector2f(_pos.x, _pos.y + BOTTOM_COLLISION_THICKNESS / 2 ),
			sf::Vector2f(size.x, size.y - BOTTOM_COLLISION_THICKNESS * 1)
		);

		this->_headCollision->Init(
			sf::Vector2f(_pos.x + size.x / 3, _pos.y - BOTTOM_COLLISION_THICKNESS / 2),
			sf::Vector2f(size.x / 3, BOTTOM_COLLISION_THICKNESS)
		);

		{
			sf::IntRect rect(sf::Vector2i(UNIT_SIZE * 5, UNIT_SIZE * 3), size);
			sf::Sprite _sp;

			_sp.setTextureRect(rect);
			_sp.setTexture(texture);

			_sp.setPosition(
				_pos.x + size.x / 2,
				_pos.y
			);
			_sp.setOrigin(
				sf::Vector2f(_sp.getGlobalBounds().width / 2, 0)
			);
			_marioMotion.push_back(_sp);
		}
		for (int i = 0; i < 4; i++)
		{
			sf::IntRect rect(pos, size);
			sf::Sprite _sp;

			_sp.setTextureRect(rect);
			_sp.setTexture(texture);

			_sp.setPosition(
				_pos.x + size.x / 2,
				_pos.y
			);
			_sp.setOrigin(
				sf::Vector2f(_sp.getGlobalBounds().width / 2, 0)
			);

			_marioMotion.push_back(_sp);
			pos.x += UNIT_SIZE;
		}
		
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
		/*this->_data->window.draw(sp);*/
		this->_data->window.draw(_marioMotion[_idx_motion]);
	}

	void Mario::Update(float dt)
	{
		if (_marioState == MarioState::MOVE_RIGHT || _marioState == MarioState::MOVE_LEFT)
		{
			if(_motionClock.getElapsedTime().asSeconds() > 0.15)
			{
				_idx_motion = (_idx_motion + 1) % _marioMotion.size();
				_idx_motion = (_idx_motion < 2) ? 2 : _idx_motion;

				/*if (_idx_motion == _marioMotion.size() - 1) 
				{
					_idx_motion = 2;
				}
				else 
				{
					_idx_motion = (_idx_motion  + 1 ) % _marioMotion.size();
				}*/
				_motionClock.restart();
			}
		}
		if (_marioState == MarioState::STOP_RIGHT || _marioState == MarioState::STOP_LEFT)
		{
			Set_Velocity(
				sf::Vector2f(0, _velocity.y)
			);
			_idx_motion = 1;
		}
		if(_isJumping == true)
		{
			_idx_motion = 0;
		}

		if(_marioState == MarioState::MOVE_RIGHT || _marioState == MarioState::STOP_RIGHT)
		{
			_marioMotion[_idx_motion].setScale(
				sf::Vector2f(1.f, 1.f)
			);
		}
		if (_marioState == MarioState::MOVE_LEFT || _marioState == MarioState::STOP_LEFT)
		{
			_marioMotion[_idx_motion].setScale(
				sf::Vector2f(-1.0f, 1.0f)
			);
		}
		/*if (_marioState == MarioState::MOVE_RIGHT || _marioState == MarioState::STOP_RIGHT)
		{
			sp.setScale(
				sf::Vector2f(1.0f, 1.0f)
			);
		}
		if (_marioState == MarioState::MOVE_LEFT || _marioState == MarioState::STOP_LEFT)
		{
			sp.setScale(
				sf::Vector2f(-1.0f, 1.0f)
			);
		}*/

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
		for(auto& sp : _marioMotion)
		{
			sp.setPosition(pos);
		}

		/*sp.setPosition(
			_pos
		);*/
	}

	void Mario::Move(sf::Vector2f _d_pos)
	{
		_pos += _d_pos;

		this->_bottomCollision->Move(
			_d_pos
		);

		this->_bodyCollision->Move(
			_d_pos
		);
		this->_headCollision->Move(
			_d_pos
		);
		for (auto& sp : _marioMotion)
		{
			sp.move(_d_pos);
		}
		/*sp.move(
			_d_pos
		);*/
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
	void Mario::Set_Jump(bool isjump)
	{
		_isJumping = isjump;
	}
}