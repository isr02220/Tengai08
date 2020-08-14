#include "Pet.h"
#include "Bullet.h"
#include "Effect.h"

void CPet::Ready() {
	info = new INFO();
	SetName(L"Æê");
	info->size = { 50.f, 35.f , 0.f };
	info->force = { 0.f, 0.f , 0.f };
	info->look = { 1.f, 0.f, 0.f };
	SetFillColor(RGB(133, 184, 235));
	SetStrokeColor(RGB(82, 82, 235));
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	rect = new RECT();
	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);

}

INT CPet::Update() {
	if (dead)
		return STATE::DEAD;


	// Move
	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	if(m_playerObj)
		info->position = *(m_playerObj->GetPosition()) + D3DXVECTOR3(-20.f, -60.f, 0.f);

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

	return STATE::NO_EVENT;
}

void CPet::LateUpdate() {

}

void CPet::Render(HDC hDC) {
	HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
	HBRUSH hBrush = CreateSolidBrush(fillColor);
	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	DrawPolygon(hDC);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CPet::Release() {

}

void CPet::OnCollision(CObj* _TargetObj) {

}

void CPet::Move() {
}

void CPet::Attack() {

}

void CPet::Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, D3DXVECTOR3 _posoffset, COLORREF _fillColor, COLORREF _strokeColor) {
	CObj* bulletObj = new CBullet(_degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position + _posoffset);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);
}

void CPet::Shoot(CObj* _targetObj, FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, D3DXVECTOR3 _posoffset, COLORREF _fillColor, COLORREF _strokeColor) {
	D3DXVECTOR3 v3Dir = *_targetObj->GetPosition() - info->position;
	FLOAT degree = _degree + D3DXToDegree(atan2f(v3Dir.y, v3Dir.x));

	CObj* bulletObj = new CBullet(degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position + _posoffset);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);
}