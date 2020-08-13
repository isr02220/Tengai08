#include "BombBullet.h"
#include "Bullet.h"
#include "Player.h"
#include "Monster.h"

CBombBullet::CBombBullet()
	: CBullet(0.f, 0.f, 50, 500) {
	objectType = OBJ::BULLET;
	lstrcpy(info->name, L"ÆøÅº ÃÑ¾Ë");
	info->size = { (FLOAT)500, (FLOAT)500 , 0.f };

	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

CBombBullet::~CBombBullet() {

}

void CBombBullet::Ready() {
}

int CBombBullet::Update() {
	CObj::UpdateRect();
	
	if (dead)
		return STATE::DEAD;
	
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);

	info->size *= 0.9f;
	if (info->size.x < 400.f)
		objectType = OBJ::EFFECT;
	if (info->size.x < 200.f)
		SetFillColor(RGB(30, 128, 192));
	if (info->size.x < 100.f)
		SetFillColor(RGB(60, 150, 255));
	else if (info->size.x < 0.1f)
		SetDead();
	return STATE::NO_EVENT;
}

void CBombBullet::LateUpdate() {
}

void CBombBullet::Render(HDC hDC) {
	CObj::UpdateRect();

	HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
	HBRUSH hBrush = CreateSolidBrush(fillColor);

	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC, rect->left, rect->top, rect->right, rect->bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CBombBullet::Release() {
}

void CBombBullet::OnCollision(CObj* _SrcObj) {

}
