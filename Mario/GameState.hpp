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

		GeometricObject* _hillPrototype;
		GeometricObject* _pipePrototype;
		GeometricObject* _stairPrototype;
		GeometricObject* _catlePrototype;
		GeometricObject* _tilePrototype;
		std::vector<GeometricObject*> _bushPrototypes;
		std::vector<GeometricObject*> _cloudPrototypes;
		
		GeometricObject* _backgrounds;

		std::vector<GeometricObject> _tiles;

		std::vector<std::vector<GeometricObject>> _no_collision_objects_arr;
		std::vector<std::vector<GeometricObject>> _collision_objects_arr;
		std::vector<std::vector<Event_GeometricObject>> _event_objects_arr;
		std::vector<std::vector<Anim_Object>> _anim_objects_arr;

		Mario* _mario;
		Camera* _camera;

		BrickWreck* _brickwreckPrototype;
		std::vector<BrickWreck> _brickWrecks;

	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		
		void Init_Object(std::string FILE_NAME, GeometricObject* protoType, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>&texture);
		void Init_Object(std::string FILE_NAME, std::vector<GeometricObject*>& protoType, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>&texture);
		void Init_Object(std::string FILE_NAME, std::vector<GeometricObject>& object_arr, std::vector<sf::Texture>&texture);
		
		sf::Sprite Load_Sprite(sf::Texture& texture, sf::IntRect);

		const Collision* Handle_Collsion(GeometricObject& obj,bool& flag);
		void _brickDestroy(int& , int& );
		void _brickMoveUp(int&, int&);
		void _brickMoveDown(int&, int&);

		void  _questionDestroy(int&, int&);
		void  _questionBoxMoveUp(int&, int&);
		void  _questionBoxMoveDown(int&, int&);
	};
}