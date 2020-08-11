
#include "framework.h"
#include "KeyManager.h"
#include "Player.h"

CPlayer::CPlayer() {

}

CPlayer::~CPlayer() {

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
	barrel = { 100.f, 0.f, 0.f };
	barrelEnd = info->position + barrel;

	gravity = 1.2f;
	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

void CPlayer::Update() {
	//MoveTopdown();
	//UpdateDraw();
	Move();
}

void CPlayer::LateUpdate() {
	
}

void CPlayer::Render(HDC hDC) {
	MoveToEx(hDC, (INT)globalVertex[3].x, (INT)globalVertex[3].y, nullptr);
	for (size_t i = 0; i < 4; i++)
		LineTo(hDC, (INT)globalVertex[i].x, (INT)globalVertex[i].y);

	MoveToEx(hDC, (INT)info->position.x, (INT)info->position.y, nullptr);
	LineTo(hDC, (INT)barrelEnd.x, (INT)barrelEnd.y);
}

void CPlayer::Release() {

}

void CPlayer::UpdateDraw() {

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	D3DXVECTOR3 vMouse = { float(pt.x), float(pt.y), 0.f };
	barrel = vMouse - info->position;

	D3DXVec3Normalize(&barrel, &barrel);

	barrel *= 100.f;

	barrelEnd = info->position + barrel;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	for (size_t i = 0; i < 4; i++) {
		globalVertex[i].x = localVertex[i].x * cosf(D3DXToRadian(angle)) - localVertex[i].y * sinf(D3DXToRadian(angle)) + info->position.x;
		globalVertex[i].y = localVertex[i].x * sinf(D3DXToRadian(angle)) + localVertex[i].y * cosf(D3DXToRadian(angle)) + info->position.y;
	}
}

void CPlayer::Move() {
	CKeyManager* keyMgr = CKeyManager::GetInstance();
	
	info->position += info->force * speed;

	info->force.x = 0.f;
	if (info->position.y < 600)  { info->force.y += 0.3f; }
	else { info->position.y = 600; info->force.y = 0.f; }
	if (keyMgr->Press(KEY::MoveLeft))		info->force.x = -1.f;
	if (keyMgr->Press(KEY::MoveRight))		info->force.x = 1.f;
	if (keyMgr->Press(KEY::MoveUp))			info->force.y = -1.f;
	if (keyMgr->Press(KEY::MoveDown))		info->force.y = 1.f;

	else {
		info->size.y = 100.f;
	}


}

void CPlayer::MoveTopdown() {
	//POINT pt = {};
		//GetCursorPos(&pt);
		//ScreenToClient(g_hWnd, &pt);
		//DXVECTOR3 vMouse = { float(pt.x), float(pt.y), 0.f };
		//info->force = vMouse - info->position;

	D3DXVec3Normalize(&info->force, &info->force);
	barrelEnd = info->position + D3DXVECTOR3(
		barrel.x * cosf(D3DXToRadian(angle)) - barrel.y * sinf(D3DXToRadian(angle)),
		barrel.x * sinf(D3DXToRadian(angle)) - barrel.y * cosf(D3DXToRadian(angle)), 0.f);

	for (size_t i = 0; i < 4; i++) {
		globalVertex[i].x = localVertex[i].x * cosf(D3DXToRadian(angle)) - localVertex[i].y * sinf(D3DXToRadian(angle)) + info->position.x;
		globalVertex[i].y = localVertex[i].x * sinf(D3DXToRadian(angle)) + localVertex[i].y * cosf(D3DXToRadian(angle)) + info->position.y;
	}
	if (CKeyManager::GetInstance()->Press(KEY::MoveLeft))
		angle -= 5.f;
	if (CKeyManager::GetInstance()->Press(KEY::MoveRight))
		angle += 5.f;
	if (CKeyManager::GetInstance()->Press(KEY::MoveUp)) {
		info->force = barrelEnd - info->position;
		if (speed <= 10.f) speed += 0.2f;
	}
	if (CKeyManager::GetInstance()->Press(KEY::MoveDown)) {
		info->force = barrelEnd - info->position;
		if (speed >= -5.f) speed -= 0.2f;
	}

	D3DXVec3Normalize(&info->force, &info->force);
	if (speed >= 0.1f) speed -= 0.1f;
	else if (speed <= -0.1f) speed += 0.1f;
	else speed = 0.f;
	//info->force += DXVECTOR3(0.f, gravity, 0.f);
	info->position += info->force * speed;
	//if (info->position.y > 800) {
	//	info->force.y = -info->force.y - gravity;
	//}
	//DXVECTOR3 vecLT = info->position - info->size / 2.f;
	//DXVECTOR3 vecRB = info->position + info->size / 2.f;
	//SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}
