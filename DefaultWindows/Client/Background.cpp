#include "Background.h"

void CBackground::Ready() {
	for (size_t i = 0; i < 50; i++) {
		m_ListBgFar.emplace_back(new CBgObj(i * 100 + (rand() % 50), 400 + (rand() % 200), (i + 1) * 100, WINCY));
		m_ListBgMiddle.emplace_back(new CBgObj(i * 200 + (rand() % 100), 500 + (rand() % 100), (i + 1) * 200, WINCY));
		m_ListBgClose.emplace_back(new CBgObj(i * 300 + (rand() % 200), 600 + (rand() % 100), (i + 1) * 300, WINCY));
	}
}

INT CBackground::Update() {
	for (auto bgObj : m_ListBgFar) {
		bgObj->MoveRect(-0.25f * speed, 0.f);
		if (bgObj->rect.right < 0.f)
			bgObj->MoveRect(5100.f, 0.f);
		else if (bgObj->rect.right > 5100.f)
			bgObj->MoveRect(-5100.f, 0.f);
	}
	for (auto bgObj : m_ListBgMiddle) {
		bgObj->MoveRect(-0.5f * speed, 0.f);
		if (bgObj->rect.right < 0.f)
			bgObj->MoveRect(10200.f, 0.f);
		else if (bgObj->rect.right > 10200.f)
			bgObj->MoveRect(-10200.f, 0.f);

	}
	for (auto bgObj : m_ListBgClose) {
		bgObj->MoveRect(-1.0f * speed, 0.f);
		if (bgObj->rect.right < 0.f)
			bgObj->MoveRect(15300.f, 0.f);
		else if (bgObj->rect.right > 15300.f)
			bgObj->MoveRect(-15300.f, 0.f);

	}
    return 0;
}

void CBackground::LateUpdate() {
}

void CBackground::Render(HDC hDC) {
	HPEN   hPenNull = CreatePen(PS_NULL, 1, RGB(26, 26, 26));
	HBRUSH hBrush1 = CreateSolidBrush(RGB(248, 160, 112));
	HBRUSH hBrush2 = CreateSolidBrush(RGB(208, 120, 72));
	HBRUSH hBrush3 = CreateSolidBrush(RGB(168, 80, 32));
	HBRUSH hBrushGreen = CreateSolidBrush(RGB(29, 215, 20));

	HPEN   oldPen = (HPEN)SelectObject(hDC, hPenNull);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush1);

	for (auto bgObj : m_ListBgFar)
		bgObj->Draw(hDC);
	(HBRUSH)SelectObject(hDC, hBrush2);
	for (auto bgObj : m_ListBgMiddle)
		bgObj->Draw(hDC);
	(HBRUSH)SelectObject(hDC, hBrush3);
	for (auto bgObj : m_ListBgClose)
		bgObj->Draw(hDC);
	(HBRUSH)SelectObject(hDC, hBrushGreen);
	for (auto bgObj : m_ListBgClose) {
		FLOAT offsetLeft   = -20;
		FLOAT offsetTop    = -80;
		FLOAT offsetRight  = 20;
		FLOAT offsetBottom = -80;
		bgObj->OffsetRect(offsetLeft, offsetTop, offsetRight, offsetBottom);
		bgObj->Draw(hDC);
		bgObj->OffsetRect(-offsetLeft, -offsetTop, -offsetRight, -offsetBottom);
	}

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPenNull);
	DeleteObject(hBrush1);
	DeleteObject(hBrush2);
	DeleteObject(hBrush3);
}

void CBackground::Release() {
	for (auto& bgObj : m_ListBgFar)
		SafeDelete(bgObj);
	for (auto& bgObj : m_ListBgMiddle)
		SafeDelete(bgObj);
	for (auto& bgObj : m_ListBgClose)
		SafeDelete(bgObj);
}

void CBackground::OnCollision(CObj* _TargetObj) {
}
