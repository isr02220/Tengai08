#pragma once
class CScene; 
class CSceneManager
{
public:
	static CSceneManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneManager;
		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
public:
	enum ID {SCENE_LOGO, SCENE_MENU, SCENE_STAGE, SCENE_END};

private:
	CSceneManager();
	~CSceneManager();

public:
	void Update(); 
	void LateUpdate(); 
	void Render(HDC hDC); 
	void Release();

	void ChangeScene(ID eSceneID);

private:
	static CSceneManager* m_pInstance;
	CScene* m_pScene = nullptr; 
	ID		m_eCurScene = SCENE_END;
	ID		m_eNextScene = SCENE_END; 
};

