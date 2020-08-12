#include "BombUI.h"
#include "UI.h"
#include "Player.h"
CBombUI::CBombUI() : CUI() {

}

CBombUI::~CBombUI() {

}

void CBombUI::Ready() {

}

INT CBombUI::Update() {

	return 0;
}

void CBombUI::LateUpdate() {
}

void CBombUI::Render(HDC hDC) {
	CObj::UpdateRect();
	TCHAR szBuffer[32];
	wsprintf(szBuffer, L"ÆøÅº");
	for (INT i = 0; i < dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->GetBombCount(); i++) {
		RECT rc = {};
		rc.left = (WINCX >> 1) + 100 + i * 70;
		rc.right = (WINCX >> 1) + 150 + i * 70;
		rc.top = 100;
		rc.bottom = 150;
		Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
		rc.top = 120;
		DrawText(hDC, szBuffer, lstrlen(szBuffer), &rc, DT_VCENTER | DT_CENTER | DT_NOCLIP);
	}
}

void CBombUI::Release() {
}

void CBombUI::OnCollision(CObj* _TargetObj) {

}