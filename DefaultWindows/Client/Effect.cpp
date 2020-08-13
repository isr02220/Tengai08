#include "Effect.h"
#include "Bullet.h"
#include "Particle.h"
#include "Player.h"
#include "Monster.h"

CEffect::CEffect(const FLOAT& _degree, const FLOAT& _speed, const FLOAT& _diffuse, const UINT& _count, const LONG& _size)
	: CObj()
	, degree(_degree), diffuse(_diffuse), count(_count), size(_size) {
	objectType = OBJ::BULLET;
	lstrcpy(info->name, L"ÀÌÆåÆ®");
	info->size = { (FLOAT)_size, (FLOAT)_size , 0.f };
	speed = _speed;
	float rad = D3DXToRadian(_degree);
	info->force = { cosf(rad), sinf(rad), 0.f };
}

CEffect::~CEffect() {

}

void CEffect::Ready() {
	D3DXVECTOR3 vecLT = info->position - info->size / 2.f;
	D3DXVECTOR3 vecRB = info->position + info->size / 2.f;

	localVertex[0] = { info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	localVertex[1] = { info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[2] = { -info->size.x / 2.f,  info->size.y / 2.f, 0.f };
	localVertex[3] = { -info->size.x / 2.f, -info->size.y / 2.f, 0.f };
	FLOAT tempDegree;
	CObj* particleObj;
	for (UINT i = 0; i < count; i++) {
		tempDegree  = degree - diffuse * INT(count / 2 - i);
		particleObj = new CParticle(tempDegree, speed, size);
		particleObj->SetFillColor(RGB(255, 0, 0));
		particleObj->SetStrokeColor(RGB(255, 0, 0));
		particleObj->SetPosition(info->position);
		vecParticles.emplace_back(particleObj);
		CObjManager::GetInstance()->AddObject(particleObj, OBJ::EFFECT);
	}
	particleObj = new CParticle(tempDegree, 2.f, size*2);
	particleObj->SetFillColor(RGB(255, 255, 255));
	particleObj->SetStrokeColor(RGB(255, 255, 255));
	particleObj->SetPosition(info->position);
	vecParticles.emplace_back(particleObj);
	CObjManager::GetInstance()->AddObject(particleObj, OBJ::EFFECT);

	SetRect(rect, (LONG)vecLT.x, (LONG)vecLT.y, (LONG)vecRB.x, (LONG)vecRB.y);
}

int CEffect::Update() {
	CObj::UpdateRect();
	if (dead) {
		for (UINT i = 0; i < count + 1; i++) {
			vecParticles[i]->SetDead();
		}
		return STATE::DEAD;
	}
	info->position += info->force * speed;
	for (UINT i = 0; i < count + 1; i++) {
		vecParticles[i]->GetInfo()->size *= FLOAT(rand() % 300 + 700) / 1000.f;
		if(vecParticles[i]->GetInfo()->size.x < 15.f)
			vecParticles[i]->SetFillColor(RGB(255, 128, 0));
		if(vecParticles[i]->GetInfo()->size.x < 8.f)
			vecParticles[i]->SetFillColor(RGB(255, 255, 0));
		if(i == count)
			vecParticles[i]->GetInfo()->size *= 0.1f;
		else if (vecParticles[i]->GetInfo()->size.x < 0.1f)
			SetDead();
	}
	return STATE::NO_EVENT;
}

void CEffect::LateUpdate() {
}

void CEffect::Render(HDC hDC) {
	CObj::UpdateRect();

	HPEN   hPen = CreatePen(PS_SOLID, 1, strokeColor);
	HBRUSH hBrush = CreateSolidBrush(fillColor);

	HPEN   oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	//Ellipse(hDC, rect->left, rect->top, rect->right, rect->bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void CEffect::Release() {
}

void CEffect::OnCollision(CObj* _SrcObj) {
	SetDead();
}
