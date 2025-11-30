#include "pch.h"
#include "CSceneLab.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CObjEditArea.h"

CSceneLab::CSceneLab()
{
}

CSceneLab::~CSceneLab()
{
	Release();
}

void CSceneLab::Initialize()
{
	CObjEditArea* pEditArea = new CObjEditArea;
	pEditArea->Initialize();
	pEditArea->Set_CX(WINCX);
	pEditArea->Set_CY(WINCY);
	pEditArea->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_EDIT_AREA, pEditArea);
}

int CSceneLab::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneLab::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_Line(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_LINE));
}

void CSceneLab::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneLab::Release()
{
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
