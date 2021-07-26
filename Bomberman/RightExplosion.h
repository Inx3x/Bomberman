#pragma once
#include "Object.h"
class RightExplosion : public Object
{
private:
	char* m_pExplosion[3];
	int Explosion_Color;

public:
	RightExplosion();
	virtual ~RightExplosion();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

