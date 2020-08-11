#include "Obj.h"
CObj::CObj() {
	ZeroMemory(&info, sizeof(INFO));
}
CObj::CObj(FLOAT _positionX, FLOAT _positionY) {
	ZeroMemory(&info, sizeof(INFO));
	info.position.x = _positionX;
	info.position.y = _positionY;
}

CObj::~CObj() {
}

void CObj::UpdateRect() {
	rect.left = LONG(info.position.x - (info.size.x / 2));
	rect.top = LONG(info.position.y - (info.size.y / 2));
	rect.right = LONG(info.position.x + (info.size.x / 2));
	rect.bottom = LONG(info.position.y + (info.size.y / 2));

}
