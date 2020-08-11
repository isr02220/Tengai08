#pragma once

const int WINCX = 1600;
const int WINCY = 900;
const FLOAT pi = 3.141592f;
const FLOAT radian = 180 / pi;
extern HWND g_hWnd;

typedef struct tagInfo {
	TCHAR name[32];
	D3DXVECTOR3 position;
	D3DXVECTOR3 force;
	D3DXVECTOR3 size;
	D3DXVECTOR3 look;

}INFO;

template<typename T>
void SafeDelete(T& rObj) {
	if (rObj) {
		delete rObj;
		rObj = nullptr;
	}
}

namespace OBJ {
	enum TYPE {
		BACKGROUND,
		BULLET,
		MONSTERBULLET,
		BOMB,
		PLAYER,
		PET,
		MONSTER,
		ITEM,
		EFFECT,
		UI,
		END
	};
}

namespace STATE {
	enum ID {
		NO_EVENT,
		DEAD
	};
}