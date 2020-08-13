#pragma once
#include "Obj.h"
class CParticle :
	public CObj {
public:
	CParticle(const FLOAT& _degree, const FLOAT& _speed, const LONG& _size);
	virtual ~CParticle();
public:
	virtual void Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _SrcObj) override;
};

