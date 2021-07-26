#pragma once
#include "Scene.h"
class Logo : public Scene
{
private:
	char* logo[13];
	char* logo_Title[6];

	Vector3 logo_Position;
	Vector3 logo_Title_Position;
	
	int logo_Title_Color;
	
	ULONG Time;
	int count_y;

public:
	Logo();
	virtual ~Logo();

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
};