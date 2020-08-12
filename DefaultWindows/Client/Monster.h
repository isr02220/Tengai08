#pragma once
#include "Obj.h"
class CMonster :
    public CObj {
    // CObj��(��) ���� ��ӵ�
    virtual void Ready() override;
    virtual INT Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void OnCollision(CObj* _TargetObj) override;

    void Move();
    void Attack();
    void Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, COLORREF _fillColor = RGB(255,128,39), COLORREF _strokeColor = RGB(255, 0, 0));
    void Shoot(CObj* _targetObj, FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, COLORREF _fillColor = RGB(255, 128, 39), COLORREF _strokeColor = RGB(255, 0, 0));
};

