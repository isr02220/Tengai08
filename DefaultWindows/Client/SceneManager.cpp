#include "framework.h"
#include "Scene.h"
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
	// ¾ÀÀ» »ý¼ºÇÏ°í ¸¸µé°í ¹¹½Ã±â ÇÒ²¨. 
	m_eNextScene = eSceneID;
	if (m_eCurScene != m_eNextScene)
	{
		Safe_Delete(m_pScene); 
		switch (m_eNextScene)
		{
		case CSceneManager::SCENE_LOGO:
			//m_pScene = new CLogo;
			break;
		case CSceneManager::SCENE_MENU:
			//m_pScene = new CMyMenu; 
			break;
		case CSceneManager::SCENE_STAGE:
			//m_pScene = new CStage;
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
