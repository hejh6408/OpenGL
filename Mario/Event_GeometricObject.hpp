#pragma once
#include "GeometricObject.hpp"
#include "DEFINITIONS.hpp"
#include <vector>
namespace Mario
{
	class Event_GeometricObject : public GeometricObject
	{
	public:
		Event_GeometricObject(GeometricObject & object, const Collision * collision);
		~Event_GeometricObject();

		Event_Number Event(const Collision* collision);
		
		void Reset_Life(void);
		void Set_Life(int);
		int Get_Life(void);
		void Push_Event(Event_Number event_number);

		void Set_EventState(Event_Number);
		Event_Number Get_EventState(void);

		void Set_Direction(int);
		int Get_Direction(void);
		
		void Set_DPos(sf::Vector2f);
		sf::Vector2f Get_DPos(void);

		void Move(sf::Vector2f);
		sf::Vector2f Get_MoveDistance(void);
		void Set_MoveDistance(sf::Vector2f);

	private:
		/****** Event_GeometricObject �� �ھ� �κ� ******/
		const Collision* _collision;
		std::vector<Event_Number> _events;
		int _life;
		Event_Number _eventState;

		/****** Event_GeometricObject �� �ӽ� ������ Ÿ�� �κ� ******/
		
		int _direction;

		/****** d_pos �� �������� ���� => Ư�� ���Ǳ����� �̵��ϰ� ******/
		sf::Vector2f _movingDistance;
		sf::Vector2f _dpos;
	};
}