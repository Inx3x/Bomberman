#pragma once
#include "Scene.h"
class Ending : public Scene
{
private:
	char* Text;
	Vector3 Text_Position;
	ULONGLONG Time;
public:
	Ending();
	virtual ~Ending();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

