#include "pch.h"
#include "CSceneMenu.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjButton.h"
#include "CObjMgr.h"

CSceneMenu::CSceneMenu()
{
}

CSceneMenu::~CSceneMenu()
{
	Release();
}

void CSceneMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	CObj* pButton = CAbstractFactory<CObjButton>::Create(200.f, 400.f);
	pButton->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CObjButton>::Create(400.f, 400.f);
	pButton->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CObjButton>::Create(600.f, 400.f);
	pButton->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);
}

int CSceneMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneMenu::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");
	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneMenu::Release()
{
	CObjMgr::Get_Instance()->Dead_ID(OBJ_BUTTON);

	CBmpMgr::Get_Instance()->Delete_Bmp(L"Start");
	CBmpMgr::Get_Instance()->Delete_Bmp( L"Edit");
	CBmpMgr::Get_Instance()->Delete_Bmp( L"Exit");
	CBmpMgr::Get_Instance()->Delete_Bmp( L"Menu");
}
