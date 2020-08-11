#pragma once
#include "Scene.h"
class CLogoScene
	: public CScene {
public:
	explicit CLogoScene();
	virtual ~CLogoScene();
	// CScene을(를) 통해 상속됨
	virtual void Ready() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

