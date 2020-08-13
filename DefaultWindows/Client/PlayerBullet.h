#pragma once
#include "Bullet.h"
class CPlayerBullet :
    public CBullet {
public:
	CPlayerBullet(const FLOAT& _degree, const FLOAT& _speed, const INT& _damage, const LONG& _bulletSize);
	virtual ~CPlayerBullet();
public:
	virtual void Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _SrcObj) override;
public:
	static FLOAT staticBulletRotation;
};

