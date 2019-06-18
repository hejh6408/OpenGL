#include "GeometricObject.hpp"
#include <SFML/Graphics.hpp>
namespace Mario
{
	GeometricObject::GeometricObject(GameDataRef data)
		:_data(data)
	{
		this->_collision = new Collision(data);
		;
	}
	GeometricObject::GeometricObject(const GeometricObject & object)
	{
		_data = object._data;
		_sprites = object._sprites;
		_pos = object._pos;
		_unitSize = object._unitSize;
		_size = object._size;
		_collision = new Collision(*(object._collision));
	}
	GeometricObject::~GeometricObject()
	{
		;
	}
	void GeometricObject::Init(sf::Texture& _texture, int _r, int _c)
	{
		{
			this->_unitSize = _texture.getSize();
			sf::Vector2f collision_box(this->_unitSize.x * _c, this->_unitSize.y * _r);
			_collision->Init(_pos, collision_box);
		}
		for(int i = 0; i < _r; i++)
		{
			for(int j = 0; j < _c; j++)
			{
				sf::Sprite sp(_texture);
			
				sp.setPosition(this->_unitSize.x * j, this->_unitSize.y * i);
				_sprites.push_back(sp);				
			}
		}

		_size.x = _unitSize.x * (_c);
		_size.y = _unitSize.y * (_r);
	}

	void GeometricObject::Init(std::vector<std::vector<sf::Texture*>> & _texture)
	{
		{
			this->_unitSize = (*_texture[0][0]).getSize();
			sf::Vector2f collision_box(this->_unitSize.x * _texture[0].size(), this->_unitSize.y * _texture.size());
			_collision->Init(_pos, collision_box);
		}

		for(int i = 0; i < _texture.size(); i++)
		{
			for(int j = 0; j < _texture[0].size(); j++)
			{
				sf::Sprite sp(*_texture[i][j]);

				sp.setPosition((_texture[i][j])->getSize().x * j, (_texture[i][j])->getSize().y * i);
				_sprites.push_back(sp);
			}
		}
		int _r = _texture.size(), _c = _texture[0].size();

		_size.x = _unitSize.x * (_c);
		_size.y = _unitSize.y * (_r);
	}

	void GeometricObject::Set_Pos(sf::Vector2f pos)
	{
		
		for(auto& sp : this->_sprites)
		{
			sf::Vector2f dpos = sp.getPosition() - _pos;
			// dpos 는 sprite 의 상대 위치
			sp.setPosition(pos + dpos);
		}
		_pos = pos;
		this->_collision->Set_Pos(pos);
	}
	sf::Vector2f GeometricObject::Get_Pos()
	{
		return _pos;
	}
	void GeometricObject::Move(sf::Vector2f _dpos)
	{
		_pos += _dpos;
		for (auto& sp : this->_sprites)
		{
			sp.move(_dpos);
		}
		this->_collision->Move(_dpos);
	}
	void GeometricObject::Draw(void)
	{
		for(auto& sp : this->_sprites)
		{
			this->_data->window.draw(sp);
		}
	}
	Collision GeometricObject::Get_Collision(void)
	{
		return Collision(*this->_collision);
	}
	void GeometricObject::Set_Collision_Pos(sf::Vector2f pos)
	{
		this->_collision->Set_Pos(pos);
	}

	sf::Vector2f GeometricObject::Get_Size(void)
	{
		return _size;
	}

	/*void GeometricObject::Move_Sprite_Rect(int n, sf::Vector2i dpos)
	{
		sf::Vector2i pos, size;
		pos.x = _sprites[n].getTextureRect().left;
		pos.y = _sprites[n].getTextureRect().top;
		size.x = _sprites[n].getTextureRect().width;
		size.y = _sprites[n].getTextureRect().height;

		_sprites[n].setTextureRect(sf::IntRect(pos + dpos, size));
	}
	void GeometricObject::Set_Sprite_Rect_Size(int n, sf::Vector2i size)
	{
		sf::Vector2i pos;
		pos.x = _sprites[n].getTextureRect().left;
		pos.y = _sprites[n].getTextureRect().top;
		
		_sprites[n].setTextureRect(sf::IntRect(pos, size));
	}
	int GeometricObject::Num_Sprite(void)
	{
		return _sprites.size();
	}*/
}
