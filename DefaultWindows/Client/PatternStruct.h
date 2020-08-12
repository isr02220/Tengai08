#pragma once

enum MONSTER_TYPE {
	MONSTER_TYPE_01,
	MONSTER_TYPE_02,
	MONSTER_TYPE_03,
	MONSTER_TYPE_04,
	MONSTER_TYPE_05,
	MONSTER_TYPE_06,
	MONSTER_TYPE_END
};

struct stMonsterType {
	COLORREF color; // ����
	int iCX; // ũ�� WIdth
	int iCY; // ũ�� Height
	int iHP; // ü��
	int iPoint; // ����
};
extern stMonsterType mobTypeList[MONSTER_TYPE_END];

enum ITEM_TYPE {
	ITEM_TYPE_NONE,
	ITEM_TYPE_P, // �Ŀ�
	ITEM_TYPE_B, // �ʻ��
	ITEM_TYPE_END
};

struct stBulletPattern;
struct stMovePattern;
struct stMonsterInfo {
	MONSTER_TYPE type;
	DWORD dwStartTime;
	float fStartX;
	float fStartY;
	ITEM_TYPE dropItem;
	stBulletPattern* blist;
	int blistNum;
	stMovePattern*   mlist;
	int mlistNum;
};

struct stBulletPattern {
	int iStartTime;
	int iStartX;
	int iStartY;
	float fDirection;
	float fSpeed;
	int iBulletSize;
	bool horming; // ���� ����
};

struct stMovePattern {
	int iStartTime;
	float fDirection;
	float fSpeed;
};