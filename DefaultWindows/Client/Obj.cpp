#include "Obj.h"
CObj::CObj() {
	ZeroMemory(&info, sizeof(INFO));
	info = new INFO();
	rect = new RECT();
}
CObj::CObj(FLOAT _positionX, FLOAT _positionY) {
	ZeroMemory(info, sizeof(INFO));
	info->position.x = _positionX;
	info->position.y = _positionY;
}

CObj::~CObj() {
	delete info;
	delete rect;
}

void CObj::UpdateRect() {
	rect->left = LONG(info->position.x - (info->size.x / 2.f));
	rect->top = LONG(info->position.y - (info->size.y / 2.f));
	rect->right = LONG(info->position.x + (info->size.x / 2.f));
	rect->bottom = LONG(info->position.y + (info->size.y / 2.f));

}
