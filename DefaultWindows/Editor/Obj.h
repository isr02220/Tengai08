#pragma once
#include "framework.h"
class CObj abstract {
public:
	CObj();
	CObj(FLOAT _positionX, FLOAT _positionY);
	virtual ~CObj();

public:
	virtual void Ready() = 0;
	virtual INT  Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
	virtual void OnCollision(CObj* _TargetObj) = 0;

public:
	void SetName(const TCHAR* _name) {
		lstrcpy(info->name, _name);
	}
	void SetPosition(const FLOAT& fX, const FLOAT& fY) {
		info->position.x = fX;
		info->position.y = fY;
	}
	void SetPosition(const D3DXVECTOR3& newPoint) {
		info->position = newPoint;
	}
	TCHAR* GetName() {
		return info->name;
	}
	RECT* GetRect() { return rect; }
	INFO* GetInfo() { return info; }
	BOOL  GetActive() { return active; };
	BOOL GetVisible() { return isVisible; };
	D3DXVECTOR3* GetPosition() { return &info->position; }
	OBJ::TYPE GetObjectType() { return objectType; }

	void UpdateRect();
	void SetDead() { dead = true; }
	void SetActive(BOOL _val) { active = _val; };
	void SetVisible(BOOL _val) { isVisible = _val; };
	void SetFillColor(const COLORREF& _FillColor) { fillColor = _FillColor; }
	void SetStrokeColor(const COLORREF& _StrokeColor) { strokeColor = _StrokeColor; }

protected:
	OBJ::TYPE objectType = OBJ::END;
	COLORREF fillColor = RGB(255, 255, 255);
	COLORREF strokeColor = RGB(0, 0, 0);
	BOOL dead = false;
	BOOL active = false;
	BOOL isVisible = true;

	INFO* info = nullptr;
	RECT* rect = nullptr;
	FLOAT angleRot = 0.f;
	FLOAT angleRev = 0.f;
	FLOAT speed = 5.f;
	D3DXVECTOR3 localVertex[4];
	D3DXVECTOR3 globalVertex[4];

	D3DXMATRIX m_matW;
	D3DXMATRIX m_matScale; // 크기
	D3DXMATRIX m_matRotation; // 자전
	D3DXMATRIX m_matTransform; // 이동
	D3DXMATRIX m_matRevolution; // 공전
	D3DXMATRIX m_matParent; // 부모
};

