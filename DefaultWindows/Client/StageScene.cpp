#include "StageScene.h"
#include "Obj.h"
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Obj.h"
#include "PatternStruct.h"
#include "MonsterList.h"
#include "UI.h"
#include "LifeUI.h"
#include "BombUI.h"
CStageScene::CStageScene() : CScene() {
}

CStageScene::~CStageScene() {
	Release();
}

void CStageScene::Ready() {

	SetActive(true);

	m_dwStartTime = GetTickCount();

// Player
	m_pPlayer = new CPlayer();
	m_pPlayer->Ready();
	objMgr->AddObject(CAbstractFactory<CPlayer>::Create(300.f, 300.f), OBJ::PLAYER);

// Monster
	for (int i = 0; i < iMobListSize; i++) {
		stMonsterInfo* pMobList = new stMonsterInfo;
		*pMobList = MobList[i];
		m_listMonsterStandby.push_back(pMobList);
	}
	objMgr->AddObject(CAbstractFactory<CBackground>::Create(), OBJ::BACKGROUND);
	objMgr->AddObject(CAbstractFactory<CLifeUI>::Create(), OBJ::UI);
	objMgr->AddObject(CAbstractFactory<CBombUI>::Create(), OBJ::UI);
}

void CStageScene::Update() {

	// 몬스터 등장
	DWORD dwCurTime = GetTickCount();
	list<stMonsterInfo*>::iterator iter = m_listMonsterStandby.begin();

	while (iter != m_listMonsterStandby.end())
	{
		if (m_dwStartTime + (*iter)->dwStartTime > dwCurTime) {
			break;
		}
		//CMonster* pMonster = new CMonster(*iter);
		//m_listObject[OBJ::MONSTER].emplace_back(dynamic_cast<CObj*>(pMonster));

		CObj* pObject = CAbstractFactory<CMonster>::Create();
		dynamic_cast<CMonster*>(pObject)->SetInfo(*iter);

		objMgr->AddObject(pObject, OBJ::MONSTER);

		iter = m_listMonsterStandby.erase(iter);
	}

	objMgr->Update();
}

void CStageScene::LateUpdate() {
	objMgr->LateUpdate();
}

void CStageScene::Render(HDC hDC) {
	objMgr->Render(hDC);
}

void CStageScene::Release() {
	SafeDelete(m_pPlayer);
	SetActive(false);
}
