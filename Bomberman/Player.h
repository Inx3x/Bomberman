#pragma once
#include "Object.h"
class Player : public Object
{
public:
	static int PlayerHp;
	Player();
	virtual ~Player();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

	void CheckKey();
	void State();
};

