#include "pch.h"
#include "CSceneLogo.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"

CSceneLogo::CSceneLogo()
{
}

CSceneLogo::~CSceneLogo()
{
	Release();
}

void CSceneLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	m_dwNextSceneTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
}

int CSceneLogo::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return 0;
	}

	CTimeMgr::Delay(&m_dwNextSceneTime, 100, []() {
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		});

	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneLogo::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneLogo::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);
}

void CSceneLogo::Release()
{
	CBmpMgr::Get_Instance()->Delete_Bmp(_T("Logo"));
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
