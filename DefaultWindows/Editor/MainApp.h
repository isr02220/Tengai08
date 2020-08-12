#pragma once
#include "framework.h"
class CObj;
class CPlayer;
class CMainApp final {
public:
	CMainApp();
	~CMainApp();

public:
	void Ready();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
private:
	HDC m_hDC;
	DWORD m_dwOldTime = 0;
	CPlayer* m_pPlayer = nullptr;
};

