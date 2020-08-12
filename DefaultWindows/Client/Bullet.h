#pragma once
#include "Obj.h"
class CBullet :
    public CObj {
public:
	CBullet(FLOAT _degree, FLOAT _speed, INT _damage, LONG _bulletSize);
	virtual ~CBullet();
public:
	virtual void Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _SrcObj) override;

public:
	void SetDamage(INT _damage) { m_damage = _damage; };
	void SetActor(CObj* _pActor) { m_pActor = _pActor; };

	INT  GetDamage() { return m_damage; };
	CObj* GetActor() { return  m_pActor; };

protected:
	INT m_damage = 10;
	CObj* m_pActor = nullptr;

};

