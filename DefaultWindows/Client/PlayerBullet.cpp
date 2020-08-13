#include "PlayerBullet.h"
#include "Bullet.h"
#include "Player.h"
#include "Monster.h"
#include "Effect.h"
FLOAT CPlayerBullet::staticBulletRotation = 30.f;

CPlayerBullet::CPlayerBullet(const FLOAT& _degree, const FLOAT& _speed, const INT& _damage, const LONG& _bulletSize)
	: CBullet(_degree, _speed, _damage, _bulletSize) {
	objectType = OBJ::BULLET;
	lstrcpy(info->name, L"ÃÑ¾Ë");
	info->size = { (FLOAT)_bulletSize / 2.f, (FLOAT)_bulletSize , 0.f };
	speed = _speed;
	float rad = D3DXToRadian(_degree);
	info->force = { cosf(rad), sinf(rad), 0.f };
	if (staticBulletRotation > 120.f) staticBulletRotation = 30.f;
	staticBulletRotation += 30.f;
	angleRot = staticBulletRotation;

	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

CPlayerBullet::~CPlayerBullet() {

}

void CPlayerBullet::Ready() {
}

int CPlayerBullet::Update() {
	CObj::UpdateRect();
	if (dead ||
		rect->left   <DeadLineMargin ||
		rect->top    <DeadLineMargin ||
		rect->right  >WINCX - DeadLineMargin ||
		rect->bottom >WINCY - DeadLineMargin)
		return STATE::DEAD;
	info->position += info->force * speed;

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

void CPlayerBullet::LateUpdate() {
}

void CPlayerBullet::Render(HDC hDC) {
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

void CPlayerBullet::Release() {
}

void CPlayerBullet::OnCollision(CObj* _SrcObj) {
	//CObj* effect = new CEffect(FLOAT(rand() % 30), 15.f, 15.f, 4, 20);
	//effect->SetPosition(info->position);
	//effect->Ready();
	//CObjManager::GetInstance()->AddObject(effect, OBJ::EFFECT);
	SetDead();
}
