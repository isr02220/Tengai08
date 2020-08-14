
#include "framework.h"
#include "MonsterBulletPattern.h"
#include "MonsterMovePattern.h"
#include "MonsterList.h"

// 반드시 시간 순서대로 정렬되어있어야 함
stMonsterInfo MobList[] = {
	// 타입				시작 시간	시작X위치			시작Y위치	아이템			총알패턴목록		갯수					이동패턴목록			갯수
	{ MONSTER_TYPE_01,	1000,		(float)WINCX,		160.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size }, // UFO부대 시작
	{ MONSTER_TYPE_01,	1100,		(float)WINCX,		240.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	1200,		(float)WINCX,		320.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_02,	1300,		(float)WINCX,		400.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size }, // UFO부대 끝

	{ MONSTER_TYPE_03,	2000,		1500.f,				0.f,		ITEM_TYPE_NONE,	mobBList3,			mobBList3Size,			mobMList1,				mobMList1Size },

	{ MONSTER_TYPE_01,	2500,		(float)WINCX,		360.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	2600,		(float)WINCX,		440.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	2700,		(float)WINCX,		520.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_02,	2800,		(float)WINCX,		600.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },

	{ MONSTER_TYPE_05,	3375,		(float)WINCX,		180.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle185,		mobMListAngle185Size },
	{ MONSTER_TYPE_05,	5708,		(float)WINCX,		450.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	6458,		(float)WINCX,		470.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle185,		mobMListAngle185Size },
	{ MONSTER_TYPE_05,	6750,		(float)WINCX,		180.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle175,		mobMListAngle175Size },
	{ MONSTER_TYPE_05,	7000,		(float)WINCX,		175.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle175,		mobMListAngle175Size },
	{ MONSTER_TYPE_05,	7542,		(float)WINCX,		750.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle185,		mobMListAngle185Size },
	{ MONSTER_TYPE_05,	7833,		(float)WINCX,		200.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },

	{ MONSTER_TYPE_01,	8000,		(float)WINCX,		160.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },

	{ MONSTER_TYPE_05,	8083,		(float)WINCX,		200.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle175,		mobMListAngle175Size },
	{ MONSTER_TYPE_01,	8100,		(float)WINCX,		240.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	8200,		(float)WINCX,		320.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_02,	8300,		(float)WINCX,		400.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	
	{ MONSTER_TYPE_05,	8417,		(float)WINCX,		300.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	8958,		(float)WINCX,		550.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle190,		mobMListAngle190Size },

	{ MONSTER_TYPE_01,	9000,		(float)WINCX,		160.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	9100,		(float)WINCX,		240.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	9200,		(float)WINCX,		320.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_02,	9300,		(float)WINCX,		400.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },

	{ MONSTER_TYPE_01,	10000,		(float)WINCX,		160.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	10100,		(float)WINCX,		240.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	10200,		(float)WINCX,		320.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_02,	10300,		(float)WINCX,		400.f,		ITEM_TYPE_NONE,	nullptr,			0,						mobMList0,				mobMList0Size }, 
	{ MONSTER_TYPE_05,	11458,		(float)WINCX,		170.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	11750,		(float)WINCX,		450.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	12042,		(float)WINCX,		180.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	12542,		(float)WINCX,		480.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },

	{ MONSTER_TYPE_05,	13125,		(float)WINCX,		140.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	13375,		(float)WINCX,		400.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	13667,		(float)WINCX,		670.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	13917,		(float)WINCX,		200.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_05,	14167,		(float)WINCX,		600.f,		ITEM_TYPE_NONE,	mobBList50,			mobBList50Size,			mobMListAngle180,		mobMListAngle180Size },

	{ MONSTER_TYPE_01,	14200,		(float)WINCX,		360.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size }, // UFO부대 시작
	{ MONSTER_TYPE_01,	14300,		(float)WINCX,		440.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_01,	14400,		(float)WINCX,		520.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size },
	{ MONSTER_TYPE_02,	14500,		(float)WINCX,		600.f,		ITEM_TYPE_NONE,	mobBList01,			mobBList01Size,			mobMList0,				mobMList0Size }, // UFO부대 끝

	{ MONSTER_TYPE_07,	15000,		1000.f,				450.f,		ITEM_TYPE_NONE,	mobBListBoss2,		mobBListBoss2Size,		mobMListBoss2,			mobMListBoss2Size },
	{ MONSTER_TYPE_08,	20000,		1000.f,				400.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList80,				mobMList80Size },
	{ MONSTER_TYPE_08,	20000,		1000.f,				400.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList81,				mobMList81Size },
	{ MONSTER_TYPE_08,	22000,		1000.f,				450.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList80,				mobMList80Size },
	{ MONSTER_TYPE_08,	22000,		1000.f,				450.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList81,				mobMList81Size },
	{ MONSTER_TYPE_06,	23000,		(float)WINCX,		200.f,		ITEM_TYPE_NONE,	mobBListBoss3,		mobBListBoss3Size,		mobMListAngle180,		mobMListAngle180Size },
	{ MONSTER_TYPE_08,	24000,		1000.f,				300.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList80,				mobMList80Size },
	{ MONSTER_TYPE_08,	24000,		1000.f,				300.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList81,				mobMList81Size },
	{ MONSTER_TYPE_08,	26000,		1000.f,				400.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList80,				mobMList80Size },
	{ MONSTER_TYPE_08,	26000,		1000.f,				400.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList81,				mobMList81Size },
	{ MONSTER_TYPE_08,	28000,		1000.f,				400.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList80,				mobMList80Size },
	{ MONSTER_TYPE_08,	28000,		1000.f,				400.f,		ITEM_TYPE_NONE,	mobBList8,			mobBList8Size,			mobMList81,				mobMList81Size },

	{ MONSTER_TYPE_06,	30000,		(float)WINCX,		450.f,		ITEM_TYPE_NONE,	mobBListBoss3,		mobBListBoss3Size,		mobMListAngle180,		mobMListAngle180Size },

	{ MONSTER_TYPE_04,	33000,		1600.f,				280.f,		ITEM_TYPE_NONE,	mobBListBoss1,		mobBListBoss1Size,		mobMListBoss1,		mobMListBoss1Size },

	{ MONSTER_TYPE_06,	36000,		(float)WINCX,		700.f,		ITEM_TYPE_NONE,	mobBListBoss3,		mobBListBoss3Size,		mobMListAngle180,		mobMListAngle180Size },

	{ MONSTER_TYPE_09,	36000,		(float)WINCX,		450.f,		ITEM_TYPE_NONE,	mobBListBoss4,		mobBListBoss4Size,		mobMListBoss4,		mobMListBoss4Size },


};
int iMobListSize = sizeof(MobList) / sizeof(stMonsterInfo);





























