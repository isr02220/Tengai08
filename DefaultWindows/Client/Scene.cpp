#include "framework.h"
#include "Scene.h"

CScene::CScene()
{
	objMgr = objMgr->GetInstance();
}


CScene::~CScene()
{
	objMgr->DestroyInstance();
}
