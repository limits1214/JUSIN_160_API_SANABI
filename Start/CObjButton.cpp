#include "pch.h"
#include "CObjButton.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"

CObjButton::CObjButton()
{
	Set_DbgName(_T("CObjButton"));
}

CObjButton::~CObjButton()
{
	Release();
}

void CObjButton::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
}

int CObjButton::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(_T("Start"), m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_TUTORIAL);
			else if (!lstrcmp(_T("Edit"), m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_TILEEIDT);
			}	
			else
				DestroyWindow(g_hWnd);
		}
		m_iDrawID = 1;
	}
	else
	{
		m_iDrawID = 0;
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjButton::Late_Update()
{
}

void CObjButton::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,				// 복사 받을 DC
		m_tRect.left,	// 복사 받을 공간의 LEFT	
		m_tRect.top,				// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
		hMemDC,				// 복사 할 DC
		m_iDrawID * (int)m_tInfo.fCX,					// 복사할 이미지의 LEFT, TOP
		0,
		(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거할 색상
}

void CObjButton::Release()
{
}
