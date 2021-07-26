#include "Item.h"
#include "DoubleBuffer.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Initialize()
{
	switch (rand()%4)
	{
	case BOMBPOWERUP:
		Texture[0] = (char*)"¦®¦¬¦¯";
		Texture[1] = (char*)"++BP++";
		Texture[2] = (char*)"¦±¦¬¦°";
		ItemList = BOMBPOWERUP;
		break;
	case BOMBPOWERDOWN:
		Texture[0] = (char*)"¦®¦¬¦¯";
		Texture[1] = (char*)"--BP--";
		Texture[2] = (char*)"¦±¦¬¦°";
		ItemList = BOMBPOWERDOWN;
		break;
	case BOMBCAPACITYUP:
		Texture[0] = (char*)"¦®¦¬¦¯";
		Texture[1] = (char*)"++BC++";
		Texture[2] = (char*)"¦±¦¬¦°";
		ItemList = BOMBCAPACITYUP;
		break;
	case BOMBCAPACITYDOWN:
		Texture[0] = (char*)"¦®¦¬¦¯";
		Texture[1] = (char*)"--BC--";
		Texture[2] = (char*)"¦±¦¬¦°";
		ItemList = BOMBCAPACITYDOWN;
		break;
	}
	
	Color = WHITE;

	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);

	Active = false;
}

void Item::Update()
{
	if (Time + 1000 < GetTickCount64()) {
		if (Color == WHITE)	Color = LIGHTWHITE;
		else				Color = WHITE;
		Time = GetTickCount64();
	}
}

void Item::Render()
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

void Item::Release()
{
}