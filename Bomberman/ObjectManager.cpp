#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "DoubleBuffer.h"
#include "Player.h"
#include "Wall.h"
#include "Box.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Item.h"
#include "Boss.h"
#include "Scene.h"

ObjectManager* ObjectManager::m_pInstance = NULL;
int ObjectManager::Enemy_cnt = 0;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	Release();
}
void ObjectManager::AddObject(Object* _obj) {
	map<OBJECT, list<Object*>>::iterator iter = ObjectList.find(_obj->GetKey());

	if (iter == ObjectList.end()) {
		list<Object*> TempList;
		TempList.push_back(_obj);

		ObjectList.insert(make_pair(_obj->GetKey(), TempList));
	}
	else {
		iter->second.push_back(_obj);
	}
}

//map<string, list<Object*>>::iterator iter = ObjectList.find("Player");
//list<Object*>::iterator iter2 = (*iter).second.begin();
//(*(*ObjectList.find("Player")).second.begin())->getActive();

void ObjectManager::Initialize()
{
	//플레이어개체 생성
	AddObject(ObjectFactory<Player>::CreateObject());
	map<OBJECT, list<Object*>>::iterator iter = ObjectList.find(PLAYER);
	(*(*ObjectList.find(PLAYER)).second.begin())->setActive(true);
	//벽객체 생성
	for (int i = 0; i < 128; i++) {
		AddObject(ObjectFactory<Wall>::CreateObject());
	}
	createWall();
	//폭탄 개체 생성
	for (int i = 0; i < 16; i++) {
		m_pBomb[i] = new Bomb;
		m_pBomb[i]->Initialize();
		AddObject(m_pBomb[i]);
	}
	bomb_cnt = 0;
	bomb_capacity = 2;
	//박스객체 생성
	for (int i = 0; i < 64; i++) {
		m_pBox[i] = new Box;
		m_pBox[i]->Initialize();
		AddObject(m_pBox[i]);
	}	
	createBox();
	//아이템객체 생성
	for (int i = 0; i < 32; i++) {
		m_pItem[i] = new Item;
		m_pItem[i]->Initialize();
		m_pItem[i]->setActive(true);
		AddObject(m_pItem[i]);
		item_hp[i] = 3;
	}
	item_cnt = 0;
	//폭파 오브젝트 생성
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++)
		{
			m_pExplosion[i][j] = new Explosion;
			m_pExplosion[i][j]->Initialize();
			AddObject(m_pExplosion[i][j]);
			switch (j) {
			case DIRECTION_UP:
				m_pExplosion[i][j]->setExplosionDirection(DIRECTION_UP);
				break;
			case DIRECTION_RIGHT:
				m_pExplosion[i][j]->setExplosionDirection(DIRECTION_RIGHT);
				break;
			case DIRECTION_LEFT:
				m_pExplosion[i][j]->setExplosionDirection(DIRECTION_LEFT);
				break;
			case DIRECTION_DOWN:
				m_pExplosion[i][j]->setExplosionDirection(DIRECTION_DOWN);
				break;
			}
		}
	}
	//보스스킬 생성
	for (int i = 0; i < 12; i++) {
		m_pBossExplosion[i] = new Explosion;
		m_pBossExplosion[i]->Initialize();
		m_pBossExplosion[i]->setBossExplosion(true);
		AddObject(m_pBossExplosion[i]);
		if (i < 3)		m_pBossExplosion[i]->setExplosionDirection(DIRECTION_UP);
		else if(i < 6)	m_pBossExplosion[i]->setExplosionDirection(DIRECTION_RIGHT);
		else if(i < 9)	m_pBossExplosion[i]->setExplosionDirection(DIRECTION_LEFT);
		else			m_pBossExplosion[i]->setExplosionDirection(DIRECTION_DOWN);
	}	
	//에너미 생성
	for (int i = 0; i < 16; i++)	{
		m_pEnemy[i] = new Enemy;
		m_pEnemy[i]->Initialize();
		AddObject(m_pEnemy[i]);
	}
	createEnemy();

	//보스 생성
	m_pBoss = new Boss;
	m_pBoss->Initialize();
	AddObject(m_pBoss);
	if (Scene::stage_No == STAGE_BOSS) 	m_pBoss->setActive(true);
	
	stage_cnt = 0;
}

void ObjectManager::Update()
{
	//폭탄개수조정
	setBombCnt();
	//플레이어 업데이트
	if ((*(*ObjectList.find(PLAYER)).second.begin())->getActive())	(*(*ObjectList.find(PLAYER)).second.begin())->Update();
	//아이템업데이트
	for (int i = 0; i < 32; i++) {					
		if (m_pItem[i]->getActive())	m_pItem[i]->Update();
	}
	//폭탄 업데이트
	for (int i = 0; i < 16; i++) {							
		if(m_pBomb[i]->getActive())		m_pBomb[i]->Update();
	}
	//폭파 업데이트
	for (int i = 0; i < 16; i++) {							
		for (int j = 0; j < 4; j++)	
			if (m_pExplosion[i][j]->getActive())	m_pExplosion[i][j]->Update();
		
	}
	//폭파충돌감지
	explosionCollision();
	//보스스킬 업데이트
	for (int i = 0; i < 12; i++) {
			if (m_pBossExplosion[i]->getActive())	m_pBossExplosion[i]->Update();

	}
	//에너미 업데이트
	for (int i = 0; i < 16; i++) {					
		if(m_pEnemy[i]->getActive())	m_pEnemy[i]->Update();
	}
	//보스 업데이트
	if(m_pBoss->getActive())	m_pBoss->Update();

	if (Enemy_cnt == 0) {
		if (stage_cnt < 1) {
			stage_cnt++;
			Scene::stage_No++;
		}
	}
}

void ObjectManager::Render()
{
	//벽 출력
	for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
		iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall)
	{
		if ((*iterWall)->getActive())	(*iterWall)->Render();
	}
	//상자 출력
	for (int i = 0; i < box_cnt; i++) {
		if(m_pBox[i]->getActive())		m_pBox[i]->Render();
	}
	//아이템 출력
	for (int i = 0; i < item_cnt; i++) {
		if (m_pItem[i]->getActive())	m_pItem[i]->Render();
	}
	//플레이어 출력
	if((*(*ObjectList.find(PLAYER)).second.begin())->getActive())	(*(*ObjectList.find(PLAYER)).second.begin())->Render();
	//폭탄출력
	for (int i = 0; i < 16; i++) {
		if (m_pBomb[i]->getActive())	m_pBomb[i]->Render();
	}
	//에너미 출력
	for (int i = 0; i < 16; i++) {
		if (m_pEnemy[i]->getActive())	m_pEnemy[i]->Render();
	}
	//보스 출력
	if (m_pBoss->getActive()) {
		m_pBoss->Render();

	}
	//폭파출력
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++)
			if (m_pExplosion[i][j]->getActive())	m_pExplosion[i][j]->Render();
	}
	//보스폭파출력
	for (int i = 0; i < 12; i++) {
			if (m_pBossExplosion[i]->getActive())	m_pBossExplosion[i]->Render();
	}
}

void ObjectManager::Release()
{
	//Player Release
	SAFE_RELEASE((*(*ObjectList.find(PLAYER)).second.begin()));
	(*ObjectList.find(PLAYER)).second.clear();

	//Wall Release
	for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
		iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall)
	{
		SAFE_RELEASE((*iterWall));
	}
	(*ObjectList.find(WALL)).second.clear();

	//Box Release
	for (int i = 0; i < 64; i++) {
		SAFE_RELEASE(m_pBox[i]);
	}

	for (int i = 0; i < 32; i++) {
		SAFE_RELEASE(m_pItem[i]);
	}
	for (int i = 0; i < 16; i++) {
		SAFE_RELEASE(m_pBomb[i]);
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			SAFE_RELEASE(m_pExplosion[i][j]);
		}
	}
	for (int i = 0; i < 12; i++) {
		SAFE_RELEASE(m_pBossExplosion[i]);
	}
	for (int i = 0; i < 16; i++) {
		SAFE_RELEASE(m_pEnemy[i]);
	}
	SAFE_RELEASE(m_pBoss);
}

//벽 생성
void ObjectManager::createWall()
{
	Transform m_pWall_TransInfo = (*(*ObjectList.find(WALL)).second.begin())->GetTransform();

	//벽 위치 설정
	list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (i == 0 || i == 16) {
				(*iterWall)->setActive(true);
				(*iterWall)->SetPosition(
					m_pWall_TransInfo.Position.x,
					m_pWall_TransInfo.Position.y);
				iterWall++;
			}
			else if (i % 2 == 1) {
				if (j == 0 || j == 16) {
					(*iterWall)->setActive(true);
					(*iterWall)->SetPosition(
						m_pWall_TransInfo.Position.x,
						m_pWall_TransInfo.Position.y);
					iterWall++;
				}
			}
			else {
				if (j % 2 == 0) {
					(*iterWall)->setActive(true);
					(*iterWall)->SetPosition(
						m_pWall_TransInfo.Position.x,
						m_pWall_TransInfo.Position.y);
					iterWall++;
				}
			}
			m_pWall_TransInfo.Position.x += OBJ_SIZE_X;
		}
		m_pWall_TransInfo.Position.x = 0;
		m_pWall_TransInfo.Position.y += OBJ_SIZE_Y;
	}
}

//박스 생성
void ObjectManager::createBox()
{
	Transform m_pBox_TransInfo = m_pBox[0]->GetTransform();
	box_cnt = 0;

	//박스 위치 설정
	switch (Scene::stage_No)
	{
	case STAGE_HIDDEN:
		break;
	case STAGE_1:
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				if (i % 2 == 0 && j % 2 == 1) {
					if (i != 0 && j != 1 && i != 16 && j != 15) {
						m_pBox[box_cnt]->SetPosition(
							m_pBox_TransInfo.Position.x,
							m_pBox_TransInfo.Position.y);
						m_pBox[box_cnt]->setActive(true);
						box_cnt++;
					}
				}
				m_pBox_TransInfo.Position.x += OBJ_SIZE_X;
			}
			m_pBox_TransInfo.Position.x = 0;
			m_pBox_TransInfo.Position.y += OBJ_SIZE_Y;
		}
		break;
	case STAGE_2:
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				if (i % 2 == 1 && j % 2 == 0) {
					if (i != 1 && j != 0 && i != 15 && j != 16) {
						m_pBox[box_cnt]->SetPosition(
							m_pBox_TransInfo.Position.x,
							m_pBox_TransInfo.Position.y);
						m_pBox[box_cnt]->setActive(true);
						box_cnt++;
					}
				}
				m_pBox_TransInfo.Position.x += OBJ_SIZE_X;
			}
			m_pBox_TransInfo.Position.x = 0;
			m_pBox_TransInfo.Position.y += OBJ_SIZE_Y;
		}
		break;
	case STAGE_BOSS:
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				if (i % 2 == 1 && j % 2 == 0) {
					if (i != 1 && j != 0 && i != 15 && j != 16) {
						m_pBox[box_cnt]->SetPosition(
							m_pBox_TransInfo.Position.x,
							m_pBox_TransInfo.Position.y);
						m_pBox[box_cnt]->setActive(true);
						box_cnt++;
					}
				}
				m_pBox_TransInfo.Position.x += OBJ_SIZE_X;
			}
			m_pBox_TransInfo.Position.x = 0;
			m_pBox_TransInfo.Position.y += OBJ_SIZE_Y;
		}
		break;
	}
}

//아이템 생성
void ObjectManager::createItem(const Transform& _m_pBox_TransInfo)
{
	m_pItem[item_cnt]->SetPosition(_m_pBox_TransInfo.Position.x, _m_pBox_TransInfo.Position.y);
	m_pItem[item_cnt]->setActive(true);
	m_pItem[item_cnt]->setTime(GetTickCount64());

	item_cnt++;
}

//적 생성
void ObjectManager::createEnemy()
{
	Transform m_pEnemy_TransInfo = m_pEnemy[0]->GetTransform();
	Enemy_cnt = 0;

	switch (Scene::stage_No)
	{
	case STAGE_HIDDEN:
		break;
	case STAGE_1:
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				if (i % 2 != 0 && j == 16 - i) {
					if (!m_pEnemy[Enemy_cnt]->getActive()) {
						m_pEnemy[Enemy_cnt]->setActive(true);
						m_pEnemy[Enemy_cnt]->SetPosition(
							m_pEnemy_TransInfo.Position.x,
							m_pEnemy_TransInfo.Position.y);
						Enemy_cnt++;
					}
				}
				m_pEnemy_TransInfo.Position.x += OBJ_SIZE_X;
			}
			m_pEnemy_TransInfo.Position.x = 0;
			m_pEnemy_TransInfo.Position.y += OBJ_SIZE_Y;
		}
		break;
	case STAGE_2:
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				if (i == 4 || i == 10) {
					if (j % 2 == 1) {
						if (!m_pEnemy[Enemy_cnt]->getActive()) {
							m_pEnemy[Enemy_cnt]->setActive(true);
							m_pEnemy[Enemy_cnt]->SetPosition(
								m_pEnemy_TransInfo.Position.x,
								m_pEnemy_TransInfo.Position.y);
							Enemy_cnt++;
						}
					}
				}
				m_pEnemy_TransInfo.Position.x += OBJ_SIZE_X;
			}
			m_pEnemy_TransInfo.Position.x = 0;
			m_pEnemy_TransInfo.Position.y += OBJ_SIZE_Y;
		}
		break;
	case STAGE_BOSS:
		Enemy_cnt++;
		break;
	}
}

//폭탄 생성
void ObjectManager::createBomb()
{
	//폭탄 생성
	bool conllision_bomb = false;
	bool bomb_capacity_over = false;
	for (int i = 0; i < 16; i++) {
		if (CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pBomb[i]->GetTransform())) {
			conllision_bomb = true;
			break;
		}
	}
	if (bomb_cnt < bomb_capacity)	bomb_capacity_over = true;

	if (!conllision_bomb && bomb_capacity_over) {
		for (int i = 0; i < 16; i++) {
			if (!m_pBomb[i]->getActive()) {
				Transform m_pBomb_TransInfo = bombTransInfo((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform());
				m_pBomb[i]->setActive(true);
				m_pBomb[i]->SetPosition(m_pBomb_TransInfo.Position.x, m_pBomb_TransInfo.Position.y);
				m_pBomb[i]->setTime(GetTickCount64());
				bomb_cnt++;
				break;
			}
		}
	}
}

//폭발 생성
void ObjectManager::createExplosion(const Vector3& _TransInfoPosition)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++) {
			if (!m_pExplosion[j][i]->getActive()) {
				m_pExplosion[j][i]->setActive(true);
				m_pExplosion[j][i]->SetPosition(_TransInfoPosition.x, _TransInfoPosition.y);
				m_pExplosion[j][i]->setExplosionPowerZero();
				break;
			}
		}
	}
}

//보스스킬 생성
void ObjectManager::createBossExplosion(const Vector3& _TransInfoPosition)
{
	for (int j = 0; j < 12; j++) {
		if (!m_pBossExplosion[j]->getActive()) {
			m_pBossExplosion[j]->setActive(true);
			switch (j) {
			case 0 :
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x, _TransInfoPosition.y - OBJ_SIZE_Y);
				break;
			case 1:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X, _TransInfoPosition.y - OBJ_SIZE_Y);
				break;																					 
			case 2:																						 
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X*2, _TransInfoPosition.y - OBJ_SIZE_Y);
				break;
			case 3:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X * 3, _TransInfoPosition.y);
				break;
			case 4:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X * 3, _TransInfoPosition.y + OBJ_SIZE_Y);
				break;
			case 5:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X * 3, _TransInfoPosition.y + OBJ_SIZE_Y * 2);
				break;
			case 6:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x - OBJ_SIZE_X, _TransInfoPosition.y);
				break;
			case 7:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x - OBJ_SIZE_X, _TransInfoPosition.y + OBJ_SIZE_Y);
				break;
			case 8:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x - OBJ_SIZE_X, _TransInfoPosition.y + OBJ_SIZE_Y * 2);
				break;
			case 9:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x, _TransInfoPosition.y + OBJ_SIZE_Y * 3);
				break;
			case 10:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X, _TransInfoPosition.y + OBJ_SIZE_Y * 3);
				break;
			case 11:
				m_pBossExplosion[j]->SetPosition(_TransInfoPosition.x + OBJ_SIZE_X * 2, _TransInfoPosition.y + OBJ_SIZE_Y * 3);
				break;
			
			}
			m_pBossExplosion[j]->setExplosionPowerZero();
		}
	}
}

//폭발 충돌
void ObjectManager::explosionCollision()
{
	bool collision = false;
	
	//폭파 벽 충돌
	for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
		iterWall != (*ObjectList.find(WALL)).second.end(); iterWall++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				if ((*iterWall)->getActive() && m_pExplosion[j][k]->getActive() &&
					CollisionManager::CollisionRact((*iterWall)->GetTransform(), m_pExplosion[j][k]->GetTransform())) {
					collision = true;
					break;
				}
			}
		}
	}
	//폭파 적들 충돌
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				if (m_pEnemy[i]->getActive() && m_pExplosion[j][k]->getActive() &&
					CollisionManager::CollisionRact(m_pEnemy[i]->GetTransform(), m_pExplosion[j][k]->GetTransform())) {
					m_pEnemy[i]->setActive(false);
					if (rand() % 10 < 7)	createItem(m_pEnemy[i]->GetTransform());	//70프로확률로 아이템생성
					m_pEnemy[i]->SetPosition(0, 0);
					Enemy_cnt--;
					break;
				}
			}
		}
	}
	//폭파 상자 충돌
	for (int i = 0; i < box_cnt; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				if (m_pBox[i]->getActive() && m_pExplosion[j][k]->getActive() &&
					CollisionManager::CollisionRact(m_pBox[i]->GetTransform(), m_pExplosion[j][k]->GetTransform())) {
					m_pBox[i]->setActive(false);
					if (rand() % 10 < 3)	createItem(m_pBox[i]->GetTransform());		//30프로확률로 아이템생성
					m_pBox[i]->SetPosition(0, 0);
				}
			}
		}
	}
	//폭파 플레이어 충돌
	for (int j = 0; j < 16; j++) {
		for (int k = 0; k < 4; k++) {
			if (m_pExplosion[j][k]->getActive() && 
				CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pExplosion[j][k]->GetTransform())) {
				Player::PlayerHp = EMPTYHP;
			}
		}
	}
	//보스 스킬 플레이어 충돌
	for (int i = 0; i < 16; i++) {
		if (m_pBossExplosion[i]->getActive() && !collision &&
			CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pBossExplosion[i]->GetTransform())) {
			Player::PlayerHp = EMPTYHP;
		}
	}
	//폭파 폭탄 충돌
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				if (m_pBomb[i]->getActive() && m_pExplosion[j][k]->getActive() &&
					CollisionManager::CollisionRact(m_pBomb[i]->GetTransform(), m_pExplosion[j][k]->GetTransform())) 
					m_pBomb[i]->setTime(m_pBomb[i]->gettTime() - 3000);
			}
		}
	}
	//보스 스킬 폭탄 충돌
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (m_pBossExplosion[i]->getActive() && m_pBomb[j]->getActive() &&
				CollisionManager::CollisionRact(m_pBomb[j]->GetTransform(), m_pBossExplosion[i]->GetTransform())) 
				m_pBomb[i]->setTime(m_pBomb[i]->gettTime() - 3000);
		}
	}
	//폭파 아이템 충돌
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				if (m_pItem[i]->getActive() && m_pExplosion[j][k]->getActive() &&
					CollisionManager::CollisionRact(m_pItem[i]->GetTransform(), m_pExplosion[j][k]->GetTransform())) {
					item_hp[i]--;
					if (item_hp[i] < 0) {
						m_pItem[i]->setActive(false);
						m_pItem[i]->SetPosition(0, 0);
					}
				}
			}
		}
	}
	//폭파 보스 충돌
	for (int j = 0; j < 16; j++) {
		for (int k = 0; k < 4; k++) {
			if (m_pBoss->getActive() && m_pExplosion[j][k]->getActive() &&
				CollisionManager::CollisionRact(m_pBoss->GetTransform(), m_pExplosion[j][k]->GetTransform())) {
				if (Boss::CurrentBossState == HP_1)	Boss::CurrentBossState--;
				else if (Boss::CurrentBossState == Boss::PreviousBossState) {
					Boss::CurrentBossState = HP_INVINCIBILITY;
				}
				break;
			}
		}
	}
}

//폭탄 개수 조정
void ObjectManager::setBombCnt()
{
	int count = 0;
	for (int i = 0; i < 16; i++) {
		if (m_pBomb[i]->getActive())	count++;
	}
	bomb_cnt = count;
}

//플레이어 충돌
bool ObjectManager::playerCollision()
{
	bool collision = false;

	//플레이어 벽 충돌
	for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
		iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall) {
		if (CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), (*iterWall)->GetTransform())) {
			collision = true;
			break;
		}
	}
	//플레이어 상자 충돌
	for (int i = 0; i < box_cnt; i++) {
		if (CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pBox[i]->GetTransform())) {
			collision = true;
			break;
		}
	}
	//플레이어 적들 충돌
	for (int i = 0; i < 16; i++) {
		if (m_pEnemy[i]->getActive() && 
			CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pEnemy[i]->GetTransform())) {
			Player::PlayerHp = EMPTYHP;
			collision = true;
			break;
		}
	}
	//플레이어 보스 충돌
	if(m_pBoss->getActive() && 
		CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pBoss->GetTransform())) {
		Player::PlayerHp = EMPTYHP;
	}
	//플레이어 아이템 충돌
	for (int i = 0; i < 32; i++) {
		if (m_pItem[i]->getActive() && !collision &&
			CollisionManager::CollisionRact(m_pItem[i]->GetTransform(), (*(*ObjectList.find(PLAYER)).second.begin())->GetTransform())) {
			m_pItem[i]->setActive(false);
			m_pItem[i]->SetPosition(0, 0);
			switch (m_pItem[i]->getItemList())
			{
			case BOMBPOWERUP:
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 16; j++) {
						if (!m_pExplosion[j][i]->getActive()) {
							m_pExplosion[j][i]->setExplosion_Weight(BOMBPOWERUP);
						}
					}
				}
				break;
			case BOMBPOWERDOWN:
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 16; j++) {
						if (!m_pExplosion[j][i]->getActive()) {
							m_pExplosion[j][i]->setExplosion_Weight(BOMBPOWERDOWN);
						}
					}
				}
				break;
			case BOMBCAPACITYUP:
				if (bomb_capacity < 15)	bomb_capacity++;
				break;
			case BOMBCAPACITYDOWN:
				if (bomb_capacity > 1)	bomb_capacity--;
				break;
			}
			break;
		}
	}

	return collision;
}

//폭발 범위
bool ObjectManager::explosionRange(const int& _direction)
{
	bool collision = false;
	list<Object*>::iterator iterWall;
	switch (_direction)
	{
	case DIRECTION_UP:
		for (int i = 0; i < 16; i++) {
			if (m_pExplosion[i][DIRECTION_UP]->getActive()) {
				for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
					iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall) {
					if (CollisionManager::CollisionRact(m_pExplosion[i][DIRECTION_UP]->GetTransform(), 
						(*iterWall)->GetTransform())) {
						collision = true;
						break;
					}
				}
			}			
		}
		for (int i = 0; i < 3; i++) {
			if(m_pBossExplosion[i]->getActive())
				if (m_pBossExplosion[i]->GetPosition().y < 0) {
					collision = true;
					break;
				}
		}
		break;
	case DIRECTION_RIGHT:
		for (int i = 0; i < 16; i++) {
			if (m_pExplosion[i][DIRECTION_RIGHT]->getActive()) {
				for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
					iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall) {
					if (CollisionManager::CollisionRact(m_pExplosion[i][DIRECTION_RIGHT]->GetTransform(),
						(*iterWall)->GetTransform())) {
						collision = true;
						break;
					}
				}
			}
		}
		for (int i = 3; i < 6; i++) {
			if (m_pBossExplosion[i]->getActive())
				if (m_pBossExplosion[i]->GetPosition().x + m_pBossExplosion[i]->GetScale().x > CONSOL_MAX_WIDTH) {
					collision = true;
					break;
				}
		}
		break;
	case DIRECTION_LEFT:
		for (int i = 0; i < 16; i++) {
			if (m_pExplosion[i][DIRECTION_LEFT]->getActive()) {
				for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
					iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall) {
					if (CollisionManager::CollisionRact(m_pExplosion[i][DIRECTION_LEFT]->GetTransform(),
						(*iterWall)->GetTransform())) {
						collision = true;
						break;
					}
				}
			}
		}
		for (int i = 6; i < 9; i++) {
			if (m_pBossExplosion[i]->getActive())
				if (m_pBossExplosion[i]->GetPosition().x < 0) {
					collision = true;
					break;
				}
		}
		break;
	case DIRECTION_DOWN:
		for (int i = 0; i < 16; i++) {
			if (m_pExplosion[i][DIRECTION_DOWN]->getActive()) {
				for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
					iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall) {
					if (CollisionManager::CollisionRact(m_pExplosion[i][DIRECTION_DOWN]->GetTransform(),
						(*iterWall)->GetTransform())) {
						collision = true;
						break;
					}
				}
			}
		}
		for (int i = 9; i < 12; i++) {
			if (m_pBossExplosion[i]->getActive())
				if (m_pBossExplosion[i]->GetPosition().y + m_pBossExplosion[i]->GetScale().y > CONSOL_MAX_HEIGHT) {
					collision = true;
					break;
				}
		}
		break;
	}

	return collision;
}

//적 충돌
bool ObjectManager::enemyCollision(){
	bool collision = false;
	//적들 플레이어 충돌
	for (int i = 0; i < 16; i++) {
		if (m_pEnemy[i]->getActive() &&
			CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pEnemy[i]->GetTransform())) {
			Player::PlayerHp = EMPTYHP;
			collision = true;
			break;
		}
	}
	//적들 벽 충돌
	for (int j = 0; j < 16; j++) {
		for (list<Object*>::iterator iterWall = (*ObjectList.find(WALL)).second.begin();
			iterWall != (*ObjectList.find(WALL)).second.end(); ++iterWall) {
			if (m_pEnemy[j]->getActive() && CollisionManager::CollisionRact(m_pEnemy[j]->GetTransform(), (*iterWall)->GetTransform())) {
				collision = true;
				break;
			}
		}
	}
	//적들 상자 충돌
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < box_cnt; i++) {
			if (m_pEnemy[j]->getActive() && CollisionManager::CollisionRact(m_pEnemy[j]->GetTransform(), m_pBox[i]->GetTransform())) {
				collision = true;
				break;
			}
		}
	}
	//적들 적들 충돌
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			if (i != j && m_pEnemy[j]->getActive() && CollisionManager::CollisionRact(m_pEnemy[j]->GetTransform(), m_pEnemy[i]->GetTransform())) {
				collision = true;
				break;
			}
		}
	}
	//적들 폭탄 충돌
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if ((m_pEnemy[i]->getActive() && m_pBomb[j]->getActive() &&
				CollisionManager::CollisionRact(m_pEnemy[i]->GetTransform(), m_pBomb[j]->GetTransform()))) {
				collision = true;
				break;
			}
		}
	}
	//적들 아이템 충돌
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 16; j++) {
			if (m_pItem[i]->getActive() && !collision &&
				CollisionManager::CollisionRact(m_pItem[i]->GetTransform(), m_pEnemy[j]->GetTransform())) {
				m_pItem[i]->setActive(false);
				m_pItem[i]->SetPosition(0, 0);
				break;
			}
		}
	}

	return collision;
}

//보스 충돌
bool ObjectManager::bossCollision()
{
	bool collision = false;
	//보스 벽 충돌
	if (m_pBoss->GetPosition().x < 0 || m_pBoss->GetPosition().x > 84.0f || m_pBoss->GetPosition().y < 0 || m_pBoss->GetPosition().y > 42.0f)
		collision = true;
	//보스 플레이어 충돌
	if (CollisionManager::CollisionRact((*(*ObjectList.find(PLAYER)).second.begin())->GetTransform(), m_pBoss->GetTransform())) {
		Player::PlayerHp = EMPTYHP;
	}
	//보스 아이템 충돌
	for (int i = 0; i < 32; i++) {
		if (m_pItem[i]->getActive() && CollisionManager::CollisionRact(m_pItem[i]->GetTransform(), m_pBoss->GetTransform())) {
			m_pItem[i]->setActive(false);
			m_pItem[i]->SetPosition(0, 0);
		}
	}

	return collision;
}

//보스 타게팅
Vector3 ObjectManager::bossTargetMove()
{
	Vector3 vTarget = (*(*ObjectList.find(PLAYER)).second.begin())->GetPosition();
	Vector3 vBoss = m_pBoss->GetPosition();

	float x = vTarget.x - vBoss.x;
	float y = vTarget.y - vBoss.y;

	float r = sqrt((x * x) + (y * y));

	x /= r;
	y /= r;

	return Vector3(x, y);
}

//폭탄 생성 위치조정
Transform ObjectManager::bombTransInfo(const Transform& _m_pPlayer_TransInfo)
{
	Transform _m_pBomb_TransInfo;
	int rest = _m_pPlayer_TransInfo.Position.x;
	int result = _m_pPlayer_TransInfo.Position.x;
	rest %= 6;
	result /= 6;

	if (rest > 3)	_m_pBomb_TransInfo.Position.x = 6 * (result + 1);
	else _m_pBomb_TransInfo.Position.x = 6 * result;

	rest = _m_pPlayer_TransInfo.Position.y;
	result = _m_pPlayer_TransInfo.Position.y;
	rest %= 3;
	result /= 3;
	if (rest >= 2)	_m_pBomb_TransInfo.Position.y = 3 * (result + 1);
	else _m_pBomb_TransInfo.Position.y = 3 * result;

	return _m_pBomb_TransInfo;
}