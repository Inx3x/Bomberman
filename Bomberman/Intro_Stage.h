#pragma once
#include "Scene.h"
class Intro_Stage : public Scene
{
private:
	char* Text;
	Vector3 Text_Position;
	Vector3 stage_No_Position;
	ULONGLONG Time;
public:
	Intro_Stage();
	virtual ~Intro_Stage();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

