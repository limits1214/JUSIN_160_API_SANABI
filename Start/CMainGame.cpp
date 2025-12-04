#include "pch.h"
#include "CMainGame.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CObjMouse.h"
#include "CUIObjDbgPanel.h"
#include "CUIObjSceneDbgPanel.h"
#include "CUIObjBmpDbgPannel.h"
#include "CEditMgr.h"
#include "CUIObjScrollDbgPanel.h"
#include "CUIObjTileEditDbgPanel.h"

CMainGame::CMainGame()
	:m_dwFPSTime(GetTickCount())
{
}

CMainGame::~CMainGame()
{
	Release();
}

// 게임시작시
// 로고 씬으로 보내주고
// 마우스OBJ 추가해준다.
void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);

	CObjMouse* pMouse = new CObjMouse;
	pMouse->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, pMouse);



#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG
}

// 업데이트시
// 타임매니터 틱 업데이트 해주고
// 현재씬 업데이트 돌려준다.
// 디버그 전용 버튼 핸들러를 등록해준다.
//
// 주의! 키 인풋 처리는 업데이트에서만 해주자
void CMainGame::Update()
{
	CTimeMgr::Get_Instance()->Update_Tick_Count();
	
	CSceneMgr::Get_Instance()->Update();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		CUIObjDbgPanel* pDbgPanel = new CUIObjDbgPanel;
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
		pDbgPanel->Initialize();
		pDbgPanel->Set_CX(WINCX >> 2);
		pDbgPanel->Set_CY(WINCY >> 2);
		pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
		pDbgPanel->Set_Header_Text(_T("DBG_PANEL"));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		CUIObjSceneDbgPanel* pDbgPanel = new CUIObjSceneDbgPanel;
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
		pDbgPanel->Initialize();
		pDbgPanel->Set_CX(WINCX >> 2);
		pDbgPanel->Set_CY(WINCY >> 2);
		pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
		pDbgPanel->Set_Header_Text(_T("SCENE_PANEL"));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		CUIObjBmpDbgPannel* pDbgPanel = new CUIObjBmpDbgPannel;
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
		pDbgPanel->Initialize();
		pDbgPanel->Set_CX(WINCX >> 2);
		pDbgPanel->Set_CY(WINCY >> 2);
		pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
		pDbgPanel->Set_Header_Text(_T("BMP_PANEL"));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F4))
	{
		CUIObjScrollDbgPanel* pDbgPanel = new CUIObjScrollDbgPanel;
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
		pDbgPanel->Initialize();
		pDbgPanel->Set_CX(WINCX >> 2);
		pDbgPanel->Set_CY(WINCY >> 2);
		pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
		pDbgPanel->Set_Header_Text(_T("SCROLL_PANEL"));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F5))
	{
		CUIObjTileEditDbgPanel* tileEditDbgPandel = new CUIObjTileEditDbgPanel;
		tileEditDbgPandel->Initialize();
		tileEditDbgPandel->Set_CX(WINCX >> 2);
		tileEditDbgPandel->Set_CY(WINCY >> 2);
		tileEditDbgPandel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
		tileEditDbgPandel->Set_Header_Text(_T("TILE_EDIT_PANEL"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, tileEditDbgPandel);
	}
}

// 업데이트 이후에 돌릴애들
// 현재씬 레이트 업데이트 돌려주고
// 키 인풋 초기화를 해준다.
void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();

	CKeyMgr::Get_Instance()->Update();
}

// 렌더타임
// 1초마다 윈도우 텍스트에 프레임 표시해준다.
// 멤디시를 현재 디시로부터 만들어내고
// 씬 렌더의 파라미터로 멤디시를 보내준다.
// 멤디시에 렌더가 끝난뒤에
// 멤디시를 현재 디시로 BitBlt 복사 해준다.(윈도우api 더블버퍼링 방식)
void CMainGame::Render()
{
	{
		++m_iFPS;
		CTimeMgr::Delay(&m_dwFPSTime, 1000,
			[&]() {
				swprintf_s(m_szFPS, _T("FPS: %d"), m_iFPS);
				m_iFPS = 0;
				SetWindowText(g_hWnd, m_szFPS);
			}
		);
	}
	
	{
		HDC memDC = CreateCompatibleDC(m_hDC);
		HBITMAP bmp = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
		HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

		Rectangle(memDC, 0, 0, WINCX, WINCY);

		CSceneMgr::Get_Instance()->Render(memDC);

		BitBlt(
			m_hDC,
			0, 0,
			WINCX, WINCY,

			memDC,
			0, 0,
			SRCCOPY
		);

		HBITMAP oldBmp2 = (HBITMAP)SelectObject(memDC, oldBmp);

		DeleteObject(oldBmp);
		DeleteObject(oldBmp2);
		DeleteObject(memDC);
	}
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSceneMgr::Destroy_Instance();

	CObjMgr::Get_Instance()->Release();
	CObjMgr::Destroy_Instance();

	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CEditMgr::Destroy_Instance();
	CTimeMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
