#pragma once
#include "framework.h"
#include "Obj.h"

class CPlayer : public CObj {
public:
	CPlayer();
	virtual ~CPlayer();

public:

	virtual void Ready() override;
	virtual INT  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _TargetObj);

	void Input();
	void Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, COLORREF _fillColor = RGB(255, 128, 39), COLORREF _strokeColor = RGB(255, 0, 0));
	void ShootBomb();
	void UpdateDraw();
	void Move();
	void IncreasePower();

	INT  GetHP() { return m_hp; }
	INT  GetBombCount() { return m_BombCount; }

	void SetHP(INT _hp) { m_hp = _hp; }
	void SetBombCount(INT _BombCount) { m_BombCount = _BombCount; }
	void SetBombEnable() { m_BombEnable = true; }

protected:
	INT m_BombCount = 3;
	BOOL m_BombEnable = true;
	INT m_hp = 3;
	INT m_level = 1;
	BOOL m_cheat = false;
	BOOL m_invincible = true;
	INT  m_invincibleFlicker = 0;
	INT  m_ShootDegree = 1;
	DWORD m_shootDelay = 10;
	DWORD m_shootDelayCount = 0;
	BOOL m_ChargeShootReady = false;
};

