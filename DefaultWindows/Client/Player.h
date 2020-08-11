#pragma once
#include "framework.h"
#include "Obj.h"

class CPlayer : public CObj {
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Ready();
	virtual INT Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

	void UpdateDraw();
	void Move();

protected:

};

