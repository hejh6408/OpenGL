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

#define TILES_COL 8
#define TILES_ROW 11

#define ANIM_TILE_COL 4
#define ANIM_TILE_ROW 3

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

#define CAMERA_SPEED 550.0f

#define MAP_1_1_BRICK_01_HEIGHT 2
#define MAP_1_1_BRICK_01_WIDTH 70

#define MAP_1_1_BRICK_01_ROW 0
#define MAP_1_1_BRICK_01_COL 21

#define BOTTOM_COLLISION_THICKNESS 10.0

#define GRAVITY 350.0f

#define JUMP_SPEED 300.f
#define GRAVITY_ACCELERATION 23.f
#define WALK_ACCELERATION 15.f
#define UNIT_SIZE 32.0f

#define JUMP_DURATION 0.5f

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
	DESTROY,
	MOVE_UP,
	MOVE_DOWN
};
