#pragma once
#include "Obj.h"
class CMonster :
    public CObj {
    // CObj을(를) 통해 상속됨
    virtual void Ready() override;
    virtual INT Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void OnCollision(CObj* _TargetObj) override;
};

