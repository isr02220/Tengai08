#include "Obj.h"
CObj::CObj() {
	info = new INFO();
	rect = new RECT();
	ZeroMemory(info, sizeof(INFO));
}
CObj::CObj(FLOAT _positionX, FLOAT _positionY) {
	info = new INFO();
	rect = new RECT();
	ZeroMemory(info, sizeof(INFO));
	info->position.x = _positionX;
	info->position.y = _positionY;
}

CObj::~CObj() {
	SafeDelete(info);
	SafeDelete(rect);
}

void CObj::UpdateRect() {
	rect->left   = LONG(info->position.x - (info->size.x / 2.f));
	rect->top    = LONG(info->position.y - (info->size.y / 2.f));
	rect->right  = LONG(info->position.x + (info->size.x / 2.f));
	rect->bottom = LONG(info->position.y + (info->size.y / 2.f));

}
