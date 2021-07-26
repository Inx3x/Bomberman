#pragma once
#include "Object.h"
class Item : public Object
{
public:
	Item();
	virtual ~Item();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

