#include "Wall.h"
#include "DoubleBuffer.h"

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
	Texture[0] = (char*)"������";
	Texture[1] = (char*)"������";
	Texture[2] = (char*)"������";
	Color = GRAY;

	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);

	Active = false;
	Key = "Wall";
}

void Wall::Update()
{
}

void Wall::Render()
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

void Wall::Release()
{
}