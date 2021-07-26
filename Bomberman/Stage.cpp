#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "DoubleBuffer.h"
#include "Player.h"
#include "Boss.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	ObjectManager::GetInstance()->Initialize();
	
	time_cnt = 0;

	Clear[0] = (char*)"  ####   ##      ######    ###    ###### ";
	Clear[1] = (char*)" ##  ##  ##      ##       ## ##   ##   ##";
	Clear[2] = (char*)"##       ##      ##      ##   ##  ##   ##";
	Clear[3] = (char*)"##       ##      #####   ##   ##  ##  ###";
	Clear[4] = (char*)"##       ##      ##      #######  #####  ";
	Clear[5] = (char*)" ##  ##  ##   #  ##      ##   ##  ## ### ";
	Clear[6] = (char*)"  ####   ######  ######  ##   ##  ##  ###";

	GameOver[0] = (char*)"  ####     ###    ##   ##   ######     #####   ##   ##   ######  ###### ";
	GameOver[1] = (char*)" ##  ##   ## ##   ### ###   ##        ##   ##  ##   ##   ##      ##   ##";
	GameOver[2] = (char*)"##       ##   ##  #######   ##        ##   ##  ##   ##   ##      ##   ##";
	GameOver[3] = (char*)"##  ###  ##   ##  #######   #####     ##   ##  ### ###   #####   ##  ###";
	GameOver[4] = (char*)"##   ##  #######  ## # ##   ##        ##   ##   #####    ##      #####  ";
	GameOver[5] = (char*)" ##  ##  ##   ##  ##   ##   ##        ##   ##    ###     ##      ## ### ";
	GameOver[6] = (char*)"  ####   ##   ##  ##   ##   ######     #####      #      ######  ##  ###";
}
                                                                        
void Stage::Update()
{
	ObjectManager::GetInstance()->Update();
	if (Player::PlayerHp == 0) {
		if (time_cnt < 1) {
			Time = GetTickCount64();
			time_cnt++;
		}
		if(Time + 4000 < GetTickCount64())	SceneManager::GetInstance()->SetScene(LOGO);
	}
	else if (ObjectManager::Enemy_cnt == 0) {
		if (time_cnt < 1) {
			Time = GetTickCount64();
			time_cnt++;
		}
		if (Time + 4000 < GetTickCount64())	SceneManager::GetInstance()->SetScene(INTRO_STAGE);
	}
	else if (Boss::CurrentBossState == HP_0) {
		if (time_cnt < 1) {
			Time = GetTickCount64();
			time_cnt++;
		}
		if (Time + 4000 < GetTickCount64())	SceneManager::GetInstance()->SetScene(ENDING);
	}
}

void Stage::Render()
{
	ObjectManager::GetInstance()->Render();
	if (Player::PlayerHp == EMPTYHP) {
		for (int i = 0; i < 7; i++) {
			DoubleBuffer::GetInstance()->WriteBuffer(
				CONSOL_MAX_WIDTH / 2 - strlen(GameOver[0]) / 2,
				CONSOL_MAX_HEIGHT / 3 + i,
				GameOver[i],
				RED);
		}
	}
	else if (ObjectManager::Enemy_cnt == 0 || Boss::CurrentBossState == HP_0) {
		for (int i = 0; i < 7; i++) {
			DoubleBuffer::GetInstance()->WriteBuffer(
				CONSOL_MAX_WIDTH / 2 - strlen(Clear[0]) / 2,
				CONSOL_MAX_HEIGHT / 3 + i,
				Clear[i],
				GREEN);
		}
	}
}

void Stage::Release()
{
	ObjectManager::GetInstance()->Release();
}
