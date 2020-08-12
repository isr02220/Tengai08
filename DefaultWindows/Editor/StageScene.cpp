#include "StageScene.h"
#include "Player.h"
#include "Monster.h"
#include "Obj.h"
CStageScene::CStageScene() : CScene() {

}

CStageScene::~CStageScene() {
	Release();
}

void CStageScene::Ready() {
	SetActive(true);
	// Player
	m_pPlayer = new CPlayer();
	m_pPlayer->Ready();
	objMgr->AddObject(CAbstractFactory<CPlayer>::Create(300.f, 300.f), OBJ::PLAYER);
	objMgr->AddObject(CAbstractFactory<CMonster>::Create(500.f, 300.f), OBJ::MONSTER);
}

void CStageScene::Update() {
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
