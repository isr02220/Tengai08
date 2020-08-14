#include "LogoScene.h"
#include "SceneManager.h"
CLogoScene::CLogoScene() : CScene() {

}

CLogoScene::~CLogoScene() {
	Release();
}

void CLogoScene::Ready() {
	SetActive(true);

}

void CLogoScene::Update() {
	if (CKeyManager::GetInstance()->OnPress(KEY::PrimaryAction)) {
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_STAGE);
	}
}

void CLogoScene::LateUpdate() {

}

void CLogoScene::Render(HDC hDC) {

	RECT rc = { 0, WINCY >> 1, WINCX, WINCY };
	//AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	DrawText(hDC, L"TENGAI", lstrlen(L"TENGAI"), &rc, DT_VCENTER | DT_CENTER | DT_NOCLIP);
}

void CLogoScene::Release() {
	SetActive(false);
}
