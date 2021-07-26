#include "Explosion.h"
#include "DoubleBuffer.h"
#include "CollisionManager.h"
#include "ObjectManager.h"

Explosion::Explosion()
{
}

Explosion::~Explosion()
{
}

void Explosion::Initialize()
{
	Texture[0] = (char*)"££££££";
	Texture[1] = (char*)"££££££";
	Texture[2] = (char*)"££££££";
	
	Color = PINK;
	Explosion_Power_Cnt = 0;
	Explosion_Direction = DIRECTION_UP;
	Explosion_Weight = 1;
	Boss_Explosion = false;

	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);

	Active = false;
}

void Explosion::Update()
{
	switch (Explosion_Direction) {
	case DIRECTION_UP:
		TransInfo.Position.y -= EXPLOSION_SPEED_Y;
		if (ObjectManager::GetInstance()->explosionRange(DIRECTION_UP)) {
			TransInfo.Position.y += EXPLOSION_SPEED_Y;
			Active = false;
		}
		break;
	case DIRECTION_RIGHT:
		TransInfo.Position.x += EXPLOSION_SPEED_X;
		if (ObjectManager::GetInstance()->explosionRange(DIRECTION_RIGHT)) {
			TransInfo.Position.y -= EXPLOSION_SPEED_X;
			Active = false;
		}
		break;
	case DIRECTION_LEFT:
		TransInfo.Position.x -= EXPLOSION_SPEED_X;
		if (ObjectManager::GetInstance()->explosionRange(DIRECTION_LEFT)) {
			TransInfo.Position.y += EXPLOSION_SPEED_X;
			Active = false;
		}
		break;
	case DIRECTION_DOWN:
		TransInfo.Position.y += EXPLOSION_SPEED_Y;
		if (ObjectManager::GetInstance()->explosionRange(DIRECTION_DOWN)) {
			TransInfo.Position.y -= EXPLOSION_SPEED_Y;
			Active = false;
		}
		break;
	}
	Explosion_Power_Cnt++;
	if (!Boss_Explosion && Explosion_Power_Cnt > EXPLOSION_RANGE * Explosion_Weight) {
		Active = false;
	}
}

void Explosion::Render()
{
	if (Boss_Explosion) {
		for (int i = 0; i < 3; i++)
		{
			DoubleBuffer::GetInstance()->WriteBuffer(
				TransInfo.Position.x,
				TransInfo.Position.y + i,
				Texture[i],
				ORANGE
			);
		}
	}
	else {
		for (int i = 0; i < 3; i++)
		{
			DoubleBuffer::GetInstance()->WriteBuffer(
				TransInfo.Position.x,
				TransInfo.Position.y + i,
				Texture[i],
				Color
			);
		}
	}	
}

void Explosion::Release()
{
}
