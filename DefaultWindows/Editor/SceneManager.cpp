#include "framework.h"
#include "Scene.h"
#include "LogoScene.h"
#include "StageScene.h"
#include "SceneManager.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;
CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::ChangeScene(ID eSceneID)
{
	// ���� �����ϰ� ����� ���ñ� �Ҳ�. 
	m_eNextScene = eSceneID;
	if (m_eCurScene != m_eNextScene)
	{
		SafeDelete(m_pScene); 
		switch (m_eNextScene)
		{
		case CSceneManager::SCENE_LOGO:
			m_pScene = new CLogoScene;
			break;
		case CSceneManager::SCENE_MENU:
			//m_pScene = new CMyMenu; 
			break;
		case CSceneManager::SCENE_STAGE:
			m_pScene = new CStageScene;
			break;
		case CSceneManager::SCENE_END:
			return;
		default:
			break;
		}
		m_pScene->Ready();
		m_eCurScene = m_eNextScene; 
	}
}

void CSceneManager::Update()
{
	m_pScene->Update(); 
}

void CSceneManager::LateUpdate()
{
	m_pScene->LateUpdate(); 
}

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC); 
}

void CSceneManager::Release()
{
	SafeDelete(m_pScene); 
}
