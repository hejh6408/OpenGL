#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

#include "GeometricObject.hpp"
#include "Mario.hpp"
#include "Camera.hpp"
#include "Event_GeometricObject.hpp"
#include "BrickWreck.hpp"
#include "Animation_Object.hpp"

#include <vector>
namespace Mario
{
	class GameState : public State
	{ 
	private:
		GameDataRef _data;
		sf::Sprite _background;
		/*Tile* _tile;*/
		std::vector<sf::Texture> _tileTextures;
		std::vector<sf::Texture> _marioTextures;
		std::vector<sf::Texture> _anim_tileTextures;
		std::vector<sf::Texture> _coinTextures;
		std::vector<sf::Texture> _firecrackerTextures;
		std::vector<sf::Texture> _flowerTextures;
		std::vector<sf::Texture> _starTextures;

		GeometricObject* _hillPrototype;
		GeometricObject* _pipePrototype;
		GeometricObject* _stairPrototype;
		GeometricObject* _catlePrototype;
		GeometricObject* _tilePrototype;
		std::vector<GeometricObject*> _bushPrototypes;
		std::vector<GeometricObject*> _cloudPrototypes;
		
		GeometricObject* _backgrounds;

		std::vector<GeometricObject> _tiles;

		std::vector<GeometricObject> _no_collision_objects_arr;
		std::vector<GeometricObject> _collision_objects_arr;
		std::vector<Event_GeometricObject> _event_objects_arr;
		std::vector<Anim_Object> _anim_objects_arr;
		std::vector<Anim_Object> _item_object_arr;

		Mario* _mario;
		Camera* _camera;

		BrickWreck* _brickwreckPrototype;
		std::vector<BrickWreck> _brickWrecks;
		
		Anim_Object* _firecrackerPrototype;
		Anim_Object* _flowerPrototype;
		Anim_Object* _starPrototype;
		Anim_Object* _coinPrototype;

		bool paused;
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		
		void Init_Object(std::string FILE_NAME, GeometricObject* protoType, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>&texture);
		void Init_Object(std::string FILE_NAME, std::vector<GeometricObject*>& protoType, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>&texture);
		void Init_Object(std::string FILE_NAME, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>&texture);
		
		const Collision* Handle_Collsion(GeometricObject& obj,bool& flag);
		const Collision* Handle_Item(GeometricObject& obj);
		
		bool _object_toggle(Event_GeometricObject& obj,float dt);
		bool _object_move(Event_GeometricObject& obj, float dt);
		
		void _spawn_BrickWreck(sf::Vector2f);
		void _spawn_MetalBox(sf::Vector2f);
		void _spawn_FireCracker(sf::Vector2f);
		void _spawn_Coin(sf::Vector2f);
		void _spawn_Flower(sf::Vector2f);
	};
}