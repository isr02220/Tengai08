#include "framework.h"
#include "Scene.h"

CScene::CScene()
{
	objMgr->GetInstance();
}


CScene::~CScene()
{
	objMgr->DestroyInstance();
}
