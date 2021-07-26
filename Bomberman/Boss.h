#pragma once
#include "Object.h"
class Boss : public Object
{
private:
	char* Boss_Texture[9];
	char* Boss_Hp;
	Vector3 Boss_Hp_Position;
	bool Jumping;
	bool Targetting;

	bool m_Jump;
	float m_Power;
	float m_OldY;
	float m_Time;
	ULONGLONG PatternTime;
	int Pattern_cnt;
public:
	static int CurrentBossState;
	static int PreviousBossState;

	Boss();
	virtual ~Boss();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

	void State();
	void StateChange();
	void randomMove();
	void targetMove();
	void Jump();
	void Skill();
};

