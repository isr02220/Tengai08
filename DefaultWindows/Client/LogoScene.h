#pragma once
#include "Scene.h"
class CLogoScene
	: public CScene {
public:
	explicit CLogoScene();
	virtual ~CLogoScene();
	// CScene��(��) ���� ��ӵ�
	virtual void Ready() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

