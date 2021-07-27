#include "Boss.h"
#include "InputManager.h"
#include "DoubleBuffer.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "Explosion.h"
#include "Player.h"


int Boss::CurrentBossState = HP_0;
int Boss::PreviousBossState = HP_0;
Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Initialize()
{
	Boss_Texture[0] = (char*)"┗━┛┗━┛┗━┛";
	Boss_Texture[1] = (char*)"┃━━╋╋╋━━┃";
	Boss_Texture[2] = (char*)"┃┏━┓　┏━┓┃";
	Boss_Texture[3] = (char*)"┃┏━┓　┏━┓┃";
	Boss_Texture[4] = (char*)"┃┃╋┃　┃╋┃┃";
	Boss_Texture[5] = (char*)"┃┗━┛╋┗━┛┃";
	Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
	Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
	Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";

	Boss_Hp = (char*)"[■■■■■]";
	//□
	Boss_Hp_Position = Vector3(84.0f, 1);
									 
	Color = LIGHTWHITE;
	CurrentBossState	= HP_5;
	PreviousBossState	= HP_5;

	TransInfo.Position  = Vector3((CONSOL_MAX_WIDTH-strlen(Boss_Texture[0]))/2-1, 21.0f);
	TransInfo.Scale		= Vector3((float)strlen(Boss_Texture[0]), 9.0f);
	
	Active = false;
	Jumping = false;
	Targetting = false;

	Time = GetTickCount64();
	PatternTime = GetTickCount64();

	m_Jump = false;
	m_OldY = 0.0f;
	m_Power = 1.0f;
	m_Time = 0.0f;

	Pattern_cnt = 0;
	Key = "Boss";
}

void Boss::Update()
{
	State();
	StateChange();
	if (PatternTime + 5000 < GetTickCount64() && CurrentBossState != HP_0) {
		Jump();
	}
	else if (PatternTime + 3000 < GetTickCount64() && CurrentBossState != HP_0)	targetMove();
	else if (PatternTime + 1000 < GetTickCount64() && CurrentBossState != HP_0)	randomMove();

	if (m_Jump)	//점프중인지 확인
	{
		m_Time += 0.1f;

		TransInfo.Position.y += -sinf(90 * PI / 180) * m_Power + (GRAVITY_ACCELERATION * m_Time * m_Time) / 2;

		if (m_OldY < TransInfo.Position.y)
		{
			TransInfo.Position.y = m_OldY;
			m_Jump = false;
			PatternTime = GetTickCount64();
			Skill();//점프가끝나는 순간 보스스킬 발동
		}
	}
}

void Boss::Render()
{
	for (int i = 0; i < 9; i++) {
		if (TransInfo.Position.y + i > 0) {
			DoubleBuffer::GetInstance()->WriteBuffer(
				int(TransInfo.Position.x),
				int(TransInfo.Position.y + i),
				Boss_Texture[i],
				Color
			);
		}
	}
	DoubleBuffer::GetInstance()->WriteBuffer(
		int(Boss_Hp_Position.x),
		int(Boss_Hp_Position.y),
		Boss_Hp
	);
}

void Boss::Release()
{
}

void Boss::State()
{
	switch (CurrentBossState)
	{
	case HP_0:
		Boss_Texture[0] = (char*)"┗━┛┗　┛┗━┛";
		Boss_Texture[1] = (char*)"┃━　╋━┳━━┃";
		Boss_Texture[2] = (char*)"┃━━━　━━━┃";
		Boss_Texture[3] = (char*)"┃┏━┳　┳━┓┃";
		Boss_Texture[4] = (char*)"┃┃┳┃　┃┳┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛┳┗━┛┃";
		Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
		Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Boss_Hp = (char*)"[□□□□□]";
		Color = PINK;
		break;
	case HP_1:
		Boss_Texture[0] = (char*)"┗━┛┗　┛┗━┛";
		Boss_Texture[1] = (char*)"┃━　╋━┳━━┃";
		Boss_Texture[2] = (char*)"┃━━━　━━━┃";
		Boss_Texture[3] = (char*)"┃┏━┳　┳━┓┃";
		Boss_Texture[4] = (char*)"┃┃┳┃　┃┳┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛┳┗━┛┃";
		Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
		Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Boss_Hp = (char*)"[■□□□□]";
		Color = PINK;
		break;
	case HP_2:
		Boss_Texture[0] = (char*)"┗━┛┗━┛┗━┛";
		Boss_Texture[1] = (char*)"┃━━╋╋╋━━┃";
		Boss_Texture[2] = (char*)"┃━━┓　┏━━┃";
		Boss_Texture[3] = (char*)"┃┏━┫　┠━┓┃";
		Boss_Texture[4] = (char*)"┃┃━┃　┃━┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛━┗━┛┃";
		Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
		Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Boss_Hp = (char*)"[■■□□□]";
		Color = YELLOW;
		break;
	case HP_3:
		Boss_Texture[0] = (char*)"┗━┛┗━┛┗━┛";
		Boss_Texture[1] = (char*)"┃━━╋╋╋━━┃";
		Boss_Texture[2] = (char*)"┃━━┓　┏━━┃";
		Boss_Texture[3] = (char*)"┃┏━┫　┠━┓┃";
		Boss_Texture[4] = (char*)"┃┃━┃　┃━┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛━┗━┛┃";
		Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
		Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Boss_Hp = (char*)"[■■■□□]";
		Color = YELLOW;
		break;
	case HP_4:
		Boss_Texture[0] = (char*)"┗━┛┗━┛┗━┛";
		Boss_Texture[1] = (char*)"┃━━╋╋╋━━┃";
		Boss_Texture[2] = (char*)"┃┏━┓　┏━┓┃";
		Boss_Texture[3] = (char*)"┃┏━┓　┏━┓┃";
		Boss_Texture[4] = (char*)"┃┃╋┃　┃╋┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛╋┗━┛┃";
		Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
		Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Boss_Hp = (char*)"[■■■■□]";
		Color = LIGHTWHITE;
		break;
	case HP_5:
		Boss_Texture[0] = (char*)"┗━┛┗━┛┗━┛";
		Boss_Texture[1] = (char*)"┃━━╋╋╋━━┃";
		Boss_Texture[2] = (char*)"┃┏━┓　┏━┓┃";
		Boss_Texture[3] = (char*)"┃┏━┓　┏━┓┃";
		Boss_Texture[4] = (char*)"┃┃╋┃　┃╋┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛╋┗━┛┃";
		Boss_Texture[6] = (char*)"┃　┏━━━┓　┃";
		Boss_Texture[7] = (char*)"┃　┗━━━┛　┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Boss_Hp = (char*)"[■■■■■]";
		Color = LIGHTWHITE;
		break;
	case HP_INVINCIBILITY:
		Boss_Texture[0] = (char*)"┗━┛┗━┛┗━┛";
		Boss_Texture[1] = (char*)"┃━╋━╋━╋━┃";
		Boss_Texture[2] = (char*)"┃┗━┛　┗━┛┃";
		Boss_Texture[3] = (char*)"┃┏━┓　┏━┓┃";
		Boss_Texture[4] = (char*)"┃┃┳┃　┃┳┃┃";
		Boss_Texture[5] = (char*)"┃┗━┛┳┗━┛┃";
		Boss_Texture[6] = (char*)"┃┏━━━━━┓┃";
		Boss_Texture[7] = (char*)"┃┗━━━━━┛┃";
		Boss_Texture[8] = (char*)"┗┳━━━━━┳┛";
		Color = GRAY;
		break;
	}
}

void Boss::StateChange()
{
	if (PreviousBossState != CurrentBossState && Pattern_cnt == 0) {
		Pattern_cnt++;
		PatternTime = GetTickCount64();
	}
	if (PreviousBossState != CurrentBossState && PatternTime + 1000 < GetTickCount64()) {
		PreviousBossState--;
		CurrentBossState = PreviousBossState;
		Pattern_cnt = 0;
	}
}

void Boss::randomMove()
{
	if (Time + 200 * (rand() % 10 + 1) < GetTickCount64()) {
		switch (rand() % 8) {
		case DIRECTION_UP:
			TransInfo.Position.y -= BOSS_SPEED_Y;
			if (ObjectManager::GetInstance()->bossCollision())
				TransInfo.Position.y += BOSS_SPEED_Y;
			break;
		case DIRECTION_RIGHT:
			TransInfo.Position.x += BOSS_SPEED_X;
			if (ObjectManager::GetInstance()->bossCollision())
				TransInfo.Position.x -= BOSS_SPEED_X;
			break;
		case DIRECTION_LEFT:
			TransInfo.Position.x -= BOSS_SPEED_X;
			if (ObjectManager::GetInstance()->bossCollision())
				TransInfo.Position.x += BOSS_SPEED_X;
			break;
		case DIRECTION_DOWN:
			TransInfo.Position.y += BOSS_SPEED_Y;
			if (ObjectManager::GetInstance()->bossCollision())
				TransInfo.Position.y -= BOSS_SPEED_Y;
			break;
		case DIRECTION_UPRIGHT:
			TransInfo.Position.y -= BOSS_SPEED_Y;
			TransInfo.Position.x += BOSS_SPEED_X;
			if (ObjectManager::GetInstance()->bossCollision()) {
				TransInfo.Position.y += BOSS_SPEED_Y;
				TransInfo.Position.x -= BOSS_SPEED_X;
			}
			break;
		case DIRECTION_UPLEFT:
			TransInfo.Position.y -= BOSS_SPEED_Y;
			TransInfo.Position.x -= BOSS_SPEED_X;
			if (ObjectManager::GetInstance()->bossCollision()) {
				TransInfo.Position.y += BOSS_SPEED_Y;
				TransInfo.Position.x += BOSS_SPEED_X;
			}
			break;
		case DIRECTION_DOWNRIGHT:
			TransInfo.Position.y += BOSS_SPEED_Y;
			TransInfo.Position.x += BOSS_SPEED_X;
			if (ObjectManager::GetInstance()->bossCollision()) {
				TransInfo.Position.y -= BOSS_SPEED_Y;
				TransInfo.Position.x -= BOSS_SPEED_X;
			}
			break;
		case DIRECTION_DOWNLEFT:
			TransInfo.Position.y += BOSS_SPEED_Y;
			TransInfo.Position.x -= BOSS_SPEED_X;
			if (ObjectManager::GetInstance()->bossCollision()) {
				TransInfo.Position.y -= BOSS_SPEED_Y;
				TransInfo.Position.x += BOSS_SPEED_X;
			}
			break;
		}
		Time = GetTickCount64();
	}

}

void Boss::targetMove()
{
	Vector3 target = ObjectManager::GetInstance()->bossTargetMove();

	TransInfo.Position.y += target.y * BOSS_TARGET_COEFFICIENT;
	if (ObjectManager::GetInstance()->bossCollision())
		TransInfo.Position.y -= target.y * BOSS_TARGET_COEFFICIENT;

	TransInfo.Position.x += target.x * BOSS_TARGET_COEFFICIENT;
	if (ObjectManager::GetInstance()->bossCollision())
		TransInfo.Position.x -= target.x * BOSS_TARGET_COEFFICIENT;
}

void Boss::Jump()
{
	if (m_Jump)
		return;

	m_Jump = true;
	m_OldY = TransInfo.Position.y;
	m_Time = 0.0f;
}

void Boss::Skill()
{
	ObjectManager::GetInstance()->createBossExplosion(TransInfo.Position);
}