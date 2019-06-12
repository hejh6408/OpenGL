#pragma once
#include "Event_GeometricObject.hpp"

namespace Mario
{
	class Anim_Object : public Event_GeometricObject
	{
	public:
		Anim_Object(GeometricObject & object, const Collision * collision, float animDuration);
		~Anim_Object();

		void Texture_Change(void);
		void Draw(void);
		void Push_Texture(sf::Texture* sp);
	private:
		int _displayed_sprite;
		sf::Clock _animTimer;
		float _animDuration;
	};
}