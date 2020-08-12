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

    void Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size);
    void Shoot(CObj* _targetObj, FLOAT _degree, FLOAT _speed, INT _damage, LONG _size);

public:
	void SetInfo(stMonsterInfo* mobinfo);

private:
	list<stBulletPattern> listBulletStandby;
	list<stMovePattern> listMoveStandby;

	int m_hp;
	int m_point;
	DWORD m_StartTime;
	ITEM_TYPE m_dropItem;
};

