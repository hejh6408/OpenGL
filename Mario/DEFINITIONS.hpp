#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

#define SPLASH_STATE_SHOW_TIME 1.0

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/sky.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/sky.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/sky.png"

#define GAME_TITLE_FILEPATH "Resources/res/title.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"

#define TILES_PATH "Resources/res/Tiles.png"
#define MARIO_PATH "Resources/res/Mario.png"
#define ANIM_TILES_PATH  "Resources/res/AnimTiles.png"
#define COIN_PATH "Resources/res/coin.png"
#define FIRECRACKER_PATH "Resources/res/Firecracker.png"
#define FLOWER_PATH "Resources/res/Flower.png"
#define STAR_PATH "Resources/res/Star.png"

#define TILES_COL 8
#define TILES_ROW 11

#define ANIM_TILE_COL 4
#define ANIM_TILE_ROW 3

#define COIN_ROW  1
#define COIN_COL  4

#define FIRECRACKER_ROW 1
#define FIRECRACKER_COL 5

#define FLOWER_ROW 1
#define FLOWER_COL 3

#define STAR_ROW 1
#define STAR_COL 3

#define MAP_1_1_PATH "Resources/map/map 1-1.txt"
#define MAP_1_1_PIPE_PATH "Resources/map/map 1-1 pipe.txt"
#define MAP_1_1_HILL_PATH "Resources/map/map 1-1 hill.txt"
#define MAP_1_1_BUSH_PATH "Resources/map/map 1-1 bush.txt"
#define MAP_1_1_CLOUD_PATH "Resources/map/map 1-1 cloud.txt"
#define MAP_1_1_STAIR_PATH "Resources/map/map 1-1 stair.txt"
#define MAP_1_1_CATLE_PATH "Resources/map/map 1-1 catle.txt"
#define MAP_1_1_TILE_PATH "Resources/map/map 1-1 tile.txt"
#define MAP_1_1_BRICK_PATH "Resources/map/map 1-1 brick.txt"
#define MAP_1_1_ANIM_TILE_PATH "Resources/map/map 1-1 anim tile.txt"
#define MAP_1_1_MAGMA_PATH "Resources/map/map 1-1 magma.txt"
#define MAP_1_1_WAVE_PATH "Resources/map/map 1-1 wave.txt"
#define MAP_1_1_COIN_PATH "Resources/map/map 1-1 coin.txt"
#define MAP_1_1_FLOWER_PATH "Resources/map/map 1-1 flower.txt"
#define MAP_1_1_STAR_PATH "Resources/map/map 1-1 star.txt"

#define CAMERA_SPEED 550.0f

#define MAP_1_1_BRICK_01_HEIGHT 2
#define MAP_1_1_BRICK_01_WIDTH 70

#define MAP_1_1_BRICK_01_ROW 0
#define MAP_1_1_BRICK_01_COL 21

#define BOTTOM_COLLISION_THICKNESS 10.0

#define GRAVITY 350.0f

#define JUMP_SPEED 300.f
#define GRAVITY_ACCELERATION 23.f
#define WALK_ACCELERATION 8.f
#define UNIT_SIZE 32.0f

#define BRICK_SPEED 100.0f

#define DIRECTION_NONE 0
#define DIRECTION_NORTH (1 << 0)
#define DIRECTION_EAST (1 << 1)
#define DIRECTION_SOUTH (1 << 2)
#define DIRECTION_WEST	(1 << 3)
enum MarioState
{
	MOVE_LEFT,
	MOVE_RIGHT,
	STOP_LEFT,
	STOP_RIGHT
};
enum Event_Number
{
	NONE,
	DELETE,
	MOVE,
	SPAWN_METAL_BOX,
	SPAWN_BRICK_WRECK,
	SPAWN_FIRECRACKER,
	SPAWN_FLOWER,
	SPAWN_STAR,
	SPAWN_COIN,
	TOGGLE,
	MOVE_AND_SPAWN_FIRECRACKER
};