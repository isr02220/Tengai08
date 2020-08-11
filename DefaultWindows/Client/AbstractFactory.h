#pragma once
#include "framework.h"
class CObj;
template<typename T>
class CAbstractFactory {
public:
	static CObj* Create() {
		CObj* pObj = new T;
		pObj->Ready();
		return pObj;
	}
	static CObj* Create(const FLOAT& fX, const FLOAT& fY) {
		CObj* pObj = new T;
		pObj->Ready();
		pObj->SetPosition(fX, fY);
		return pObj;
	}
	static CObj* Create(const D3DXVECTOR3& pos) {
		CObj* pObj = new T;
		pObj->Ready();
		pObj->SetPosition(pos);
		return pObj;
	}
};