#pragma once
#include "Object.h"
class Wall : public Object
{
public:
	Wall();
	virtual ~Wall();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

