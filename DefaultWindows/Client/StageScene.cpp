#include "StageScene.h"
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
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
	// Player
	m_pPlayer = new CPlayer();
	m_pPlayer->Ready();
	objMgr->AddObject(CAbstractFactory<CPlayer>::Create(300.f, 300.f), OBJ::PLAYER);
	objMgr->AddObject(CAbstractFactory<CMonster>::Create(500.f, 300.f), OBJ::MONSTER);
	objMgr->AddObject(CAbstractFactory<CLifeUI>::Create(), OBJ::UI);
	objMgr->AddObject(CAbstractFactory<CBombUI>::Create(), OBJ::UI);
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
