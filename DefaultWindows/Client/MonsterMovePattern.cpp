#include "framework.h"
#include "MonsterMovePattern.h"

stMovePattern mobMList0[] = {
	// 시작 시간	방향	속도
	{	0,			180.f,	4.0f },
	{	2500,		180.f,  0.0f },
	{	3000,		0.f,    4.0f }
};
int mobMList0Size = sizeof(mobMList0) / sizeof(stMovePattern);

stMovePattern mobMList1[] = {
	// 시작 시간	방향	속도
	{	0,			90.f,	4.0f },
	{	2000,		90.f,	0.0f },
	{	3000,		190.f,  4.0f }
};
int mobMList1Size = sizeof(mobMList1) / sizeof(stMovePattern);

stMovePattern mobMListAngle175[] = {
	// 시작 시간	방향	속도
	{	0,			175.f,	4.0f }
};
int mobMListAngle175Size = sizeof(mobMListAngle175) / sizeof(stMovePattern);

stMovePattern mobMListAngle180[] = {
	// 시작 시간	방향	속도
	{	0,			180.f,	4.0f }
};
int mobMListAngle180Size = sizeof(mobMListAngle180) / sizeof(stMovePattern);

stMovePattern mobMListAngle185[] = {
	// 시작 시간	방향	속도
	{	0,			185.f,	6.0f }
};
int mobMListAngle185Size = sizeof(mobMListAngle185) / sizeof(stMovePattern);

stMovePattern mobMListAngle190[] = {
	// 시작 시간	방향	속도
	{	0,			190.f,	4.0f }
};
int mobMListAngle190Size = sizeof(mobMListAngle190) / sizeof(stMovePattern);

stMovePattern mobMListBoss1[] = {
	// 시작 시간	방향	속도
	{	0,			180.f,	3.0f },
	{	1500,		180.f,	0.0f },
	{	6000,		180.f,  3.0f },
	{	6400,		180.f,  2.0f },
	{	6600,		180.f,  2.0f }
};
int mobMListBoss1Size = sizeof(mobMListBoss1) / sizeof(stMovePattern);