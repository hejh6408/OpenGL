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
		: _data(data), paused(false)
	{
		
	}

	void GameState::Init()
	{
		////////////////////////////////
		_camera = new Camera(_data);
		////////////////////////////////
		this->_data->assets.LoadTexture(
			"Game Background", 
			GAME_BACKGROUND_FILEPATH
		);

		this->_data->assets.LoadTexture(
			"Tiles",
			TILES_PATH
		);
		////////////////////////////////
		this->_data->assets.LoadTexture(
			"Mario",
			MARIO_PATH
		);
		this->_mario = new Mario(_data);
		this->_mario->Init(
			this->_data->assets.GetTexture("Mario")
		);
		////////////////////////////////

		_background.setTexture(
			this->_data->assets.GetTexture("Game Background")
		);
		////////////////////////////////
		_tileTextures = this->_data->assets.Parse_Texture(TILES_PATH, TILES_ROW, TILES_COL);
		_anim_tileTextures = this->_data->assets.Parse_Texture(ANIM_TILES_PATH, ANIM_TILE_ROW, ANIM_TILE_COL);
		_coinTextures = this->_data->assets.Parse_Texture(COIN_PATH, COIN_ROW, COIN_COL);
		_firecrackerTextures = this->_data->assets.Parse_Texture(FIRECRACKER_PATH, FIRECRACKER_ROW, FIRECRACKER_COL);
		_flowerTextures = this->_data->assets.Parse_Texture(FLOWER_PATH, FLOWER_ROW, FLOWER_COL);
		_starTextures = this->_data->assets.Parse_Texture(STAR_PATH, STAR_ROW, STAR_COL);
		////////////////////////////////

		// 게임 배경 이미지 1 행 7 열로 설정.
		_backgrounds = new GeometricObject(_data);

		_backgrounds->Init(
			this->_data->assets.GetTexture("Game Background"),
			1, 7
		);
		////////////////////////////////

		{	
			/*
			파이프 오브젝트
			언덕 오브젝트
			bush 오브젝트
			cloud 오브젝트
			계단 오브젝트
			catle 오브젝트
			*/
			Init_Object(MAP_1_1_PIPE_PATH, _pipePrototype, _collision_objects_arr, _tileTextures);

			Init_Object(MAP_1_1_HILL_PATH, _hillPrototype, _no_collision_objects_arr, _tileTextures);
			
			Init_Object(MAP_1_1_BUSH_PATH, _bushPrototypes, _no_collision_objects_arr, _tileTextures);

			Init_Object(MAP_1_1_CLOUD_PATH, _cloudPrototypes, _no_collision_objects_arr, _tileTextures);

			Init_Object(MAP_1_1_STAIR_PATH, _stairPrototype, _collision_objects_arr, _tileTextures);

			Init_Object(MAP_1_1_CATLE_PATH, _catlePrototype, _no_collision_objects_arr, _tileTextures);
		}
		{
			/*
			이벤트 오브젝트
			벽돌 오브젝트
			*/
			std::vector<GeometricObject> arr;
			Init_Object(MAP_1_1_BRICK_PATH, arr, _tileTextures);

			sf::Vector2f dpos(0, -10.f);
			for (auto& obj : arr)
			{
				Event_GeometricObject event_obj(obj, this->_mario->Get_Head_Collision_Ref());
				event_obj.Push_Event(Event_Number::SPAWN_BRICK_WRECK);
				
				event_obj.Push_Event(Event_Number::TOGGLE);
				
				event_obj.Set_DPos(dpos);

				_event_objects_arr.push_back(event_obj);
			}			
		}
		{
			
			Init_Object(MAP_1_1_TILE_PATH, _collision_objects_arr, _tileTextures);
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
			파도
			*/
			{
				std::vector<GeometricObject> arr;
				Init_Object(MAP_1_1_ANIM_TILE_PATH, arr, _anim_tileTextures);

				sf::Vector2f dpos(0, -10.f);
				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Head_Collision_Ref(), 0.05);
					/*
					FLOWER 나 MUSHROOM 이 소환 되거나 모든 COIN 을 SPAWN 하면 자동적으로 METAL_BOX 를 소환한다.
					anim_obj.Push_Event(Event_Number::SPAWN_METAL_BOX);
					*/
					/*
					anim_obj.Push_Event(Event_Number::SPAWN_METAL_BOX);
					*/

					anim_obj.Push_Event(Event_Number::SPAWN_FLOWER);
					anim_obj.Push_Event(Event_Number::SPAWN_COIN);
					anim_obj.Set_DPos(dpos);

					anim_obj.Push_Texture(&_anim_tileTextures[1]);
					anim_obj.Push_Texture(&_anim_tileTextures[2]);
					anim_obj.Push_Texture(&_anim_tileTextures[3]);
					_anim_objects_arr.push_back(anim_obj);
				}
			}
			{
				std::vector<GeometricObject> arr;
				Init_Object(MAP_1_1_MAGMA_PATH, arr, _anim_tileTextures);

				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Head_Collision_Ref(), 0.2);

					anim_obj.Push_Texture(&_anim_tileTextures[9]);
					anim_obj.Push_Texture(&_anim_tileTextures[10]);
					anim_obj.Push_Texture(&_anim_tileTextures[11]);
					
					anim_obj.GeometricObject::Move(sf::Vector2f(0, -UNIT_SIZE * 0.5f));
					_anim_objects_arr.push_back(anim_obj);
				}
			}
			{
				std::vector<GeometricObject> arr;
				Init_Object(MAP_1_1_WAVE_PATH, arr, _anim_tileTextures);

				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Head_Collision_Ref(), 0.2);

					anim_obj.Push_Texture(&_anim_tileTextures[5]);
					anim_obj.Push_Texture(&_anim_tileTextures[6]);
					anim_obj.Push_Texture(&_anim_tileTextures[7]);

					anim_obj.GeometricObject::Move(sf::Vector2f(0, -UNIT_SIZE * 0.5f));
					_anim_objects_arr.push_back(anim_obj);
				}
			}
		}
		{
			{
				GeometricObject obj(_data);
				obj.Init(_coinTextures[0], 1, 1);
				_coinPrototype = new Anim_Object(obj, _mario->Get_Body_Collision_Ref(), 0.15);
				_coinPrototype->Push_Texture(&_coinTextures[1]);
				_coinPrototype->Push_Texture(&_coinTextures[2]);
				_coinPrototype->Push_Texture(&_coinTextures[3]);

				std::vector<GeometricObject> arr;
				Init_Object(MAP_1_1_COIN_PATH, arr, _coinTextures);

				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Body_Collision_Ref(), 0.15);

					anim_obj.Push_Texture(&_coinTextures[1]);
					anim_obj.Push_Texture(&_coinTextures[2]);
					anim_obj.Push_Texture(&_coinTextures[3]);

					anim_obj.Push_Event(Event_Number::SPAWN_FIRECRACKER);
					
					_item_object_arr.push_back(anim_obj);
				}
			}
			{
				GeometricObject obj(_data);
				obj.Init(_firecrackerTextures[0], 1, 1);
				_firecrackerPrototype = new Anim_Object(obj, _mario->Get_Body_Collision_Ref(), 0.3);
				_firecrackerPrototype->Push_Texture(&_firecrackerTextures[1]);
				_firecrackerPrototype->Push_Texture(&_firecrackerTextures[2]);
				_firecrackerPrototype->Push_Texture(&_firecrackerTextures[3]);
				_firecrackerPrototype->Push_Texture(&_firecrackerTextures[4]);
			}
			
			{
				/*std::vector<GeometricObject> arr;
				std::vector<Anim_Object> flower;
				Init_Object(MAP_1_1_FLOWER_PATH, arr, _flowerTextures);

				for(auto& obj: arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Body_Collision_Ref(), 0.15);

					anim_obj.Push_Texture(&_flowerTextures[1]);
					anim_obj.Push_Texture(&_flowerTextures[2]);

					anim_obj.Push_Event(Event_Number::DESTROY);

					flower.push_back(anim_obj);
				}
				_item_objects_arr.push_back(flower);*/

				GeometricObject obj(_data);
				obj.Init(_flowerTextures[0], 1, 1);
				_flowerPrototype = new Anim_Object(obj, _mario->Get_Body_Collision_Ref(), 0.1);
				_flowerPrototype->Push_Texture(&_flowerTextures[1]);
				_flowerPrototype->Push_Texture(&_flowerTextures[2]);
				_flowerPrototype->Set_Pos(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));				
			}
			{
				/*std::vector<GeometricObject> arr;
				std::vector<Anim_Object> star;
				Init_Object(MAP_1_1_STAR_PATH, arr, _starTextures);

				for (auto& obj : arr)
				{
					Anim_Object anim_obj(obj, this->_mario->Get_Body_Collision_Ref(), 0.1);

					anim_obj.Push_Texture(&_starTextures[1]);
					anim_obj.Push_Texture(&_starTextures[2]);

					anim_obj.Push_Event(Event_Number::DESTROY);

					star.push_back(anim_obj);
				}
				_item_objects_arr.push_back(star);*/

				GeometricObject obj(_data);
				obj.Init(_starTextures[0], 1, 1);
				_starPrototype = new Anim_Object(obj, _mario->Get_Body_Collision_Ref(), 0.1);
				_starPrototype->Push_Texture(&_starTextures[1]);
				_starPrototype->Push_Texture(&_starTextures[2]);
				_starPrototype->Set_Pos(sf::Vector2f(SCREEN_WIDTH / 2 + UNIT_SIZE, SCREEN_HEIGHT / 2));
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
					this->_mario->Set_Jump(true);
				}
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::P)
			{
				paused = true;
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::O)
			{
				paused = false;
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
		if(paused)
		{
			return;
		}
		{	// Camera Position Update
			sf::Vector2f pos(this->_mario->Get_Pos().x, this->_camera->Get_Pos().y);

			this->_camera->Set_Pos(pos);
		}
		
		{	// 장애물 충돌 및 낙하 혹은 점프 구현.
			bool flag = false;

			for (auto & obj : _collision_objects_arr)
			{
				Handle_Collsion(obj, flag);
			}

			for (auto & obj : _event_objects_arr)
			{
				const Collision* collision_part = Handle_Collsion(obj, flag);

				obj.Event(collision_part);
			}

			for (auto & obj : _anim_objects_arr)
			{
				const Collision* collision_part = Handle_Collsion(obj, flag);

				obj.Event(collision_part);
			}

			// flag == false 라면, bottom collision 과 겹치는 것은 아무것도 없고, 따라서 떨어지는 상태가 된다.
			if(_mario->Get_UpDown() <= 0)
			{
				if (flag == false)
				{
					this->_mario->Set_UpDown(-1);
				}
				else
				{
					this->_mario->Set_Jump(false);
				}
			}
		}
		{	
			for (int j = 0; j < _event_objects_arr.size(); j++)
			{
				auto& obj = _event_objects_arr[j];
				Event_Number event_number = obj.Get_EventState();
		
				switch (event_number)
				{
				case Event_Number::SPAWN_BRICK_WRECK:
					this->_spawn_BrickWreck(obj.Get_Pos());
				case Event_Number::DELETE:
					_event_objects_arr.erase(_event_objects_arr.begin() + j);
					j--;
					continue;
				case Event_Number::TOGGLE:
					_object_toggle(obj, dt);
					continue;
				default:
					continue;
				}
			}
			
			for (int j = 0; j < _anim_objects_arr.size(); j++)
			{
				auto & obj = _anim_objects_arr[j];
				Event_Number event_number = obj.Get_EventState();
				obj.Update(dt);

				switch (event_number)
				{
				case Event_Number::SPAWN_COIN:
					_spawn_Coin(obj.Get_Pos());
					obj.Set_EventState(Event_Number::TOGGLE);
					continue;
				case Event_Number::SPAWN_FLOWER:
					_spawn_Flower(obj.Get_Pos());
					obj.Set_EventState(Event_Number::SPAWN_METAL_BOX);
					continue;
				case Event_Number::TOGGLE:
					_object_toggle(obj, dt);
					continue;
				case Event_Number::SPAWN_METAL_BOX:
					this->_spawn_MetalBox(obj.Get_Pos());
				case Event_Number::DELETE:
					_anim_objects_arr.erase(_anim_objects_arr.begin() + j);
					j--;
					continue;
				default:
					continue;
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

		for (int i = 0; i < _item_object_arr.size(); i++)
		{
			auto & obj = _item_object_arr[i];
			obj.Update(dt);
			const Collision* collision = Handle_Item(obj);
			Event_Number event_number = obj.Event(collision);
			event_number = obj.Get_EventState();
			if (obj.Get_Num_DrawCycle() == 0)
			{
				event_number = Event_Number::DELETE;
			}

			switch (event_number)
			{
			case Event_Number::MOVE:
				if(!_object_move(obj, dt))
				{
					obj.Set_EventState(Event_Number::NONE);
				}
				continue;
			case Event_Number::SPAWN_FIRECRACKER:
				_spawn_FireCracker(
					sf::Vector2f(obj.Get_Pos().x + obj.Get_Size().x / 2, obj.Get_Pos().y)
				);
			case Event_Number::DELETE:
				_item_object_arr.erase(_item_object_arr.begin() + i);
				i--;
				continue;
			case Event_Number::MOVE_AND_SPAWN_FIRECRACKER:
				if (!_object_move(obj, dt))
				{
					obj.Set_EventState(Event_Number::SPAWN_FIRECRACKER);
				}
				continue;
			default:
				break;
			}
		}
		_starPrototype->Update(dt);
		_flowerPrototype->Update(dt);
		this->_mario->Update(dt);
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_backgrounds->Draw();

		// 나중에 그리는 obj 일수록 화면의 앞에 그려지는 우선순위가 높다.

		for (auto & obj : _no_collision_objects_arr)
		{
			obj.Draw();
		}
		for (auto & obj : _collision_objects_arr)
		{
			obj.Draw();
		}
		for (auto & obj : _item_object_arr)
		{
			obj.Draw();
		}
		for (auto & obj : _event_objects_arr)
		{
			obj.Draw();
		}
		for (auto & obj : _anim_objects_arr)
		{
			obj.Draw();
		}
		for (auto & obj : _brickWrecks)
		{
			obj.Draw();
		}
		_flowerPrototype->Draw();
		_starPrototype->Draw();

		this->_mario->Draw();
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

	const Collision * GameState::Handle_Collsion(GeometricObject& obj, bool& flag)
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

			}
			if ((this->_mario->Get_Move() == MarioState::MOVE_RIGHT) &&
				(obj_pos.x > mario_pos.x))
			{
				this->_mario->Set_Move(MarioState::STOP_RIGHT);
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

				_mario->Move(sf::Vector2f(0, dh / 2));
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
	const Collision * GameState::Handle_Item(GeometricObject & obj)
	{
		const Collision * ret = nullptr;

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

		if (is_bottom_collision || is_body_collision || is_head_collision)
		{
			ret = this->_mario->Get_Body_Collision_Ref();
		}

		return ret;
	}
	bool GameState::_object_toggle(Event_GeometricObject & obj, float dt)
	{
		bool ret = false;
		if (DIRECTION_NONE == obj.Get_Direction())
		{
			obj.Set_Direction(DIRECTION_NORTH);
		}
		else
		{
			if (!_object_move(obj, dt))
			{
				sf::Vector2f dpos(obj.Get_DPos());
				dpos = -dpos;
				obj.Set_DPos(dpos);
				obj.Set_MoveDistance(sf::Vector2f(0, 0));
				if ((DIRECTION_NORTH & obj.Get_Direction()))
				{
					obj.Set_Direction(DIRECTION_SOUTH);
				}
				else
				{
					obj.Set_EventState(Event_Number::NONE);
					obj.Set_Direction(DIRECTION_NONE);

					ret = true;
				}
			}
		}
		return ret;
	}
	bool GameState::_object_move(Event_GeometricObject & obj, float dt)
	{
		sf::Vector2f dpos(obj.Get_DPos()), dist(obj.Get_MoveDistance());
		bool ret;
		if (std::sqrtf(dist.x * dist.x + dist.y * dist.y) + std::sqrtf(dpos.x * dpos.x + dpos.y * dpos.y) * (float)0.1 < std::sqrtf(dpos.x * dpos.x + dpos.y * dpos.y) * 0.99)
		{
			obj.Move(dpos * (float)0.1);
			ret = true;
		}
		else
		{
			obj.Move(dpos - dist);
			ret = false;
		}
		return ret;
	}

	void GameState::_spawn_BrickWreck(sf::Vector2f pos)
	{
		BrickWreck wreck_01(*_brickwreckPrototype);
		wreck_01.Set_Pos(pos);
		wreck_01.Set_Velocity(
			sf::Vector2f(-100.f, -JUMP_SPEED * 1.8)
		);
		_brickWrecks.push_back(wreck_01);

		BrickWreck wreck_02(*_brickwreckPrototype);
		wreck_02.Set_Pos(pos + sf::Vector2f(UNIT_SIZE / 2, 0));
		wreck_02.Set_Velocity(
			sf::Vector2f(100.f, -JUMP_SPEED * 1.8)
		);
		_brickWrecks.push_back(wreck_02);

		BrickWreck wreck_03(*_brickwreckPrototype);
		wreck_03.Set_Pos(pos + sf::Vector2f(0, UNIT_SIZE / 2));
		wreck_03.Set_Velocity(
			sf::Vector2f(-100.f, -JUMP_SPEED * 1.3)
		);
		_brickWrecks.push_back(wreck_03);

		BrickWreck wreck_04(*_brickwreckPrototype);
		wreck_04.Set_Pos(pos + sf::Vector2f(UNIT_SIZE / 2, UNIT_SIZE / 2));
		wreck_04.Set_Velocity(
			sf::Vector2f(100.f, -JUMP_SPEED * 1.3)
		);
		_brickWrecks.push_back(wreck_04);
	}
	void GameState::_spawn_MetalBox(sf::Vector2f pos)
	{
		GeometricObject t(this->_data);
		t.Init(_tileTextures[8], 1, 1);

		Event_GeometricObject obj(t, this->_mario->Get_Head_Collision_Ref());
		obj.Set_Pos(pos);
		sf::Vector2f dpos(0, -10.f);
		obj.Set_DPos(dpos);
		obj.Set_EventState(Event_Number::TOGGLE);
		_event_objects_arr.push_back(obj);
	}
	void GameState::_spawn_FireCracker(sf::Vector2f pos)
	{
		Anim_Object obj(*_firecrackerPrototype);

		obj.Set_Pos(
			sf::Vector2f(pos.x - obj.Get_Size().x / 2, pos.y)
		);
		obj.Set_Num_DrawCycle(1);
		obj.Push_Event(Event_Number::NONE);
		_item_object_arr.push_back(obj);
	}
	void GameState::_spawn_Coin(sf::Vector2f pos)
	{
		Anim_Object obj(*_coinPrototype);

		obj.Set_Pos(
			pos
		);
		obj.Set_DPos(
			sf::Vector2f(0, -UNIT_SIZE * 2.5)
		);
		obj.Set_EventState(Event_Number::MOVE_AND_SPAWN_FIRECRACKER);
		_item_object_arr.push_back(obj);
	}
	void GameState::_spawn_Flower(sf::Vector2f pos)
	{
		Anim_Object obj(*_flowerPrototype);

		obj.Set_Pos(
			pos
		);
		obj.Set_DPos(
			sf::Vector2f(0, -UNIT_SIZE)
		);
		obj.Push_Event(Event_Number::SPAWN_FIRECRACKER);
		obj.Set_EventState(Event_Number::MOVE);
		_item_object_arr.push_back(obj);
	}
}