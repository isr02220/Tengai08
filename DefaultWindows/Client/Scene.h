#pragma once
class CScene abstract
{
public:
	explicit CScene();
	virtual ~CScene();
public:
	virtual void Ready()=0; 
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

};

