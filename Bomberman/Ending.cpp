#include "Ending.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

Ending::Ending()
{
}

Ending::~Ending()
{
}

void Ending::Initialize()
{
	Text = "- Thank you -";
	Text_Position = Vector3((CONSOL_MAX_WIDTH - strlen(Text)) / 2, CONSOL_MAX_HEIGHT / 2);
	Time = GetTickCount64();
}

void Ending::Update()
{
	if (Time + 5000 < GetTickCount64())	SceneManager::GetInstance()->SetScene(LOGO);
}

void Ending::Render()
{
	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)Text_Position.x,
		(int)Text_Position.y,
		Text
	);
}

void Ending::Release()
{
}
