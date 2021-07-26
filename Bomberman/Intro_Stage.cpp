#include "Intro_Stage.h"
#include "SceneManager.h"
#include "DoubleBuffer.h"
Intro_Stage::Intro_Stage()
{
}

Intro_Stage::~Intro_Stage()
{
}

void Intro_Stage::Initialize()
{	
	Text = "Stage ";
	if (stage_No == BOSS)	Text = "Boss";
	Text_Position = Vector3((CONSOL_MAX_WIDTH - strlen(Text)) / 2, CONSOL_MAX_HEIGHT / 2);
	stage_No_Position = Vector3(Text_Position.x + strlen(Text), CONSOL_MAX_HEIGHT / 2);
	Time = GetTickCount64();
}

void Intro_Stage::Update()
{
	if(Time + 3000 < GetTickCount64()){
		Time = GetTickCount64();
		SceneManager::GetInstance()->SetScene(STAGE);
	}
}

void Intro_Stage::Render()
{
	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)Text_Position.x,
		(int)Text_Position.y,
		Text
	);
	if (stage_No != BOSS) {
		DoubleBuffer::GetInstance()->WriteBuffer(
			(int)stage_No_Position.x,
			(int)stage_No_Position.y,
			stage_No
		);
	}
}

void Intro_Stage::Release()
{
}
