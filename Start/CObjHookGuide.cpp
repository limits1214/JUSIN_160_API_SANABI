#include "pch.h"
#include "CObjHookGuide.h"
#include "CObjMouse.h"
#include "CScrollMgr.h"
#include "CObjMgr.h"
#include "CObjGrab.h"
#include "CObjPlayer.h"

CObjHookGuide::CObjHookGuide()
	:m_fMaxLength(0.f), m_pGrab(nullptr)
{
	ZeroMemory(&m_tLine, sizeof(LINE));
}

CObjHookGuide::~CObjHookGuide()
{
	Release();
}

void CObjHookGuide::Initialize()
{
	m_fMaxLength = 200.f;

	m_bUseMainScroll = true;
}

int CObjHookGuide::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjHookGuide::Late_Update()
{
}

void CObjHookGuide::Render(HDC hDC)
{
	if (false)
	{
		MoveToEx(hDC, m_tLine.tLeft.fX, m_tLine.tLeft.fY, nullptr);
		LineTo(hDC, m_tLine.tRight.fX, m_tLine.tRight.fY);
	}
	
}

void CObjHookGuide::Release()
{
}

void CObjHookGuide::On_Mouse_Pos(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
			POINT ptCurr = pMouse->Get_Pt_Curr();
		
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			

			float fParentX = m_pParent->Get_Info()->fX + iScrollX;
			float fParentY = m_pParent->Get_Info()->fY + iScrollY;
			float fPointX = (float)ptCurr.x ;
			float fPointY = (float)ptCurr.y ;
			LINEPOINT ptLeft{ fParentX, fParentY };
			LINEPOINT ptRight{ fPointX, fPointY };

			float fWidth =  ptRight.fX - ptLeft.fX;
			float fHeight =  ptRight.fY - ptLeft.fY;

			m_fAngle = atan2f(fHeight, fWidth);
			float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
			if (fDist > m_fMaxLength)
			{
				
 				ptRight.fX = ptLeft.fX + cosf(m_fAngle)* m_fMaxLength;
				ptRight.fY = ptLeft.fY + sinf(m_fAngle) * m_fMaxLength;
			}



			m_tLine = { ptLeft, ptRight };

			

			pMouse->Mouse_PreventEvent();
	}
}

void CObjHookGuide::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		float fParentX = m_pParent->Get_Info()->fX + iScrollX;
		float fParentY = m_pParent->Get_Info()->fY + iScrollY;

		if (m_pGrab != nullptr)
		{
			m_pGrab->Set_Dead();
		}

		CObjGrab* pGrab = new CObjGrab;
		pGrab->Initialize();
		pGrab->Set_Pos(fParentX, fParentY);
		pGrab->Set_Angle(m_fAngle);
		pGrab->Set_Target(m_pParent);
		//pGrab->Set_Parent(m_pParent);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pGrab);
		m_pGrab = pGrab;

		//pGrab->Set_Pos()

		//CObjMgr::Add_Object(OBJ_PLAYER, )

		//if (PtInRect(&m_tCloseRect, ptCurr))
		//{
		//	Set_Dead_Cascade();
		//	//Get_Parent()->Set_Dead_Cascade();;
		//	pMouse->Mouse_TargetBringToTop();
		//	pMouse->Mouse_PreventEvent();
		//}

		//if (PtInRect(&m_tHeaderRect, ptCurr))
		//{
		//	m_bMouseTrack = true;
		//	pMouse->Mouse_TargetBringToTop();
		//	pMouse->Mouse_PreventEvent();

		//}

		//if (PtInRect(&m_tRect, ptCurr))
		//{
		//	pMouse->Mouse_TargetBringToTop();
		//	pMouse->Mouse_PreventEvent();
		//}

		//if (PtInRect(&m_tScrollRect, ptCurr))
		//{
		//	m_bMouseScrollTrack = true;
		//	pMouse->Mouse_TargetBringToTop();
		//	pMouse->Mouse_PreventEvent();
		//}
	}
}

void CObjHookGuide::On_Mouse_Key_Up(CObj* pMouse)
{

	if (m_pGrab != nullptr)
	{
		m_pGrab->Set_Dead();
	}
	
	//auto view = CObjMgr::Get_Instance()->Get_HierarchyView();
	//auto parentsChild = view[m_pParent];
	//for (pair<OBJID, CObj*>& pair : parentsChild)
	//{
	//	auto pGrab = dynamic_cast<CObjGrab*>(pair.second);
	//	if (pGrab != nullptr)
	//	{
	//		//pGrab->Set_Dead();
	//	}
	//}
}

void CObjHookGuide::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CObjHookGuide::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
}
