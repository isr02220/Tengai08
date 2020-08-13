#pragma once
class CObj;
class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();
public:
	static void CollisionPoint(CObj* pointObj, list<CObj*>& rDstList);
	static void CollisionRect(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static void CollisionSphere(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static void CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList);
private:
	static bool CheckSphere(CObj* pDstObject, CObj* rSrcObject);
	static bool CheckRect(CObj* pDstObject, CObj* rSrcObject, float* pMoveX, float* pMoveY);
};

