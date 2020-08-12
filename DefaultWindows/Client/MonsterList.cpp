
#include "framework.h"
#include "MonsterBulletPattern.h"
#include "MonsterMovePattern.h"
#include "MonsterList.h"

// 반드시 시간 순서대로 정렬되어있어야 함
stMonsterInfo MobList[1] = {
	// 타입				시작 시간	시작X위치			시작Y위치	아이템			총알패턴목록	갯수	이동패턴목록	갯수
	{ MONSTER_TYPE_01,	1000,		(float)WINCX-100,	500.f,		ITEM_TYPE_NONE,	mobBList01,		3,		mobMList0,		2 }
};
