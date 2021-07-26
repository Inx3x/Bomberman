#include "SceneManager.h"
#include "Logo.h"
#include "Intro_Stage.h"
#include "Stage.h"
#include "Ending.h"

SceneManager* SceneManager::m_pInstance = NULL;


SceneManager::SceneManager() : m_pSceneState(NULL)
{
}

SceneManager::~SceneManager()
{
	Release();
}


void SceneManager::SetScene(const SCENEID& _SceneID)
{
	SAFE_RELEASE(m_pSceneState);

	switch (_SceneID)
	{
	case LOGO:
		m_pSceneState = new Logo;
		break;
	case INTRO_STAGE:
		m_pSceneState = new Intro_Stage;
		break;
	case STAGE:
		m_pSceneState = new Stage;		
		break;
	case ENDING:
		m_pSceneState = new Ending;
		break;
	case EXIT:
		exit(NULL);
		break;
	}

	m_pSceneState->Initialize();
}

void SceneManager::Update()
{
	m_pSceneState->Update();
}

void SceneManager::Render()
{
	m_pSceneState->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(m_pSceneState);
}