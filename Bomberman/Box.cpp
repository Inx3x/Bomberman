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
	Texture[0] = (char*)"旨收旬";
	Texture[1] = (char*)"早朱早";
	Texture[2] = (char*)"曲收旭";
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