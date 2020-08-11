#pragma once
#include "Scene.h"
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
	CPlayer* m_pPlayer = nullptr;
};

