#include "Enemy.h"
#include "Player.h"
#include "DoubleBuffer.h"
#include "ObjectManager.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Texture[0] = (char*)"旨收旬";
	Texture[1] = (char*)"早XX早";
	Texture[2] = (char*)"曲收旭";

	Color = PURPLE;

	TransInfo.Position = Vector3(96.0f, 0);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);

	Active = false;

	Time = GetTickCount64();
	Key = "Enemy";
}

void Enemy::Update()
{
	if (Player::PlayerHp != EMPTYHP)	randomMove();
}

void Enemy::Render()
{
	for (int i = 0; i < 3; i++) {
		DoubleBuffer::GetInstance()->WriteBuffer(
			int(TransInfo.Position.x),
			int(TransInfo.Position.y + i),
			Texture[i],
			Color
		);
	}
}

void Enemy::Release()
{
}

void Enemy::randomMove()
{	
	if (Time + 100 * (rand() % 10 + 1) < GetTickCount64()) {
		switch (rand() % 4) {
		case DIRECTION_UP:
			TransInfo.Position.y -= ENEMY_SPEED_Y;
			if (ObjectManager::GetInstance()->enemyCollision())
				TransInfo.Position.y += ENEMY_SPEED_Y;
			break;
		case DIRECTION_RIGHT:
			TransInfo.Position.x += ENEMY_SPEED_X;
			if (ObjectManager::GetInstance()->enemyCollision())
				TransInfo.Position.x -= ENEMY_SPEED_X;
			break;
		case DIRECTION_LEFT:
			TransInfo.Position.x -= ENEMY_SPEED_X;
			if (ObjectManager::GetInstance()->enemyCollision())
				TransInfo.Position.x += ENEMY_SPEED_X;
			break;
		case DIRECTION_DOWN:
			TransInfo.Position.y += ENEMY_SPEED_Y;
			if (ObjectManager::GetInstance()->enemyCollision())
				TransInfo.Position.y -= ENEMY_SPEED_Y;
			break;
		}
		Time = GetTickCount64();
	}

}
