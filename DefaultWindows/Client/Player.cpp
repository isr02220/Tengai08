#include "framework.h"
#include "KeyManager.h"
#include "Player.h"
#include "Pet.h"
#include "Bullet.h"
#include "PlayerBullet.h"
#include "ChargeBullet.h"
#include "Bomb.h"

CPlayer::CPlayer() : CObj(){

}

CPlayer::~CPlayer() {
	Release();
}

void CPlayer::Ready() {
	lstrcpy(info->name, L"플레이어");
	info->size = { 80.f, 50.f , 0.f };
	info->force = { 0.f, 0.f , 0.f };
	info->look = { 1.f, 0.f, 0.f };
	speed = 10.f;
	active = false;

	petObj = CAbstractFactory<CPet>::Create(info->position);
	dynamic_cast<CPet*>(petObj)->SetPlayer(this);
	CObjManager::GetInstance()->AddObject(petObj, OBJ::PET);

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
	if (m_invincible)
		if(m_invincibleFlicker == 0) {
			m_invincibleFlicker = 2;
			return;
		}
		else {
			m_invincibleFlicker--;
		}
	DrawPolygon(hDC);
	//MoveToEx(hDC, (INT)globalVertex[3].x, (INT)globalVertex[3].y, nullptr);
	//for (size_t i = 0; i < 4; i++)
	//	LineTo(hDC, (INT)globalVertex[i].x, (INT)globalVertex[i].y);
}

void CPlayer::Release() {
}

void CPlayer::OnCollision(CObj* _TargetObj) {
	if (!m_invincible && _TargetObj->GetObjectType() == OBJ::BULLET) {
		m_hp -= 1;
		SetActive(false);
		m_invincible = true;
		timer = GetTickCount();
		SetPosition(-300.f, 400.f);
		if (m_hp <= 0) {
			SetDead();
		}
	}
}

void CPlayer::Input() {
	CKeyManager* keyMgr = CKeyManager::GetInstance();
	if (active) {
		if (keyMgr->OnPress(KEY::CONTROL)) {
			m_cheat = !m_cheat;
		}
		if (keyMgr->OnPress(KEY::SHIFT)) {
			IncreasePower();
		}
		if (m_cheat) {
			m_invincible = true;
			m_hp = 3;
			m_BombCount = 3;
		}
		else if (m_invincible && timer + 3000 < GetTickCount()) {
			m_invincible = false;
		}
		if (keyMgr->OnPress(KEY::PrimaryAction)) {
			m_shootStack = m_level;
		}
		if (m_shootStack > 0) {
			if (m_shootDelayCount == 0) {
				m_shootDelayCount = m_shootDelay;

				m_shootStack--;
				Shoot(FLOAT((rand() % m_ShootDegree) - (m_ShootDegree >> 1)), 30.f, 20, 50, RGB(153, 204, 255), RGB(102, 102, 255));
			}
		}
		if (keyMgr->OnRelease(KEY::PrimaryAction)) {
			if (m_ChargeShootReady) {
				ChargeShoot(0.f, 10.f, 5, 150, RGB(153, 204, 255), RGB(102, 102, 255));
			}
		}
		m_ChargeShootReady = keyMgr->KeepPress(KEY::PrimaryAction, 40);
		if (keyMgr->KeepPress(KEY::PrimaryAction, 10)) {
			petObj->SetRotation(-10.f);

			if (keyMgr->KeepPress(KEY::PrimaryAction, 20)) {
				petObj->SetRotation(-20.f);
				petObj->SetFillColor(RGB(122, 152, 245));
			}
			if (keyMgr->KeepPress(KEY::PrimaryAction, 30)) {
				petObj->SetRotation(-25.f);
				petObj->SetFillColor(RGB(102, 102, 255));
				petObj->GetInfo()->size.x = 60;
				petObj->GetInfo()->size.y = 43;
			}
			if (m_ChargeShootReady) {
				petObj->GetInfo()->size.x = 70;
				petObj->GetInfo()->size.y = 50;
				petObj->SetRotation(-30.f);
			}
		}
		else {
			petObj->SetRotation(0.f);
			petObj->SetFillColor(RGB(133, 184, 235));
			petObj->GetInfo()->size.x = 50;
			petObj->GetInfo()->size.y = 35;
		}
		if (keyMgr->OnPress(KEY::SecondaryAction)) {
			ShootBomb();
		}
	}
	if (m_shootDelayCount > 0) m_shootDelayCount--;
	else m_shootDelayCount = 0;
}

void CPlayer::Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, COLORREF _fillColor, COLORREF _strokeColor) {
	CObj* bulletObj = new CPlayerBullet(_degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);
}

void CPlayer::ChargeShoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, COLORREF _fillColor, COLORREF _strokeColor) {
	CObj* bulletObj = new CChargeBullet(_degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::BULLET);
}

void CPlayer::ShootBomb() {
	if (m_BombEnable && m_BombCount > 0) {
		m_BombCount--;
		m_BombEnable = false;

		CObj* BombObj = new CBomb();
		BombObj->SetPosition(info->position);
		BombObj->Ready();
		CObjManager::GetInstance()->AddObject(BombObj, OBJ::BOMB);
	}
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
	if (active) {
		if (keyMgr->Press(KEY::MoveLeft))
			info->force.x += -1.f;
		if (keyMgr->Press(KEY::MoveRight))
			info->force.x += 1.f;
		if (keyMgr->Press(KEY::MoveUp))
			info->force.y += -1.f;
		if (keyMgr->Press(KEY::MoveDown))
			info->force.y += 1.f;
	}
	else {
		info->force.x = 1.f;
		if (info->position.x > 200.f)
			SetActive(true);
	}
	angleRot = info->force.x * 30.f;
	D3DXVec3Normalize(&info->force, &info->force);

	info->position += info->force * speed;
}

void CPlayer::IncreasePower() {
	if (m_level < 4) m_level += 1;
	switch (m_level) {
	case 1:
		m_shootDelay = 10;
		m_ShootDegree = 1;
		break;
	case 2:
		m_shootDelay = 8;
		m_ShootDegree = 5;
		break;
	case 3:
		m_shootDelay = 6;
		m_ShootDegree = 10;
		break;
	case 4:
		m_shootDelay = 4;
		m_ShootDegree = 15;
		break;
	default:
		break;
	}
	
}
