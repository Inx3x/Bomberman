#pragma once
#include "Headers.h"

class Object;
class ObjectManager
{
private:
	ObjectManager();
	static ObjectManager* m_pInstance;

	//¸Ê »ý¼º
	map<string, list<Object*>> ObjectList;

	int stage_cnt;

	//Object* m_pWall[128];
	int wall_cnt;

	Object* m_pBox[64];
	int box_cnt;

	Object* m_pItem[32];
	int item_cnt;
	int item_hp[32];

	Object* m_pBomb[16];
	int bomb_cnt;
	int bomb_capacity;
	
	Object* m_pExplosion[16][4];
	Object* m_pBossExplosion[12];

	Object* m_pEnemy[16];

	Object* m_pBoss;

public:
	static int Enemy_cnt;
	static ObjectManager* GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new ObjectManager;
		return m_pInstance;
	}

	void AddObject(Object* _obj);
	void Initialize();
	void Update();
	void Render();
	void Release();

	void createWall();
	void createBox();
	void createItem(const Transform&);
	void createBomb();
	void createExplosion(const Vector3&);
	void createBossExplosion(const Vector3&);
	void createEnemy();

	void explosionCollision();
	void setBombCnt();
	
	bool playerCollision();
	bool explosionRange(const int&);
	bool enemyCollision();
	bool bossCollision();
	Vector3 bossTargetMove();

	Transform bombTransInfo(const Transform&);

	~ObjectManager();
};