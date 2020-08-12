#pragma once
#include "UI.h"
class CBombUI :
    public CUI {
public:
	explicit CBombUI();
	virtual ~CBombUI();
	virtual void Ready() override;
	virtual INT  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObj* _TargetObj) override;

};

