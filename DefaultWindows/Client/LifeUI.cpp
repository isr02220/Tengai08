#include "LifeUI.h"
#include "UI.h"
#include "Player.h"
CLifeUI::CLifeUI() : CUI() {

}

CLifeUI::~CLifeUI() {

}

void CLifeUI::Ready() {

}

INT CLifeUI::Update() {

	return 0;
}

void CLifeUI::LateUpdate() {
}

void CLifeUI::Render(HDC hDC) {
	CObj::UpdateRect();
	TCHAR szBuffer[32];
	wsprintf(szBuffer, L"¸ñ¼û");
	for (INT i = 0; i < dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->GetHP(); i++) {
		RECT rc = {};
		rc.left = 100 + i * 70;
		rc.right = 150 + i * 70;
		rc.top = 100;
		rc.bottom = 150;
		Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
		rc.top = 115;
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_VCENTER | DT_CENTER | DT_NOCLIP);
	}
}

void CLifeUI::Release() {
}

void CLifeUI::OnCollision(CObj* _TargetObj) {

}