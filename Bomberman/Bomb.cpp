#include "Bomb.h"
#include "DoubleBuffer.h"
#include "ObjectManager.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Initialize()
{
	Texture[0] = (char*)"¦®¦µ¦¯";
	Texture[1] = (char*)"¦­¢Ë¦­";
	Texture[2] = (char*)"¦±¦¬¦°";
	Color = LIGHTWHITE;

	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);

	Active = false;
}

void Bomb::Update()
{
	if (Active) {
		if (Time + 1000 < GetTickCount64()) {
			Color = ORANGE;
			if (Time + 2000 < GetTickCount64())	Color = RED;
		}
		
		if (Time + 3000 < GetTickCount64()) {
			Active = false;
			Time = GetTickCount64();
			Color = LIGHTWHITE;
			ObjectManager::GetInstance()->createExplosion(TransInfo.Position);
			TransInfo.Position = Vector3(0, 0);
		}
	}
}

void Bomb::Render()
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

void Bomb::Release()
{
}
