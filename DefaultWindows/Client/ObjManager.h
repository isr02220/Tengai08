#pragma once
#pragma warning(disable: 4351)
class CObj;
class CObjManager {
public:
	static CObjManager* GetInstance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CObjManager;

		return m_pInstance;
	}
	static void Destroy_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CObjManager();
	~CObjManager();
public:
//	CObj* GetPlayer() { return m_listObj[OBJ::PLAYER].front(); }
//	list<CObj*>* GetList(OBJ::TYPE eID) { return &m_listObj[eID]; }
//	vector<CObj*>* GetVector(OBJ::TYPE eID) { return &vecObj[eID]; }
//public:
//	void AddObject(CObj* pObj, OBJ::TYPE eID);
//	void InsertObject(CObj* pObj, OBJ::TYPE eID);
public:
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
private:
	static CObjManager* m_pInstance;
private:
	//list<CObj*> m_listObj[OBJ::END];
	//vector<CObj*> vecObj[OBJ::END];
};

