#pragma once
#include "Object.h"
class Bomb : public Object
{
public:
	Bomb();
	virtual ~Bomb();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

