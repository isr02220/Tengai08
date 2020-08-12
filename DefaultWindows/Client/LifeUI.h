#pragma once
#include "UI.h"
class CLifeUI :
    public CUI {
public:
	explicit CLifeUI();
	virtual ~CLifeUI();
	virtual void Ready() override;
	virtual INT  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _TargetObj) override;

};

