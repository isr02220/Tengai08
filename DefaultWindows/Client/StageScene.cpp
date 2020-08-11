#include "StageScene.h"
#include "Player.h"
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

}

void CStageScene::Update() {

	m_pPlayer->Update();
}

void CStageScene::LateUpdate() {
	m_pPlayer->LateUpdate();

}

void CStageScene::Render(HDC hDC) {

	RECT rc = { 0,0, WINCX, WINCY };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	DrawText(hDC, L"TENGAI", lstrlen(L"TENGAI"), &rc, DT_VCENTER | DT_NOCLIP);
}

void CStageScene::Release() {
	SafeDelete(m_pPlayer);
	SetActive(false);
}
