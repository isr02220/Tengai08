#pragma once
#include "Scene.h"
class CObj;
class CPlayer;
class CStageScene :
    public CScene {
public:
	explicit CStageScene();
	virtual ~CStageScene();
	// CScene을(를) 통해 상속됨
	virtual void Ready() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

protected:
	CObj* m_pPlayer = nullptr;
};

