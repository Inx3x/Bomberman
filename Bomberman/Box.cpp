#include "Box.h"
#include "DoubleBuffer.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::Initialize()
{
	Texture[0] = (char*)"������";
	Texture[1] = (char*)"������";
	Texture[2] = (char*)"������";
	Color = ORANGE;

	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3((float)strlen(Texture[0]), 3.0f);

	Active = false;
	Key = BOX;
}

void Box::Update()
{
	
}

void Box::Render()
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

void Box::Release()
{
}