#pragma once
#include "Bullet.h"
class CChargeBullet :
	public CBullet {
public:
	CChargeBullet(const FLOAT& _degree, const FLOAT& _speed, const INT& _damage, const LONG& _bulletSize);
	virtual ~CChargeBullet();
public:
	virtual void Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _SrcObj) override;
public:
	FLOAT m_scale = 1.f;
};

