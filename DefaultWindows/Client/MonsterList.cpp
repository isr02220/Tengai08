
#include "framework.h"
#include "MonsterBulletPattern.h"
#include "MonsterMovePattern.h"
#include "MonsterList.h"

// �ݵ�� �ð� ������� ���ĵǾ��־�� ��
stMonsterInfo MobList[1] = {
	// Ÿ��				���� �ð�	����X��ġ			����Y��ġ	������			�Ѿ����ϸ��	����	�̵����ϸ��	����
	{ MONSTER_TYPE_01,	1000,		(float)WINCX-100,	500.f,		ITEM_TYPE_NONE,	mobBList01,		3,		mobMList0,		2 }
};
