#pragma once
#include "Object.h"
class Explosion : public Object
{
public:
	Explosion();
	virtual ~Explosion();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

