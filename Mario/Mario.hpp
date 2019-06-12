#pragma once

#include "GeometricObject.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include <vector>
namespace Mario
{
	class Mario
	{
	public:
		Mario(GameDataRef data);
		~Mario();

		void Init(sf::Texture& texture);
		
		void Set_Move(int direction);
		int Get_Move(void);

		void Draw();
		void Update(float dt);
		sf::Vector2f Get_Pos(void);

		Collision Get_Bottom_Collision(void);
		Collision Get_Body_Collsion(void);
		Collision Get_Head_Collsion(void);

		const Collision* Get_Bottom_Collision_Ref(void);
		const Collision* Get_Body_Collision_Ref(void);
		const Collision* Get_Head_Collision_Ref(void);


		void Set_UpDown(int state);
		int Get_UpDown(void);
		
		void Set_Pos(sf::Vector2f _pos);
		void Move(sf::Vector2f _d_pos);

		int Get_State(void);

		void Accelerate_Velocity(sf::Vector2f d_Velocity);
		void Set_Velocity(sf::Vector2f velocity);
		sf::Vector2f Get_Velocity(void);

		void Set_Jump(bool isjump);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Clock _jumpClock;

		std::vector<sf::Texture> _animationFrames;
		std::vector<std::vector<sf::Sprite>> _sprites;

		sf::Sprite sp;

		int _marioState;
		sf::Vector2f _pos;

		Collision* _bottomCollision;
		Collision* _bodyCollision;
		Collision* _headCollision;

		int _UpDown;

		sf::Vector2f _velocity;

		sf::Vector2f _maxSpeed;

		sf::Clock _motionClock;
		std::vector<sf::Sprite > _marioMotion;
		int _idx_motion;
		bool _isJumping;
	};
}