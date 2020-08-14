#include "EndScene.h"
#include "SceneManager.h"

CEndScene::CEndScene() : CScene()
{
}

CEndScene::~CEndScene()
{
	Release();
}

void CEndScene::Ready()
{
	SetActive(true);
}

void CEndScene::Update()
{
}

void CEndScene::LateUpdate()
{
}

void CEndScene::Render(HDC hDC)
{
	RECT rc = { 0,WINCY >> 1, WINCX, WINCY };
	//AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	DrawText(hDC, L"END", lstrlen(L"END"), &rc, DT_VCENTER | DT_CENTER | DT_NOCLIP);
}

void CEndScene::Release()
{
	SetActive(false);
}
