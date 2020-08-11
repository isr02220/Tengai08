#pragma once
#include "Obj.h"
#include "framework.h"
class CPlayer : public CObj {
public:
	CPlayer();
	~CPlayer();

public:

	virtual void Ready() override;
	virtual INT  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _TargetObj);

	void UpdateDraw();
	void Move();

protected:
	INFO* info = nullptr;
	RECT* rect = nullptr;
	FLOAT angle = 0.f;
	FLOAT speed = 5.f;
	D3DXVECTOR3 localVertex[4];
	D3DXVECTOR3 globalVertex[4];
};

