#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
namespace Mario
{
	GameState::GameState(GameDataRef data) 
		: _data(data)
	{
		
	}

	Event_Number destroy(void)
	{
		return Event_Number::DESTROY;
	}
	Event_Number move_up(void)
	{
		return Event_Number::MOVE_UP;
	}

	void GameState::Init()
	{
		{
			_camera = new Camera(_data);
		}

		this->_data->assets.LoadTexture(
			"Game Background", 
			GAME_BACKGROUND_FILEPATH
		);

		this->_data->assets.LoadTexture(
			"Tiles",
			TILES_PATH
		);

		{
			this->_data->assets.LoadTexture(
				"Mario",
				MARIO_PATH
			);

			this->_mario = new Mario(_data);
			this->_mario->Init(
				this->_data->assets.GetTexture("Mario")
			);
		}
		

		_background.setTexture(
			this->_data->assets.GetTexture("Game Background")
		);

		_tileTextures = this->_data->assets.Parse_Texture(TILES_PATH, TILES_ROW, TILES_COL);
		
		_anim_tileTextures = this->_data->assets.Parse_Texture(ANIM_TILES_PATH, ANIM_TILE_ROW, ANIM_TILE_COL);
		{	// 게임 배경 이미지 1 행 7 열로 설정.
			_backgrounds = new GeometricObject(_data);
			
			_backgrounds->Init(
				this->_data->assets.GetTexture("Game Background"), 
				1, 7
			);
		}
		{	
			/*
			파이프 오브젝트
			언덕 오브젝트
			bush 오브젝트
			cloud 오브젝트
			계단 오브젝트
			catle 오브젝트
			*/
			_collision_objects_arr.push_back(std::vector<GeometricObject>());
			Init_Object(MAP_1_1_PIPE_PATH, _pipePrototype, _collision_objects_arr.back(), _tileTextures);

			_no_collision_objects_arr.push_back(std::vector<GeometricObject>());
			Init_Object(MAP_1_1_HILL_PATH, _hillPrototype, _no_collision_objects_arr.back(), _tileTextures);
			
			_no_collision_objects_arr.push_back(std::vector<GeometricObject>());
			Init_Object(MAP_1_1_BUSH_PATH, _bushPrototypes, _no_collision_objects_arr.back(), _tileTextures);

			_no_collision_objects_arr.push_back(std::vector<GeometricObject>());
			Init_Object(MAP_1_1_CLOUD_PATH, _cloudPrototypes, _no_collision_objects_arr.back(), _tileTextures);

			_collision_objects_arr.push_back(std::vector<GeometricObject>());
			Init_Object(MAP_1_1_STAIR_PATH, _stairPrototype, _collision_objects_arr.back(), _tileTextures);

			_no_collision_objects_arr.push_back(std::vector<GeometricObject>());
			Init_Object(MAP_1_1_CATLE_PATH, _catlePrototype, _no_collision_objects_arr.back(), _tileTextures);
		}
		{
			/*
			이벤트 오브젝트
			벽돌 오브젝트
			*/
			std::vector<GeometricObject> arr;
			std::vector<Event_GeometricObject> bricks;
			Init_Object(MAP_1_1_BRICK_PATH, arr, _tileTextures);

			sf::FloatRect border(sf::Vector2f(-10, -10), sf::Vector2f(20, 20));
			for (auto& obj : arr)
			{
				Event_GeometricObject event_obj(obj, this->_mario->Get_Head_Collision_Ref());

				event_obj.Push_Event(destroy);
				event_obj.Push_Event(move_up);
				event_obj.Set_Border(border);
				bricks.push_back(event_obj);
			}
			_event_objects_arr.push_back(bricks);
			
		}
		{
			_collision_objects_arr.push_back(std::vector<GeometricObject>());
			
			Init_Object(MAP_1_1_TILE_PATH, _collision_objects_arr.back(), _tileTextures);
		}

		{
			_brickwreckPrototype = new BrickWreck(this->_data, _tileTextures[1], _tileTextures[1].getSize().x / 4);
		}

		{
			/*
			GeometricObject ttt(_data);
			ttt.Init(_anim_tileTextures[0], 1, 1);
			
			_questionboxPrototype = new Anim_Object(ttt, this->_mario->Get_Head_Collision_Ref(), 0.1);

			_questionboxPrototype->Push_Texture(&_anim_tileTextures[0]);
			_questionboxPrototype->Push_Texture(&_anim_tileTextures[1]);
			_questionboxPrototype->Push_Texture(&_anim_tileTextures[2]);
			_questionboxPrototype->Push_Texture(&_anim_tileTextures[3]);

			_questionboxPrototype->Set_Pos(sf::Vector2f(0, 0));

			물음표 상자
			마그마
			*/
			{
				std::vector<GeometricObject> arr;
				std::vector<Anim_Object> question_boxs;
				Init_Object(MAP_1_1_ANIM_TILE_PATH, arr, _anim_tileTextures);

				sf::FloatRect border(sf::Vector2f(-10, -10), sf::Vector2f(20, 20));
				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Head_Collision_Ref(), 0.05);

					anim_obj.Push_Event(destroy);
					anim_obj.Push_Event(move_up);
					anim_obj.Push_Event(move_up);
					anim_obj.Set_Border(border);

					anim_obj.Push_Texture(&_anim_tileTextures[1]);
					anim_obj.Push_Texture(&_anim_tileTextures[2]);
					anim_obj.Push_Texture(&_anim_tileTextures[3]);
					question_boxs.push_back(anim_obj);
				}
				_anim_objects_arr.push_back(question_boxs);
			}
			{
				std::vector<GeometricObject> arr;
				std::vector<Anim_Object> magma;
				Init_Object(MAP_1_1_MAGMA_PATH, arr, _anim_tileTextures);

				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Head_Collision_Ref(), 0.2);

					anim_obj.Push_Texture(&_anim_tileTextures[9]);
					anim_obj.Push_Texture(&_anim_tileTextures[10]);
					anim_obj.Push_Texture(&_anim_tileTextures[11]);
					
					anim_obj.GeometricObject::Move(sf::Vector2f(0, -UNIT_SIZE * 0.5f));
					magma.push_back(anim_obj);
				}
				_anim_objects_arr.push_back(magma);
			}
			{
				std::vector<GeometricObject> arr;
				std::vector<Anim_Object> wave;
				Init_Object(MAP_1_1_WAVE_PATH, arr, _anim_tileTextures);

				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Head_Collision_Ref(), 0.2);

					anim_obj.Push_Texture(&_anim_tileTextures[5]);
					anim_obj.Push_Texture(&_anim_tileTextures[6]);
					anim_obj.Push_Texture(&_anim_tileTextures[7]);

					anim_obj.GeometricObject::Move(sf::Vector2f(0, -UNIT_SIZE * 0.5f));
					wave.push_back(anim_obj);
				}
				_anim_objects_arr.push_back(wave);
			}
		}
	}

	void GameState::HandleInput()
	{
		sf::Event event;
		
		
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Right)
			{
				this->_mario->Set_Move(MarioState::STOP_RIGHT);

				
				this->_mario->Set_Velocity(
					sf::Vector2f(0, _mario->Get_Velocity().y)
				);
			}
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Left)
			{
				this->_mario->Set_Move(MarioState::STOP_LEFT);

				this->_mario->Set_Velocity(
					sf::Vector2f(0, _mario->Get_Velocity().y)
				);
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				if (this->_mario->Get_UpDown() == 0) 
				{
					this->_mario->Set_UpDown(2);

				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->_mario->Set_Move(MarioState::MOVE_RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->_mario->Set_Move(MarioState::MOVE_LEFT);
		}
	}

	void GameState::Update(float dt)
	{
		{	// Camera Position Update
			sf::Vector2f pos(this->_mario->Get_Pos().x, this->_camera->Get_Pos().y);

			this->_camera->Set_Pos(pos);
		}
		
		{	// 장애물 충돌 및 낙하 혹은 점프 구현.
			bool flag = false;

			for (auto & object_arr : _collision_objects_arr)
			{
				for (auto & obj : object_arr)
				{
					Handle_Collsion(obj, flag);
				}
			}

			for (auto & object_arr : _event_objects_arr)
			{
				for (auto & obj : object_arr)
				{
					const Collision* collision_part = Handle_Collsion(obj, flag);

					Event_Number func_number = obj.Event(collision_part);
				}
			}

			for (auto & object_arr : _anim_objects_arr)
			{
				for (auto & obj : object_arr)
				{
					const Collision* collision_part = Handle_Collsion(obj, flag);

					Event_Number func_number = obj.Event(collision_part);
				}
			}

			// flag == false 라면, bottom collision 과 겹치는 것은 아무것도 없고, 따라서 떨어지는 상태가 된다.
			if (flag == false && _mario->Get_UpDown() <= 0)
			{
				this->_mario->Set_UpDown(-1);
			}
		}
		{	// Event_Object 들의 이벤트 구현;
			for (int i = 0; i < _event_objects_arr.size(); i++)
			{
				for (int j = 0; j < _event_objects_arr[i].size(); j++)
				{
					Event_Number func_number = _event_objects_arr[i][j].Get_EventState();

					switch (func_number)
					{
					case Event_Number::DESTROY:
						this->_brickDestroy(i, j);
						continue;
					case Event_Number::MOVE_UP:
						this->_brickMoveUp(i, j);
						continue;
					case Event_Number::MOVE_DOWN:
						this->_brickMoveDown(i, j);
						continue;

					default:
						continue;
					}
				}
			}
			for (int i = 0; i < _anim_objects_arr.size(); i++)
			{
				for (int j = 0; j < _anim_objects_arr[i].size(); j++)
				{
					Event_Number func_number = _anim_objects_arr[i][j].Get_EventState();

					switch (func_number)
					{
					case Event_Number::DESTROY:
						this->_questionDestroy(i, j);
						continue;
					case Event_Number::MOVE_UP:
						this->_questionBoxMoveUp(i, j);
						continue;
					case Event_Number::MOVE_DOWN:
						this->_questionBoxMoveDown(i, j);
						continue;

					default:
						continue;
					}
				}
			}
		}
		for(int i = 0; i < _brickWrecks.size(); i++)
		{
			auto & obj = _brickWrecks[i];
		
			if (obj.Get_Clock().getElapsedTime().asSeconds() > 2.0f) 
			{
				_brickWrecks.erase(_brickWrecks.begin() + i);
				i--;
			}
			else
			{
				obj.Update(dt);
			}
		}

		this->_mario->Update(dt);
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_backgrounds->Draw();

		// 나중에 그리는 obj 일수록 화면의 앞에 그려지는 우선순위가 높다.

		for(auto & object_arr : _no_collision_objects_arr)
		{
			for(auto & obj : object_arr)
			{
				obj.Draw();
			}
		}

		for (auto & object_arr : _collision_objects_arr)
		{
			for (auto & obj : object_arr)
			{
				obj.Draw();
			}
		}
		
		for (auto & object_arr : _event_objects_arr)
		{
			for (auto & obj : object_arr)
			{
				obj.Draw();
			}
		}
		for (auto & object_arr : _anim_objects_arr)
		{
			for (auto & obj : object_arr)
			{
				obj.Draw();
			}
		}
		for (auto & obj : _brickWrecks)
		{
			obj.Draw();
		}

		this->_mario->Draw();
		
		/*this->_questionboxPrototype->Draw();*/
		this->_data->window.display();
	}

	void GameState::Init_Object(std::string FILE_NAME, GeometricObject * protoType
		, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>& texture)
	{
		std::fstream cin(FILE_NAME);
		protoType = new GeometricObject(_data);

		int n, m, number_objects = 0;

		cin >> n >> m;

		std::vector<std::vector<int>> OBJECT_DATA(n);

		for (int i = 0; i < n; i++)
		{
			OBJECT_DATA[i].resize(m);
			for (int j = 0; j < m; j++)
			{
				cin >> OBJECT_DATA[i][j];
			}
		}

		std::vector<std::vector<sf::Texture*>> arr(OBJECT_DATA.size());

		for (int i = 0; i < OBJECT_DATA.size(); i++)
		{
			for (int j = 0; j < OBJECT_DATA[0].size(); j++)
			{
				arr[i].push_back(&texture[OBJECT_DATA[i][j]]);
			}
		}

		protoType->Init(arr);
		cin >> number_objects;

		for (int i = 0; i < number_objects; i++)
		{
			float row, col;
			cin >> col >> row;
			GeometricObject new_object(*protoType);
			new_object.Set_Pos(
				sf::Vector2f(UNIT_SIZE * (col), UNIT_SIZE * (MAP_1_1_BRICK_01_COL - row))
			);
			object_arr.push_back(new_object);
		}
	}
	
	void GameState::Init_Object(std::string FILE_NAME, std::vector<GeometricObject*>& protoTypes
		, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>& texture)
	{
		std::fstream cin(FILE_NAME);
		int number_prototypes = 0;
		
		cin >> number_prototypes;
		protoTypes.resize(number_prototypes);
		for(int k = 0; k < number_prototypes; k++)
		{
			protoTypes[k] = new GeometricObject(_data);
			int n, m;

			cin >> n >> m;

			std::vector<std::vector<int>> OBJECT_DATA(n);

			for (int i = 0; i < n; i++)
			{
				OBJECT_DATA[i].resize(m);
				for (int j = 0; j < m; j++)
				{
					cin >> OBJECT_DATA[i][j];
				}
			}

			std::vector<std::vector<sf::Texture*>> arr(OBJECT_DATA.size());
			for (int i = 0; i < OBJECT_DATA.size(); i++)
			{
				for (int j = 0; j < OBJECT_DATA[0].size(); j++)
				{
					arr[i].push_back(&texture[OBJECT_DATA[i][j]]);
				}
			}
			protoTypes[k]->Init(arr);
		}

		int number_objects = 0;
		cin >> number_objects;

		for (int k = 0; k < number_objects; k++)
		{
			float row, col, prototype_number;
			cin >> col >> row >> prototype_number;
			GeometricObject new_object(*protoTypes[prototype_number]);
			new_object.Set_Pos(
				sf::Vector2f(UNIT_SIZE * (col), UNIT_SIZE * (MAP_1_1_BRICK_01_COL - row))
			);
			object_arr.push_back(new_object);
		}
	}
	
	void GameState::Init_Object(std::string FILE_NAME, std::vector<GeometricObject>& object_arr
		, std::vector<sf::Texture>& texture)
	{
		std::fstream cin(FILE_NAME);
		
		int texture_number, number_obj;
		cin >> texture_number;
		cin >> number_obj;

		for(int i = 0; i < number_obj; i++)
		{
			int left, top, width, height;

			cin >> height >> width >> left >> top;

			GeometricObject obj(_data);
			obj.Init(texture[texture_number], height, width);
			obj.Set_Pos(
				sf::Vector2f(UNIT_SIZE * left, UNIT_SIZE * (MAP_1_1_BRICK_01_COL - top))
			);
			object_arr.push_back(obj);
		}
	}

	sf::Sprite GameState::Load_Sprite(sf::Texture& texture, sf::IntRect rect)
	{
		/*sf::Sprite* sp = new sf::Sprite(texture);*/

		sf::Sprite sp(texture);
		/*sp->setTextureRect(rect);*/
		sp.setTextureRect(rect);
		return sp;
	}
	const Collision* GameState::Handle_Collsion(GeometricObject& obj, bool& flag)
	{
		const Collision* ret = nullptr;
		Collision mario_bottom_collision(
			this->_mario->Get_Bottom_Collision()
		);
		Collision mario_body_collision(
			this->_mario->Get_Body_Collsion()
		);
		Collision mario_head_collision(
			this->_mario->Get_Head_Collsion()
		);
		Collision object_collision(
			obj.Get_Collision()
		);
		bool is_bottom_collision = mario_bottom_collision.CheckCollision(object_collision);
		bool is_body_collision = mario_body_collision.CheckCollision(object_collision);
		bool is_head_collision = mario_head_collision.CheckCollision(object_collision);

		sf::Vector2f obj_pos = obj.Get_Pos();
		if (is_body_collision)
		{
			sf::Vector2f mario_pos = this->_mario->Get_Pos();
			

			if ((this->_mario->Get_Move() == MarioState::MOVE_LEFT) &&
				(obj_pos.x < mario_pos.x))
			{
				this->_mario->Set_Move(MarioState::STOP_LEFT);

				this->_mario->Set_Velocity(
					sf::Vector2f(0, _mario->Get_Velocity().y)
				);
			}
			if ((this->_mario->Get_Move() == MarioState::MOVE_RIGHT) &&
				(obj_pos.x > mario_pos.x))
			{
				this->_mario->Set_Move(MarioState::STOP_RIGHT);

				this->_mario->Set_Velocity(
					sf::Vector2f(0, _mario->Get_Velocity().y)
				);
			}

			ret = this->_mario->Get_Body_Collision_Ref();
		}
		else if (is_bottom_collision && !is_body_collision)
		{
			if (this->_mario->Get_UpDown() <= 0)
			{
				this->_mario->Set_UpDown(0);

				flag = true;
				
				float dh = obj_pos.y - (mario_bottom_collision.Get_Pos().y + mario_bottom_collision.Get_Box().height / 2);

				if (dh < 0)
				{
					_mario->Move(sf::Vector2f(0, dh / 2));
				}
				else if (dh > 0)
				{
					_mario->Move(sf::Vector2f(0, dh / 2));
				}
			}
			ret = this->_mario->Get_Bottom_Collision_Ref();
		}

		if (is_head_collision && !is_body_collision)
		{
			this->_mario->Set_UpDown(-1);
			ret = this->_mario->Get_Head_Collision_Ref();

			this->_mario->Set_Velocity(
				sf::Vector2f(_mario->Get_Velocity().x, 0)
			);

			sf::Vector2f bottompos = (obj_pos + obj.Get_Size());
			float dh = mario_head_collision.Get_Pos().y - bottompos.y;

			if(dh < 0)
			{
				_mario->Move(sf::Vector2f(0, -dh));
			}
		}

		return ret;
	}

	void GameState::_brickDestroy(int & row, int & col)
	{
		
		Event_GeometricObject& obj = _event_objects_arr[row][col];
		
		BrickWreck wreck_01(*_brickwreckPrototype);
		wreck_01.Set_Pos(obj.Get_Pos());
		wreck_01.Set_Velocity(sf::Vector2f(-100.f, -300.f));
		_brickWrecks.push_back(wreck_01);

		BrickWreck wreck_02(*_brickwreckPrototype);
		wreck_02.Set_Pos(obj.Get_Pos() + sf::Vector2f(UNIT_SIZE / 2, 0));
		wreck_02.Set_Velocity(sf::Vector2f(100.f, -300.f));
		_brickWrecks.push_back(wreck_02);

		BrickWreck wreck_03(*_brickwreckPrototype);
		wreck_03.Set_Pos(obj.Get_Pos() + sf::Vector2f(0, UNIT_SIZE / 2));
		wreck_03.Set_Velocity(sf::Vector2f(-100.f, -200.f));
		_brickWrecks.push_back(wreck_03);

		BrickWreck wreck_04(*_brickwreckPrototype);
		wreck_04.Set_Pos(obj.Get_Pos() + sf::Vector2f(UNIT_SIZE / 2, UNIT_SIZE / 2));
		wreck_04.Set_Velocity(sf::Vector2f(100.f, -200.f));
		_brickWrecks.push_back(wreck_04);

		_event_objects_arr[row].erase(_event_objects_arr[row].begin() + col);
		col--;
	}
	void GameState::_brickMoveUp(int & row, int & col)
	{
		Event_GeometricObject& obj = _event_objects_arr[row][col];
		if (obj.Get_Direction() == DIRECTION_NONE) 
		{
			obj.Set_Direction(DIRECTION_NORTH);
			obj.Reset_Clock();
		}
		else
		{
			if((DIRECTION_NORTH & obj.Get_Direction()))
			{
				sf::Vector2f dpos(0, -BRICK_SPEED * 0.01);
				if(obj.Get_Border().contains(obj.Get_MoveDistance() + dpos))
				{
					obj.Move(dpos);
				}
				else
				{
					dpos.y = obj.Get_Border().top - obj.Get_MoveDistance().y;
					obj.Move(dpos);
					obj.Set_EventState(Event_Number::MOVE_DOWN);
					obj.Set_Direction(DIRECTION_NONE);
				}
			}
		}
	}
	void GameState::_brickMoveDown(int & row, int & col)
	{
		Event_GeometricObject& obj = _event_objects_arr[row][col];
		if (obj.Get_Direction() == DIRECTION_NONE)
		{
			obj.Set_Direction(DIRECTION_SOUTH);
			obj.Reset_Clock();
		}
		else
		{
			if ((DIRECTION_SOUTH & obj.Get_Direction()))
			{
				sf::Vector2f dpos(0, + BRICK_SPEED * 0.01);
				if ((obj.Get_MoveDistance() + dpos).y < 0)
				{
					obj.Move(dpos);
				}
				else
				{
					dpos.y = -obj.Get_MoveDistance().y;
					obj.Move(dpos);
					obj.Set_EventState(Event_Number::NONE);
					obj.Set_Direction(DIRECTION_NONE);
				}
			}
		}
	}
	void GameState::_questionDestroy(int &row, int & col)
	{
		Event_GeometricObject& obj = _anim_objects_arr[row][col];
		GeometricObject t(this->_data);
		t.Init(_tileTextures[8], 1, 1);
		t.Set_Pos(obj.Get_Pos());
		std::vector<GeometricObject> v;
		v.push_back(t);
		_collision_objects_arr.push_back(v);

		_anim_objects_arr[row].erase(_anim_objects_arr[row].begin() + col);
		col--;
	}
	void GameState::_questionBoxMoveUp(int & row, int & col)
	{
		Event_GeometricObject& obj = _anim_objects_arr[row][col];
		if (obj.Get_Direction() == DIRECTION_NONE)
		{
			obj.Set_Direction(DIRECTION_NORTH);
			obj.Reset_Clock();
		}
		else
		{
			if ((DIRECTION_NORTH & obj.Get_Direction()))
			{
				sf::Vector2f dpos(0, -BRICK_SPEED * 0.01);
				if (obj.Get_Border().contains(obj.Get_MoveDistance() + dpos))
				{
					obj.Move(dpos);
				}
				else
				{
					dpos.y = obj.Get_Border().top - obj.Get_MoveDistance().y;
					obj.Move(dpos);
					obj.Set_EventState(Event_Number::MOVE_DOWN);
					obj.Set_Direction(DIRECTION_NONE);
				}
			}
		}
	}
	void GameState::_questionBoxMoveDown(int &row , int & col)
	{
		Event_GeometricObject& obj = _anim_objects_arr[row][col];
		if (obj.Get_Direction() == DIRECTION_NONE)
		{
			obj.Set_Direction(DIRECTION_SOUTH);
			obj.Reset_Clock();
		}
		else
		{
			if ((DIRECTION_SOUTH & obj.Get_Direction()))
			{
				sf::Vector2f dpos(0, +BRICK_SPEED * 0.01);
				if ((obj.Get_MoveDistance() + dpos).y < 0)
				{
					obj.Move(dpos);
				}
				else
				{
					dpos.y = -obj.Get_MoveDistance().y;
					obj.Move(dpos);
					obj.Set_EventState(Event_Number::NONE);
					obj.Set_Direction(DIRECTION_NONE);
					/*
					여기서 Q Box 가 동전이나 버섯을 내뱉는다.
					*/
				}
			}
		}
	}
}