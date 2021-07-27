#include "Player.h"
#include "InputManager.h"
#include "DoubleBuffer.h"
#include "CollisionManager.h"
#include "ObjectManager.h"

int Player::PlayerHp = FULLHP;
Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	Texture[0] = (char*)"旨朴旬";
	Texture[1] = (char*)"早00早";
	Texture[2] = (char*)"曲收旭";
	
	Color = GREEN;
	PlayerHp = FULLHP;

	TransInfo.Position = Vector3(6.0f, 3.0f);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);
	Active = false;
	Key = "Player";
}

void Player::Update()
{
	if(PlayerHp != EMPTYHP)	CheckKey();
	State();
}

void Player::Render()
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

void Player::Release()
{
}

void Player::CheckKey()
{
	ULONG ulKey = InputManager::GetInstance()->GetKey();
	
	if (ulKey & KEYID_UP)
	{
		TransInfo.Position.y -= PLAYER_SPEED_Y;
		if(ObjectManager::GetInstance()->playerCollision())
			TransInfo.Position.y += PLAYER_SPEED_Y;
	}

	if (ulKey & KEYID_DOWN)
	{
		TransInfo.Position.y += PLAYER_SPEED_Y;
		if (ObjectManager::GetInstance()->playerCollision())
			TransInfo.Position.y -= PLAYER_SPEED_Y;
	}

	if (ulKey & KEYID_RIGHT)
	{
		TransInfo.Position.x += PLAYER_SPEED_X;
		if (ObjectManager::GetInstance()->playerCollision())
			TransInfo.Position.x -= PLAYER_SPEED_X;
	}

	if (ulKey & KEYID_LEFT)
	{
		TransInfo.Position.x -= PLAYER_SPEED_X;
		if (ObjectManager::GetInstance()->playerCollision())
			TransInfo.Position.x += PLAYER_SPEED_X;
	}
	if (ulKey & KEYID_SPACE)
	{
		ObjectManager::GetInstance()->createBomb();
	}
}

void Player::State()
{
	switch (PlayerHp)
	{
	case EMPTYHP:
		Texture[0] = (char*)"旨朴旬";
		Texture[1] = (char*)"早XX早";
		Texture[2] = (char*)"曲收旭";
		Color = RED;
		break;
	case FULLHP:
		Texture[0] = (char*)"旨朴旬";
		Texture[1] = (char*)"早00早";
		Texture[2] = (char*)"曲收旭";
		Color = GREEN;
		break;
	}
}
