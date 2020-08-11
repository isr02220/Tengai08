#include "framework.h"
#include "CollisionManager.h"
#include "Obj.h"

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::CollisionRect(list<CObj*>& rDstList, list<CObj*>& rSrcList)
{
	RECT rc = {}; 
	for (auto& rDstObject : rDstList)
	{
		for (auto& rSrcObject : rSrcList)
		{
			if (IntersectRect(&rc,&rDstObject->Get_Rect(), &rSrcObject->Get_Rect()))
			{
				rDstObject->Set_Dead(); 
				rSrcObject->Set_Dead(); 
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
			if (CheckSphere(rDstObject, *rSrcObject))
			{
				rDstObject->Set_Dead();
				rSrcObject->Set_Dead();
			}
		}
	}
}

void CCollisionManager::CollisionRectEX(list<CObj*>& rDstList, list<CObj*>& rSrcList)
{
	float fMoveX = 0.f, fMoveY = 0.f; 

	for (auto& rDstObject : rDstList)
	{
		for (auto& rSrcObject : rSrcList)
		{
			if (CheckRect(rDstObject, *rSrcObject, &fMoveX, &fMoveY))
			{
				float fX = rSrcObject->Get_Info()->fX; 
				float fY = rSrcObject->Get_Info()->fY; 

				if (fMoveX > fMoveY)
				{
					if (fY < rDstObject->Get_Info()->fY)
						fMoveY *= -1.f; 
					
					rSrcObject->Set_Pos(fX, fY + fMoveY); 
				}
				else
				{
					if (fX < rDstObject->Get_Info()->fX)
						fMoveX *= -1.f; 
					rSrcObject->Set_Pos(fX + fMoveX, fY);
				}
			}
		}
	}

}

bool CCollisionManager::CheckSphere(const CObj * pDstObject, const CObj & rSrcObject)
{
	float fRadiusSum = static_cast<float>((pDstObject->Get_Info()->iCX >> 1) + (rSrcObject.Get_Info()->iCX >> 1));
	float fX = pDstObject->Get_Info()->fX - rSrcObject.Get_Info()->fX; 
	float fY = pDstObject->Get_Info()->fY - rSrcObject.Get_Info()->fY; 
	float fDist = sqrtf(fX * fX + fY * fY); 

	return fDist <fRadiusSum;
}

bool CCollisionManager::CheckRect(const CObj * pDstObject, const CObj & rSrcObject, float * pMoveX, float * pMoveY)
{
	// 1.�簢�� �ΰ��� x�������� �������� ���� ����. 
	float fRadiusSumX = static_cast<float>((pDstObject->Get_Info()->iCX >> 1) + (rSrcObject.Get_Info()->iCX >> 1));
	//2.�簢�� �ΰ��� y�������� �������� ���� ����. 
	float fRadiusSumY = static_cast<float>((pDstObject->Get_Info()->iCY >> 1) + (rSrcObject.Get_Info()->iCY >> 1));

	// x��� y���� �Ÿ� ����. 
	float fDistX = fabs(pDstObject->Get_Info()->fX - rSrcObject.Get_Info()->fX); 
	float fDistY = fabs(pDstObject->Get_Info()->fY - rSrcObject.Get_Info()->fY); 

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
