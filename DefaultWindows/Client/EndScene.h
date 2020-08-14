#pragma once
#include "Scene.h"
class CEndScene :
	public CScene
{
public:
	explicit CEndScene();
	virtual ~CEndScene();

	// CScene��(��) ���� ��ӵ�
	virtual void Ready() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

