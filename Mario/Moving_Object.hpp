#pragma once
#include "Animation_Object.hpp"

namespace Mario
{
	class Moving_Object: public Anim_Object 
	{
	public:
		Moving_Object(GeometricObject & object, const Collision * collision, float animDuration);
		Moving_Object(Anim_Object& obj);
		~Moving_Object();

		void Set_Velocity(sf::Vector2f vel);
		void Accelerate(sf::Vector2f dv);
		void Init(void);
		void Move(sf::Vector2f dpos);

		void Set_Pos(sf::Vector2f pos);
		void Handle_Collision(GeometricObject& obj);
		void Update(float dt);
	private:
		sf::Vector2f _velocity;
		Collision* _headCollision;
		Collision* _bodyCollision;
		Collision* _bottomCollision;
	};
}