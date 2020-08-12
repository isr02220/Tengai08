#include "Monster.h"
#include "Bullet.h"

void CMonster::Ready() {
	info = new INFO();
    SetName(L"몬스터");
	info->position = { 500.f, 600.f , 0.f };
	info->size = { 100.f, 100.f , 0.f };
	info->force = { 0.f, 0.f , 0.f };
	info->look = { 1.f, 0.f, 0.f };
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	rect = new RECT();

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

INT CMonster::Update() {
    if (dead)
        return STATE::DEAD;

	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);

	Move();
	Attack();
	// 확인용 총알 발사 //
	Shoot(180.f, 10.f, 20, 10);
	//Shoot(CObjManager::GetInstance()->GetPlayer(),0.f, 10.f, 20, 10);
	//////////////////////

    return STATE::NO_EVENT;
}

void CMonster::LateUpdate() {

}

void CMonster::Render(HDC hDC) {
	HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
	HBRUSH hBrush = CreateSolidBrush(fillColor);

	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, rect->left, rect->top, rect->right, rect->bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CMonster::Release() {

}

void CMonster::OnCollision(CObj* _TargetObj) {

}

void CMonster::Move() {
}

void CMonster::Attack() {
}

void CMonster::Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size) {
	CObj* bulletObj = new CBullet(_degree, _speed, _damage, _size);
	bulletObj->SetPosition(info->position);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);
}

void CMonster::Shoot(CObj* _targetObj, FLOAT _degree, FLOAT _speed, INT _damage, LONG _size) {
	D3DXVECTOR3 v3Dir = *_targetObj->GetPosition() - info->position;
	FLOAT degree = _degree + D3DXToDegree(atan2f(v3Dir.y, v3Dir.x));

	CObj* bulletObj = new CBullet(degree, _speed, _damage, _size);
	bulletObj->SetPosition(info->position);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::MONSTERBULLET);
}