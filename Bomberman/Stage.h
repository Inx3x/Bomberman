#pragma once
#include "Scene.h"

class Object;
class Stage : public Scene
{
private:
	ULONGLONG Time;
	int time_cnt;
	char* Clear[7];
	char* GameOver[7];
public:
	Stage();
	virtual ~Stage();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};

