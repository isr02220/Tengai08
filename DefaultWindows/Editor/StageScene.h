#pragma once
#include "Scene.h"
class CObj;
class CPlayer;
class CStageScene :
    public CScene {
public:
	explicit CStageScene();
	virtual ~CStageScene();
	// CScene��(��) ���� ��ӵ�
	virtual void Ready() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

protected:
	CObj* m_pPlayer = nullptr;
};

