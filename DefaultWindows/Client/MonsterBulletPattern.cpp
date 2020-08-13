
#include "framework.h"
#include "MonsterBulletPattern.h"

stBulletPattern mobBList01[] = {
	// 시작 시간	시작 X위치	시작 Y위치	방향	속도	총알크기	공전	유도여부
	{ 1000,			0,			0,			170.f,	10.f,	10,			0.f,	false },
	{ 1000,			0,			0,			180.f,	10.f,	10,			0.f,	false },
	{ 1000,			0,			0,			190.f,	10.f,	10,			0.f,	false }
};
int mobBList01Size = sizeof(mobBList01) / sizeof(stBulletPattern);

stBulletPattern mobBList50[] = {
	// 시작 시간	시작 X위치	시작 Y위치	방향	속도	총알크기	공전	유도여부
	{ 50,			0,			0,			0.f,	10.f,	10,			0.f,	true }
};
int mobBList50Size = sizeof(mobBList50) / sizeof(stBulletPattern);


stBulletPattern mobBListHorming1[] = {
	// 시작 시간	시작 X위치	시작 Y위치	방향	속도	총알크기	공전	유도여부
	{ 2000,			0,			0,			0.f,	10.f,	10,			0.f,	true }
};
int mobBListHorming1Size = sizeof(mobBListHorming1) / sizeof(stBulletPattern);

stBulletPattern mobBListBoss1[] = {
	// 시작 시간	시작 X위치	시작 Y위치	방향	속도	총알크기	공전	유도여부
	{ 4000,			0,			0,			22.5f,	5.f,	20,			0.f,	false },
	{ 4050,			0,			0,			45.f,	5.f,	20,			0.f,	false },
	{ 4100,			0,			0,			67.5f,	5.f,	20,			0.f,	false },
	{ 4150,			0,			0,			90.f,	5.f,	20,			0.f,	false },
	{ 4200,			0,			0,			112.5f,	5.f,	20,			0.f,	false },
	{ 4250,			0,			0,			135.f,	5.f,	20,			0.f,	false },
	{ 4300,			0,			0,			157.5f,	5.f,	20,			0.f,	false },
	{ 4350,			0,			0,			180.f,	5.f,	20,			0.f,	false },
	{ 4400,			0,			0,			202.5f,	5.f,	20,			0.f,	false },
	{ 4450,			0,			0,			225.f,	5.f,	20,			0.f,	false },
	{ 4500,			0,			0,			247.5f,	5.f,	20,			0.f,	false },
	{ 4550,			0,			0,			270.f,	5.f,	20,			0.f,	false },
	{ 4600,			0,			0,			292.5f,	5.f,	20,			0.f,	false },
	{ 4650,			0,			0,			315.f,	5.f,	20,			0.f,	false },
	{ 4700,			0,			0,			337.5f,	5.f,	20,			0.f,	false },
	{ 4750,			0,			0,			360.f,	5.f,	20,			0.f,	false },

	{ 6000,			0,			0,			0.f,	10.f,	10,			0.f,	true },
	{ 6100,			0,			0,			5.f,	10.f,	10,			0.f,	true },
	{ 6100,			0,			0,			-5.f,	10.f,	10,			0.f,	true },
	{ 6200,			0,			0,			0.f,	10.f,	10,			0.f,	true },
	{ 6200,			0,			0,			-10.f,	10.f,	10,			0.f,	true },
	{ 6200,			0,			0,			10.f,	10.f,	10,			0.f,	true },

	{ 7000,			0,			0,			0.f,	10.f,	10,			0.f,	true },
	{ 7100,			0,			0,			5.f,	10.f,	10,			0.f,	true },
	{ 7100,			0,			0,			-5.f,	10.f,	10,			0.f,	true },
	{ 7200,			0,			0,			0.f,	10.f,	10,			0.f,	true },
	{ 7200,			0,			0,			-10.f,	10.f,	10,			0.f,	true },
	{ 7200,			0,			0,			10.f,	10.f,	10,			0.f,	true }
};
int mobBListBoss1Size = sizeof(mobBListBoss1) / sizeof(stBulletPattern);
