#include "Monster.h"
#include "Bullet.h"
#include "Effect.h"

void CMonster::Ready() {
	info = new INFO();
    SetName(L"¸ó½ºÅÍ");
	info->position = { 500.f, 600.f , 0.f };
	info->size = { 100.f, 100.f , 0.f };
	info->force = { 0.f, 0.f , 0.f };
	info->look = { 1.f, 0.f, 0.f };
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	rect = new RECT();

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
	
	m_StartTime = GetTickCount();
}

INT CMonster::Update() {
    if (dead)
        return STATE::DEAD;

	DWORD dwCurTime = GetTickCount();

// Move Pattern
	list<stMovePattern>::iterator iterM = listMoveStandby.begin();
	while (iterM != listMoveStandby.end())
	{
		if (m_StartTime + iterM->dwStartTime > dwCurTime) {
			break;
		}

		info->force.x = cosf(D3DXToRadian(iterM->fDirection));
		info->force.y = sinf(D3DXToRadian(iterM->fDirection));

		speed = iterM->fSpeed;

		iterM = listMoveStandby.erase(iterM);
	}

// Bullet Pattern
	list<stBulletPattern>::iterator iterB = listBulletStandby.begin();
	while (iterB != listBulletStandby.end())
	{
		if (m_StartTime + iterB->dwStartTime > dwCurTime) {
			break;
		}

		if (iterB->horming) {
			Shoot(CObjManager::GetInstance()->GetPlayer(), iterB->fDirection, iterB->fSpeed, 20, iterB->iBulletSize, D3DXVECTOR3((float)iterB->iStartX, (float)iterB->iStartY, 0.f));
		}
		else {
			Shoot(iterB->fDirection, iterB->fSpeed, 20, iterB->iBulletSize, D3DXVECTOR3((float)iterB->iStartX, (float)iterB->iStartY, 0.f));
		}

		iterB = listBulletStandby.erase(iterB);
	}

// Move
	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };

	info->position += info->force * speed;
	angleRot += 3.f;
	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&m_matRotation, D3DXToRadian(angleRot));
	D3DXMatrixTranslation(&m_matTransform, info->position.x, info->position.y, info->position.z);
	D3DXMatrixRotationZ(&m_matRevolution, D3DXToRadian(angleRev));

	D3DXMatrixIdentity(&m_matW);
	m_matW = m_matScale * m_matRotation * m_matTransform * m_matRevolution;
	//m_matW = m_matScale * m_matTransform;

	for (size_t i = 0; i < 4; i++) {
		D3DXVec3TransformCoord(&globalVertex[i], &localVertex[i], &m_matW);
	}

	// Rect
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;
	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);

	// Dead
	if (info->position.x < 0) {
		if (timer + 1000 < GetTickCount())
			SetDead();
	}
	else {
		timer = GetTickCount();
	}
    return STATE::NO_EVENT;
}

void CMonster::LateUpdate() {

}

void CMonster::Render(HDC hDC) {
	HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
	HBRUSH hBrush = CreateSolidBrush(fillColor);

	FLOAT  hpPercent = (FLOAT)m_hp / (FLOAT)m_maxHp;
	INT colorR = 255;
	INT colorG = 255;
	if (hpPercent > 0.5f) {
		colorR = INT(255 - hpPercent * 510);
		colorG = 255;
	}
	else {
		colorG = INT((hpPercent * hpPercent) * 510);
		if (colorG < 0) colorG = 0;
		colorR = 255;
	}
	HPEN   hPanelPen   = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH hPanelBrush = CreateSolidBrush(RGB(0, 0, 0));
	HPEN   hHpPen   = CreatePen(PS_NULL, 1, RGB(0,0,0));
	HBRUSH hHpBrush = CreateSolidBrush(RGB(colorR, colorG, 0));
	HPEN   oldPen   = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	DrawPolygon(hDC);

	RECT rc = {};
	SetRect(&rc, rect->left, rect->bottom, rect->right, rect->bottom + 20);

	(HPEN)SelectObject(hDC, hPanelPen);
	(HBRUSH)SelectObject(hDC, hPanelBrush);
	Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);

	(HPEN)SelectObject(hDC, hHpPen);
	(HBRUSH)SelectObject(hDC, hHpBrush);
	Rectangle(hDC, rc.left+1, rc.top, rc.left + INT(hpPercent * (rc.right - rc.left)), rc.bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(hPanelPen);
	DeleteObject(hPanelBrush);
	DeleteObject(hHpPen);
	DeleteObject(hHpBrush);
}

void CMonster::Release() {

}

void CMonster::OnCollision(CObj* _TargetObj) {
	if (_TargetObj->GetObjectType() == OBJ::BULLET) {

		CObj* effect = new CEffect(FLOAT(rand() % 30), 15.f, 15.f, 4, 20);
		effect->SetPosition(info->position);
		effect->Ready();
		CObjManager::GetInstance()->AddObject(effect, OBJ::EFFECT);

		m_hp -= dynamic_cast<CBullet*>(_TargetObj)->GetDamage();
		if (m_hp <= 0) {
			CObj* effect = new CEffect(FLOAT(rand() % 30), 5.f, 15.f, 22, 20);
			effect->SetPosition(info->position);
			effect->Ready();
			CObjManager::GetInstance()->AddObject(effect, OBJ::EFFECT);
			SetDead();
		}
	}
}

void CMonster::Move() {
}

void CMonster::Attack() {

}

void CMonster::Shoot(FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, D3DXVECTOR3 _posoffset, COLORREF _fillColor, COLORREF _strokeColor) {
	CObj* bulletObj = new CBullet(_degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position + _posoffset);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::MONSTERBULLET);
}

void CMonster::Shoot(CObj* _targetObj, FLOAT _degree, FLOAT _speed, INT _damage, LONG _size, D3DXVECTOR3 _posoffset, COLORREF _fillColor, COLORREF _strokeColor) {
	D3DXVECTOR3 v3Dir = *_targetObj->GetPosition() - info->position;
	FLOAT degree = _degree + D3DXToDegree(atan2f(v3Dir.y, v3Dir.x));

	CObj* bulletObj = new CBullet(degree, _speed, _damage, _size);
	bulletObj->SetFillColor(_fillColor);
	bulletObj->SetStrokeColor(_strokeColor);
	bulletObj->SetPosition(info->position + _posoffset);
	CObjManager::GetInstance()->AddObject(bulletObj, OBJ::MONSTERBULLET);
}

void CMonster::SetInfo(stMonsterInfo * mobinfo)
{
	// Monster Info
	fillColor		= mobTypeList[mobinfo->type].color;
	info->size.x	= (FLOAT)mobTypeList[mobinfo->type].iCX;
	info->size.y	= (FLOAT)mobTypeList[mobinfo->type].iCY;
	m_maxHp			= mobTypeList[mobinfo->type].iHP;
	m_hp			= mobTypeList[mobinfo->type].iHP;
	m_point			= mobTypeList[mobinfo->type].iPoint;

	info->position.x = mobinfo->fStartX;
	info->position.y = mobinfo->fStartY;
	m_dropItem = mobinfo->dropItem;

	// Bullet Pattern
	for (int i = 0; i < mobinfo->blistNum; i++) {
		listBulletStandby.emplace_back(mobinfo->blist[i]);
	}

	// Move Pattern
	for (int i = 0; i < mobinfo->mlistNum; i++) {
		listMoveStandby.emplace_back(mobinfo->mlist[i]);
	}
}
