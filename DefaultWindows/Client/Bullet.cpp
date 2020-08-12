#include "Bullet.h"
#include "Player.h"
#include "Monster.h"

CBullet::CBullet(FLOAT _degree, FLOAT _speed, INT _damage, LONG _bulletSize)
	: CObj()
	, m_damage(_damage) {
	objectType = OBJ::BULLET;
	lstrcpy(info->name, L"총알");
	info->size = { (FLOAT)_bulletSize, (FLOAT)_bulletSize , 0.f };
	speed = _speed;
	float rad = D3DXToRadian(_degree);
	info->force = { cosf(rad), sinf(rad), 0.f };

	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	//gravity = 1.2f;
	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

CBullet::~CBullet() {

}

void CBullet::Ready() {
}

int CBullet::Update() {
	//if (dead ||
	//	rect->left < DeadLineMargin ||
	//	rect->top < DeadLineMargin ||
	//	rect->right > WINCX - DeadLineMargin ||
	//	rect->bottom > WINCY - DeadLineMargin)
	//	return STATE_DEAD;
	if (dead)
		return STATE::DEAD;

	CObj::UpdateRect();
	info->position += info->force * speed;

	return STATE::NO_EVENT;
}

void CBullet::LateUpdate() {
}

void CBullet::Render(HDC hDC) {
	CObj::UpdateRect();
	if (isVisible) {
		Ellipse(hDC, rect->left, rect->top, rect->right, rect->bottom);

	}
}

void CBullet::Release() {
}

void CBullet::OnCollision(CObj* _SrcObj) {
	SetDead();
}
