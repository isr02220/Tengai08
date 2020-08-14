#pragma once
#include "Obj.h"
class CPet :
    public CObj {
public:
    virtual void Ready() override;
    virtual INT Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void OnCollision(CObj* _TargetObj) override;

    void SetPlayer(CObj* _pObj) { m_playerObj = _pObj; }
    void Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, D3DXVECTOR3 _posoffset, COLORREF _fillColor = RGB(255, 128, 39), COLORREF _strokeColor = RGB(255, 0, 0));
    void Shoot(CObj* _targetObj, FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, D3DXVECTOR3 _posoffset, COLORREF _fillColor = RGB(255, 128, 39), COLORREF _strokeColor = RGB(255, 0, 0));

private:
    CObj* m_playerObj = nullptr;

    void Move();
    void Attack();
};

