#pragma once
#include "Obj.h"
class CEffect :
	public CObj {
public:
	CEffect(const FLOAT& _degree, const FLOAT& _speed, const FLOAT& _diffuse, const UINT& _count, const LONG& _size);
	virtual ~CEffect();
public:
	virtual void Ready() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _SrcObj) override;

private:
	FLOAT degree;
	FLOAT diffuse;
	UINT  count;
	LONG  size;

	vector<CObj*> vecParticles;
};

