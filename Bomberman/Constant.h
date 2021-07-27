#pragma once
const ULONG KEYID_UP		= 0x00000001;
const ULONG KEYID_DOWN		= 0x00000002;
const ULONG KEYID_LEFT		= 0x00000004;
const ULONG KEYID_RIGHT		= 0x00000008;

const ULONG KEYID_SPACE		= 0x00000010;
const ULONG KEYID_ESCAPE	= 0x00000020;
const ULONG KEYID_RETURN	= 0x00000040;

const int CONSOL_MAX_WIDTH	= 104;
const int CONSOL_MAX_HEIGHT = 52;

const float PLAYER_SPEED_X	= 2.0f;
const float PLAYER_SPEED_Y	= 1.0f;

const float ENEMY_SPEED_X = 2.0f;
const float ENEMY_SPEED_Y = 1.0f;

const float BOSS_SPEED_X = 2.0f;
const float BOSS_SPEED_Y = 1.0f; 
const float BOSS_TARGET_COEFFICIENT = 0.7f;

const float EXPLOSION_SPEED_X = 3.0f;
const float EXPLOSION_SPEED_Y = 1.5f;
const int	EXPLOSION_RANGE	  = 2;

const int BLACK		 = 0;
const int RED		 = 4;
const int ORANGE	 = 6;
const int LIGHTWHITE = 7;
const int GRAY		 = 8;
const int GREEN		 = 10;
const int PINK		 = 12;
const int PURPLE	 = 13;
const int YELLOW	 = 14;
const int WHITE		 = 15;

const float OBJ_SIZE_X = 6.0f;
const float OBJ_SIZE_Y = 3.0f;

#define GRAVITY_ACCELERATION 0.98f
#define PI 3.141592f
