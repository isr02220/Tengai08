#include "MainApp.h"
#include "Player.h"
#include "KeyManager.h"
#include "SceneManager.h"

CMainApp::CMainApp() {
	m_hDC = 0;
}

CMainApp::~CMainApp() {
	Release();
}

void CMainApp::Ready() {
// HDC
	m_hDC = GetDC(g_hWnd);

// Scene
	CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_LOGO);
}

void CMainApp::Update() {
	CKeyManager::GetInstance()->UpdateKeyManager();
	CSceneManager::GetInstance()->Update();
}

void CMainApp::LateUpdate() {
	CSceneManager::GetInstance()->LateUpdate();
}

void CMainApp::Render() {

	HDC hMemDC;
	HBITMAP hBitmap, oldBitmap;
	hMemDC = CreateCompatibleDC(m_hDC);
	hBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	oldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	SetBkMode(hMemDC, TRANSPARENT);
	////////////////
	Rectangle(hMemDC, 0, 0, WINCX, WINCY);
	CSceneManager::GetInstance()->Render(hMemDC);
	/// ////////////
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hMemDC, oldBitmap));
	DeleteDC(hMemDC);
}

void CMainApp::Release() {
	CSceneManager::GetInstance()->Release();
}


