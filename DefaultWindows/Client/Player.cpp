
#include "framework.h"
#include "KeyManager.h"
#include "Player.h"

CPlayer::CPlayer() {

}

CPlayer::~CPlayer() {
	Release();
}

void CPlayer::Ready() {
	info = new INFO();
	lstrcpy(info->name, L"플레이어");
	info->position = { 500.f, 600.f , 0.f };
	info->size = { 100.f, 100.f , 0.f };
	info->force = { 0.f, 0.f , 0.f };
	info->look = { 1.f, 0.f, 0.f };
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	rect = new RECT();
	
	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = {-info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = {-info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	//gravity = 1.2f;
	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

void CPlayer::Update() {
	//MoveTopdown();
	UpdateDraw();
	Move();
}

void CPlayer::LateUpdate() {
	
}

void CPlayer::Render(HDC hDC) {
	MoveToEx(hDC, (INT)globalVertex[3].x, (INT)globalVertex[3].y, nullptr);
	for (size_t i = 0; i < 4; i++)
		LineTo(hDC, (INT)globalVertex[i].x, (INT)globalVertex[i].y);
}

void CPlayer::Release() {
	delete info;
	delete rect;
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

	for (size_t i = 0; i < 4; i++) {
		globalVertex[i].x = localVertex[i].x * cosf(D3DXToRadian(angle)) - localVertex[i].y * sinf(D3DXToRadian(angle)) + info->position.x;
		globalVertex[i].y = localVertex[i].x * sinf(D3DXToRadian(angle)) + localVertex[i].y * cosf(D3DXToRadian(angle)) + info->position.y;
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

	info->position += info->force * speed;
}
