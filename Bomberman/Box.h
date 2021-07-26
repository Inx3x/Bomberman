#pragma once
#include "Object.h"
class Box : public Object
{
public:
	Box();
	virtual ~Box();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

