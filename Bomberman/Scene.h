#pragma once
#include "Headers.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();	
	
	static int stage_No;

	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	void SetStageNo(const int& _stage_No) { stage_No = _stage_No; }
	int GetStageNo() { return stage_No; }
};

