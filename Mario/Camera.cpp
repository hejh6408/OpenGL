#include "Camera.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Mario
{
	Camera::Camera(GameDataRef data)
		: _data(data)
	{
		sf::Vector2f view_center(
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2
		);

		sf::Vector2f view_rect(
			SCREEN_WIDTH,
			SCREEN_HEIGHT
		);

		_view.setCenter(view_center);
		_view.setSize(view_rect);

		this->_data->window.setView(_view);
	}
	Camera::~Camera()
	{
	}

	void Camera::Set_Pos(sf::Vector2f & pos)
	{
		if (pos.x < SCREEN_WIDTH / 2)
		{// �� ���ʿ� ��ġ��, �ڷ� ���� ���̻� �̵����� ����
			return;
		}
		if (pos.x > SCREEN_WIDTH  * 6 + SCREEN_WIDTH / 2)
		{// �� ���ʿ� ��ġ��, ������ ���� ���̻� �̵����� ����
			return;
		}
			
		_view.setCenter(pos);

		this->_data->window.setView(_view);
	}
	sf::Vector2f Camera::Get_Pos()
	{
		return _view.getCenter();
	}
}