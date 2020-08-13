#include "framework.h"
#include "CollisionManager.h"
#include "Obj.h"

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::CollisionPoint(CObj* pointObj, list<CObj*>& rDstList) {
	POINT pt = {};
	for (auto DstObj : rDstList) {

		pt.x = (INT)pointObj->GetPosition()->x;
		pt.y = (INT)pointObj->GetPosition()->y;
		if (PtInRect(DstObj->GetRect(), pt)) {
			pointObj->OnCollision(DstObj);
			DstObj->OnCollision(pointObj);
		}
	}
}
void CCollisionManager::CollisionRect(list<CObj*>& rDstList, list<CObj*>& rSrcList)
{
	RECT rc = {}; 
	for (auto rDstObject : rDstList)
	{
		for (auto rSrcObject : rSrcList)
		{
			if (IntersectRect(&rc, rDstObject->GetRect(), rSrcObject->GetRect()))
			{
				rDstObject->OnCollision(rSrcObject);
				rSrcObject->OnCollision(rDstObject);
			}
		}
	}
}

void CCollisionManager::CollisionSphere(list<CObj*>& rDstList, list<CObj*>& rSrcList)
{
	for (auto& rDstObject : rDstList)
	{
		for (auto& rSrcObject : rSrcList)
		{
			if (CheckSphere(rDstObject, rSrcObject))
			{
				rDstObject->OnCollision(rSrcObject);
				rSrcObject->OnCollision(rDstObject);
			}
		}
	}
}

void CCollisionManager::CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList)
{
	float fMoveX = 0.f, fMoveY = 0.f; 

	for (auto rDstObject : rDstList)
	{
		for (auto rSrcObject : rSrcList)
		{
			if (CheckRect(rDstObject, rSrcObject, &fMoveX, &fMoveY))
			{
				float fX = rSrcObject->GetPosition()->x; 
				float fY = rSrcObject->GetPosition()->y;

				if (fMoveX > fMoveY)
				{
					if (fY < rDstObject->GetPosition()->y)
						fMoveY *= -1.f; 
					
					rSrcObject->SetPosition(fX, fY + fMoveY);
				}
				else
				{
					if (fX < rDstObject->GetPosition()->x)
						fMoveX *= -1.f; 
					rSrcObject->SetPosition(fX + fMoveX, fY);
				}
			}
		}
	}
}

bool CCollisionManager::CheckSphere(CObj * pDstObject, CObj * rSrcObject)
{
	float fRadiusSum = (pDstObject->GetInfo()->size.x / 2) + (rSrcObject->GetInfo()->size.y / 2);
	float fX = pDstObject->GetPosition()->x - rSrcObject->GetPosition()->x;
	float fY = pDstObject->GetPosition()->y - rSrcObject->GetPosition()->y;
	float fDist = sqrtf(fX * fX + fY * fY); 

	return fDist <fRadiusSum;
}

bool CCollisionManager::CheckRect(CObj * pDstObject, CObj *rSrcObject, float * pMoveX, float * pMoveY)
{
	// 1.�簢�� �ΰ��� x�������� �������� ���� ����. 
	float fRadiusSumX = (pDstObject->GetInfo()->size.x / 2) + (rSrcObject->GetInfo()->size.x / 2);
	//2.�簢�� �ΰ��� y�������� �������� ���� ����. 
	float fRadiusSumY = (pDstObject->GetInfo()->size.y / 2) + (rSrcObject->GetInfo()->size.y / 2);;

	// x��� y���� �Ÿ� ����. 
	float fDistX = fabsf(pDstObject->GetPosition()->x - rSrcObject->GetPosition()->x);
	float fDistY = fabsf(pDstObject->GetPosition()->y - rSrcObject->GetPosition()->y);

	// ���� �ΰ��� �Ÿ��� �������� ���� ���� ��. 
	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY)
	{
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY; 
		return true;
	}
	// �ΰ��� �Ÿ��� �� ª�ٶ�� ? �浹. 
	return false; 
}