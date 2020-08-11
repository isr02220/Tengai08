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

	void UpdateDraw();
	void Move();

protected:

};

