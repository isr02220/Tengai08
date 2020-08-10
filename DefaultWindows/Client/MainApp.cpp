#include "MainApp.h"
#include "Player.h"
#include "KeyManager.h"
CMainApp::CMainApp() {
	m_hDC = 0;
}

CMainApp::~CMainApp() {
	Release();
}

void CMainApp::Ready() {
	m_hDC = GetDC(g_hWnd);
	m_pPlayer = new CPlayer();
	m_pPlayer->Ready();
}

void CMainApp::Update() {
	m_pPlayer->Update();
	CKeyManager::GetInstance()->UpdateKeyManager();
}

void CMainApp::LateUpdate() {
	m_pPlayer->LateUpdate();
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
	m_pPlayer->Render(hMemDC);

	/// ////////////
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(SelectObject(hMemDC, oldBitmap));
	DeleteDC(hMemDC);
}

void CMainApp::Release() {
	Safe_Delete(m_pPlayer);
}


