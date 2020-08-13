#pragma once
#include "Obj.h"
class CBomb :
    public CObj {
public:
    CBomb();
    virtual ~CBomb();
    // CObj��(��) ���� ��ӵ�
    virtual void Ready() override;
    virtual INT Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void OnCollision(CObj* _TargetObj) override;

    DWORD BombBulletTimer;
};

