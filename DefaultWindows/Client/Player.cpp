#include "framework.h"
#include "KeyManager.h"
#include "Player.h"
#include "Bullet.h"

CPlayer::CPlayer() : CObj(){

}

CPlayer::~CPlayer() {
	Release();
}

void CPlayer::Ready() {
	lstrcpy(info->name, L"플레이어");
	info->position = { 500.f, 600.f , 0.f };
	info->size = { 100.f, 100.f , 0.f };
	info->force = { 0.f, 0.f , 0.f };
	info->look = { 1.f, 0.f, 0.f };
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	
	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = {-info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = {-info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

INT CPlayer::Update() {
	//MoveTopdown();
	UpdateDraw();
	Input();
	Move();
	return STATE::NO_EVENT;
}

void CPlayer::LateUpdate() {
	
}

void CPlayer::Render(HDC hDC) {
	MoveToEx(hDC, (INT)globalVertex[3].x, (INT)globalVertex[3].y, nullptr);
	for (size_t i = 0; i < 4; i++)
		LineTo(hDC, (INT)globalVertex[i].x, (INT)globalVertex[i].y);
}

void CPlayer::Release() {
}

void CPlayer::OnCollision(CObj* _TargetObj) {

}

void CPlayer::Input() {
	CKeyManager* keyMgr = CKeyManager::GetInstance();
	if (keyMgr->OnPress(KEY::PrimaryAction)) {
		Shoot(0.f, 10.f, 20, 10);
		m_hp++;
	}
	if (keyMgr->OnPress(KEY::SecondaryAction)) {
		m_BombCount--;
	}
}

void CPlayer::Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, COLORREF _fillColor, COLORREF _strokeColor) {
	CObj* bulletObj = new CBullet(_degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);
}

void CPlayer::UpdateDraw() {

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	D3DXVECTOR3 vMouse = { float(pt.x), float(pt.y), 0.f };

	localVertex[0] = {  info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = {  info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&m_matRotation, D3DXToRadian(angleRot));
	D3DXMatrixTranslation(&m_matTransform, info->position.x, info->position.y, info->position.z);
	D3DXMatrixRotationZ(&m_matRevolution, D3DXToRadian(angleRev));
	
	D3DXMatrixIdentity(&m_matW);
	m_matW = m_matScale * m_matRotation * m_matTransform * m_matRevolution;

	for (size_t i = 0; i < 4; i++) {
		D3DXVec3TransformCoord(&globalVertex[i], &localVertex[i], &m_matW);
	}
}

void CPlayer::Move() {
	CKeyManager* keyMgr = CKeyManager::GetInstance();

	info->force.x = 0.f;
	info->force.y = 0.f;

	if (keyMgr->Press(KEY::MoveLeft))
		info->force.x = -1.f;
	if (keyMgr->Press(KEY::MoveRight))
		info->force.x = 1.f;
	if (keyMgr->Press(KEY::MoveUp))
		info->force.y = -1.f;
	if (keyMgr->Press(KEY::MoveDown))
		info->force.y = 1.f;

	D3DXVec3Normalize(&info->force, &info->force);

	info->position += info->force * speed;
}
