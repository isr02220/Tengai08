#pragma once
#include "framework.h"
class CPlayer {
public:
	CPlayer();
	~CPlayer();

public:
	void Ready();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
	void UpdateDraw();
	void Move();
	void MoveTopdown();
protected:
	INFO* info = nullptr;
	RECT* rect = nullptr;
	FLOAT angle = 0.f;
	FLOAT speed = 5.f;
	D3DXVECTOR3 localVertex[4];
	D3DXVECTOR3 globalVertex[4];
	D3DXVECTOR3 barrel;
	D3DXVECTOR3 barrelEnd;
	FLOAT gravity = 0.02f;
	
};

