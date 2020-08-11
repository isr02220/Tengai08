#pragma once
class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();
public:
	static void CollisionRect(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static void CollisionSphere(list<CObj*>& rDstList, list<CObj*>& rSrcList);
	static void CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList);
private:
	static bool CheckSphere(const CObj* pDstObject, const CObj& rSrcObject);
	static bool CheckRect(const CObj* pDstObject, const CObj& rSrcObject, float* pMoveX, float* pMoveY);
};

