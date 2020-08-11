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
	//CCollisionManager::CollisionBelt(m_listObj[OBJ::PLAYER]);
	//CCollisionManager::CollisionBelt(m_listObj[OBJ::ITEM]);
	//CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::ITEM]);
	//CCollisionManager::CollisionSphere(m_listObj[OBJ::MONSTER], m_listObj[OBJ::BULLET]);
	//CCollisionManager::CollisionSphere(m_listObj[OBJ::PLAYER], m_listObj[OBJ::MONSTERBULLET]);
	//CCollisionManager::CollisionRectEX(m_listObj[OBJ::PLAYER], m_listObj[OBJ::BELT]);
	//CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), m_listObj[OBJ::PLAYER]);
	//CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::RESOURCEORE]);
	//CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::BELT]);
	//CCollisionManager::CollisionPoint(m_listObj[OBJ::MOUSE].front(), vecObj[OBJ::ENTITY]);

	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i]) {
			pObj->LateUpdate();
		}
	}
}

void CObjManager::Render(HDC hDC) {

}

void CObjManager::Release() {
	for (int i = 0; i < OBJ::END; ++i) {
		for (auto& pObj : m_listObj[i])
			SafeDelete(pObj);
		m_listObj[i].clear();
	}
}