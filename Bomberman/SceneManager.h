#pragma once
#include "Headers.h"
class Scene;
class SceneManager
{
private:
	static SceneManager* m_pInstance;
	SceneManager();
	Scene* m_pSceneState;
public:
	static SceneManager* GetInstance() {
		if (m_pInstance == NULL)	m_pInstance = new SceneManager;
		return m_pInstance;
	}

	~SceneManager();

	void SetScene(const SCENEID&);
	void Update();
	void Render();
	void Release();
};

