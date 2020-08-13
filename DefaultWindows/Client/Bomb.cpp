#include "Obj.h"
#include "Player.h"
#include "Bomb.h"
#include "BombBullet.h"

CBomb::CBomb() : CObj() {
	objectType = OBJ::BOMB;
	lstrcpy(info->name, L"ÆøÅº");
}

CBomb::~CBomb() {

}

void CBomb::Ready() {
	info->force.x = 1.f;
	speed = 10.f;
	info->size = { 30.f, 50.f, 0.f };
	SetFillColor  (RGB(232, 60, 40));
	SetStrokeColor(RGB(230, 0, 0  ));
	timer = GetTickCount();
	BombBulletTimer = GetTickCount();

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };
}

INT CBomb::Update() {
	CObj::UpdateRect();
	if (dead)
		return STATE::DEAD;
	if (timer + 1000 < GetTickCount()) {
		info->size = { 500.f, 500.f, 0.f };
		if (BombBulletTimer + 120 < GetTickCount()) {
			BombBulletTimer = GetTickCount();
			CObj* bulletObj = new CBombBullet();
			bulletObj->SetFillColor(RGB(0, 60, 40));
			bulletObj->SetStrokeColor(RGB(0, 50, 200));
			bulletObj->SetPosition(info->position);
			CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);

			if (timer + 4000 < GetTickCount()) {
				SetDead();
				dynamic_cast<CPlayer*>(CObjManager::GetInstance()->GetPlayer())->SetBombEnable();
			}
		}
		SetVisible(false);
	}
	else {
		SetVisible(true);
		info->position += info->force * speed;
		angleRot += 10.f;
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&m_matRotation, D3DXToRadian(angleRot));
		D3DXMatrixTranslation(&m_matTransform, info->position.x, info->position.y, info->position.z);
		D3DXMatrixRotationZ(&m_matRevolution, D3DXToRadian(angleRev));

		D3DXMatrixIdentity(&m_matW);
		m_matW = m_matScale * m_matRotation * m_matTransform * m_matRevolution;
		//m_matW = m_matScale * m_matTransform;

		for (size_t i = 0; i < 4; i++) {
			D3DXVec3TransformCoord(&globalVertex[i], &localVertex[i], &m_matW);
		}

		// Rect
		D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
		D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
		SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
	}


	return STATE::NO_EVENT;
}

void CBomb::LateUpdate() {
}

void CBomb::Render(HDC hDC) {
	CObj::UpdateRect();

	HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
	HBRUSH hBrush = CreateSolidBrush(fillColor);

	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	DrawPolygon(hDC);
	//Ellipse(hDC, rect->left, rect->top, rect->right, rect->bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CBomb::Release() {
}

void CBomb::OnCollision(CObj* _TargetObj) {

}
