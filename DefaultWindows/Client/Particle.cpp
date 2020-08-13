#include "Particle.h"
#include "Player.h"
#include "Monster.h"

CParticle::CParticle(const FLOAT& _degree, const FLOAT& _speed, const LONG& _size)
	: CObj() {
	objectType = OBJ::EFFECT;
	lstrcpy(info->name, L"ÆÄÆ¼Å¬");
	info->size = { (FLOAT)_size, (FLOAT)_size , 0.f };
	speed = _speed;
	float rad = D3DXToRadian(_degree);
	info->force = { cosf(rad), sinf(rad), 0.f };

	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

CParticle::~CParticle() {

}

void CParticle::Ready() {

}

int CParticle::Update() {
	CObj::UpdateRect();
	if (dead)
		return STATE::DEAD;
	info->position += info->force * speed;

	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	angleRot += 15.f;
	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&m_matRotation, D3DXToRadian(angleRot));
	D3DXMatrixTranslation(&m_matTransform, info->position.x, info->position.y, info->position.z);
	D3DXMatrixRotationZ(&m_matRevolution, D3DXToRadian(angleRev));

	D3DXMatrixIdentity(&m_matW);
	m_matW = m_matScale * m_matRotation * m_matTransform * m_matRevolution;

	for (size_t i = 0; i < 4; i++) {
		D3DXVec3TransformCoord(&globalVertex[i], &localVertex[i], &m_matW);
	}
	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
	return STATE::NO_EVENT;
}

void CParticle::LateUpdate() {
}

void CParticle::Render(HDC hDC) {
	CObj::UpdateRect();

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

void CParticle::Release() {
}

void CParticle::OnCollision(CObj* _SrcObj) {
	SetDead();
}
