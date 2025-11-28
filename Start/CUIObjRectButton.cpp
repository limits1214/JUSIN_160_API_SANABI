#include "pch.h"
#include "CUIObjRectButton.h"
#include "CKeyMgr.h"
#include "CUIObjText.h"
#include "CObjMgr.h"
#include "CObjMouse.h"

CUIObjRectButton::CUIObjRectButton()
{
	m_OnKeydownFunc = nullptr;
	m_colDefault = RGB(255, 255, 255);
	m_colHover = RGB(255, 0, 0);
	m_colCur = m_colDefault;

	Set_DbgName(_T("CUIObjRectButton"));
}

CUIObjRectButton::~CUIObjRectButton()
{
	Release();
}

void CUIObjRectButton::Initialize()
{
	//CUIObjText* pText = new CUIObjText;
	//pText->Initialize();
	//pText->Set_CX(100);
	//pText->Set_CY(100);
	//pText->Set_Pos(0, 0);
	//pText->Set_Text(_T("zzzzz"));
	//pText->Set_Parent(this);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText);
}

int CUIObjRectButton::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//POINT pt{};
	//GetCursorPos(&pt);
	//ScreenToClient(g_hWnd, &pt);
	//if (PtInRect(&m_tRect, pt))
	//{
	//	//if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	//	//{
	//	//	if (m_OnKeydownFunc != nullptr)
	//	//	{
	//	//		m_OnKeydownFunc();
	//	//	}
	//	//}
	//	m_colCur = m_colHover;
	//}
	//else
	//{
	//	m_colCur = m_colDefault;
	//}
	m_colCur = m_colDefault;
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CUIObjRectButton::Late_Update()
{
}

void CUIObjRectButton::Render(HDC hDC)
{
	if (!m_bVisible)
		return;
	COLORREF color = m_colCur;
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
	//DrawText(hDC, m_szText, lstrlen(m_szText), &m_tRect, DT_CENTER);
}

void CUIObjRectButton::Release()
{
}

void CUIObjRectButton::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		if (PtInRect(&m_tRect, ptCurr))
		{
			if (m_OnKeydownFunc != nullptr)
			{
				m_OnKeydownFunc();
			}
			//pMouse->Mouse_TargetActive();
			pMouse->Mouse_PreventEvent();
		}
	}
}

void CUIObjRectButton::On_Mouse_Key_Up(CObj* pMouse)
{
}

void CUIObjRectButton::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CUIObjRectButton::On_Mouse_Pos(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		if (PtInRect(&m_tRect, ptCurr))
		{
			//if (m_OnKeydownFunc != nullptr)
			//{
			//	m_OnKeydownFunc();
			//}
			//pMouse->Mouse_TargetActive();
			pMouse->Mouse_PreventEvent();
			m_colCur = m_colHover;
		}
		else
		{
			//m_colCur = m_colDefault;
			//pMouse->Mouse_PreventEvent();
		}
	}
}
