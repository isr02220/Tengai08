#include "framework.h"
#include "ObjManager.h"
#include "Obj.h"
CObjManager* CObjManager::m_pInstance = nullptr;

CObjManager::CObjManager() {
}


CObjManager::~CObjManager() {
	Release();
}

void CObjManager::AddObject(CObj* pObj, OBJ::TYPE eID) {
	m_listObj[eID].emplace_back(pObj);
}

void CObjManager::Update() {
	for (size_t i = 0; i < OBJ::END; ++i) {
		auto iter_end = m_listObj[i].end();
		for (auto iter = m_listObj[i].begin(); iter != iter_end; ) {
			int iEvent = (*iter)->Update();
			if (STATE::DEAD == iEvent) {
				SafeDelete(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjManager::LateUpdate() {
	//CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::ITEM]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::MONSTER], m_listObj[OBJ::BULLET]);
	CCollisionManager::CollisionPoint(m_listObj[OBJ::PLAYER].front(), m_listObj[OBJ::MONSTERBULLET]);
	CCollisionManager::CollisionSphere(m_listObj[OBJ::BOMB], m_listObj[OBJ::MONSTERBULLET]);
	//CCollisionManager::CollisionRectEX(m_listObj[OBJ::PLAYER], m_listObj[OBJ::BELT]);

	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i]) {
			pObj->LateUpdate();
		}
	}
}

void CObjManager::Render(HDC hDC) {

	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i]) {
			if (pObj->GetVisible())
				pObj->Render(hDC);
		}
	}
}

void CObjManager::Release() {
	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i])
			SafeDelete(pObj);
		m_listObj[i].clear();
	}
}