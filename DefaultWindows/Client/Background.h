#pragma once
#include "Obj.h"
class CBgObj;
class CBackground :
    public CObj {
public:
    virtual void Ready() override;
    virtual INT Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void OnCollision(CObj* _TargetObj) override;

private:
    list<CBgObj*> m_ListBgSky;
    list<CBgObj*> m_ListBgSky2;
    list<CBgObj*> m_ListBgFar;
    list<CBgObj*> m_ListBgMiddle;
    list<CBgObj*> m_ListBgClose;
    list<CBgObj*> m_ListBgBush;
    list<CBgObj*> m_ListBgGround;
};

class FloatRect {
public:
    FloatRect() {};
    FloatRect(FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom) {
        left = _left; top = _top; right = _right; bottom = _bottom;
    };
public:
    FLOAT left = 0;
    FLOAT top = 0;
    FLOAT right = 0;
    FLOAT bottom = 0;
};

class CBgObj {
public:
    CBgObj(LONG _left, LONG _top, LONG _right, LONG _bottom) {
        SetRect((FLOAT)_left, (FLOAT)_top, (FLOAT)_right, (FLOAT)_bottom);
    }
    void SetRect(FLOAT _left, FLOAT _top, FLOAT _right, FLOAT _bottom) {
        rect.left = _left; rect.top = _top; rect.right = _right; rect.bottom = _bottom;
    }
    void OffsetRect(FLOAT _offsetLeft, FLOAT _offsetTop, FLOAT _offsetRight, FLOAT _offsetBottom) {
        rect.left += _offsetLeft; rect.top += _offsetTop; rect.right += _offsetRight; rect.bottom += _offsetBottom;
    }
    void MoveRect(FLOAT _dx, FLOAT _dy) {
        rect.left += _dx; rect.top += _dy; rect.right += _dx; rect.bottom += _dy;
    }
    void Draw(HDC hDC) {
        Rectangle(hDC, (INT)rect.left, (INT)rect.top, (INT)rect.right, (INT)rect.bottom);
    }
    FloatRect rect;
};
