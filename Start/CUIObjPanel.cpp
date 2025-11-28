#include "pch.h"
#include "CUIObjPanel.h"
#include "CKeyMgr.h"
#include "CObjMouse.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CObjGrp.h"

CUIObjPanel::CUIObjPanel()
	:m_iHeaderHeight(20), m_bMouseTrack(false), m_pUIContentBox(nullptr), m_iYScrollWidth(10), m_bMouseScrollTrack(false)
	, m_iYScrollLength(0), m_fYScrollPercent(0.f)
{
	Set_DbgName(_T("CUIObjPanel"));
}

CUIObjPanel::~CUIObjPanel()
{
	Release();
}

void CUIObjPanel::Set_Header_Text(const TCHAR* pText)
{
	CUIObjText* pTextUI = new CUIObjText;
	//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
	CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pTextUI);
	pTextUI->Initialize();
	pTextUI->Set_Text(pText);
	pTextUI->Set_Parent(this);
	pTextUI->Set_Pos(0, -(m_tInfo.fCY * 0.5) + (m_iHeaderHeight * 0.5));
}

void CUIObjPanel::Initialize()
{
	CObjGrp* pGrp = new CObjGrp;
	//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
	CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pGrp);
	pGrp->Initialize();
	pGrp->Set_Pos(-(m_iYScrollWidth * 0.5), +(m_iHeaderHeight * 0.5));
	//pBox->Set_Pos(0, 0);
	//pBox->Set_Pos(0, (m_iHeaderHeight ));
	pGrp->Set_Parent(this);

	m_pUIContentBox = pGrp;
}

int CUIObjPanel::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	m_tHeaderRect = m_tRect;
	m_tHeaderRect.bottom = m_tHeaderRect.top + m_iHeaderHeight;

	m_tCloseRect = m_tHeaderRect;
	m_tCloseRect.left = m_tHeaderRect.right - m_iHeaderHeight;
	m_tCloseRect.bottom = m_tHeaderRect.top + m_iHeaderHeight;

	m_tScrollRect = m_tRect;
	m_tScrollRect.left = m_tRect.right - m_iYScrollWidth;
	m_tScrollRect.top = m_tRect.top + m_iHeaderHeight + m_iYScrollLength;
	//m_tScrollRect.bottom -= ((m_tScrollRect.bottom - m_tScrollRect.top) * 0.5) + m_iScrollLength;
	// TODO: 스크롤 높이는 고정값이 아니라 컨텐츠 사이즈에 비례해서 조절해야함
	m_iYScrollHeight = m_iYScrollWidth * 2;
	m_tScrollRect.bottom = m_tScrollRect.top + m_iYScrollHeight;

	//m_tContentRect = m_tRect;
	//m_tContentRect.top += m_iHeaderHeight;


	LONG contentWidth = m_tRect.right - m_tRect.left - m_iYScrollWidth;
	LONG contentHeight = m_tRect.bottom - (m_tRect.top + m_iHeaderHeight);

	m_pUIContentBox->Set_CX(contentWidth);
	m_pUIContentBox->Set_CY(contentHeight );
	
	

	return OBJ_NOEVENT;
}

void CUIObjPanel::Late_Update()
{
}

void CUIObjPanel::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Rectangle(hDC, m_tHeaderRect.left, m_tHeaderRect.top, m_tHeaderRect.right, m_tHeaderRect.bottom);
	Rectangle(hDC, m_tCloseRect.left, m_tCloseRect.top, m_tCloseRect.right, m_tCloseRect.bottom);
	Rectangle(hDC, m_tScrollRect.left, m_tScrollRect.top, m_tScrollRect.right, m_tScrollRect.bottom);

	//Rectangle(hDC, m_tContentRect.left + 5, m_tContentRect.top + 5, m_tContentRect.right - 5, m_tContentRect.bottom - 5);
}

void CUIObjPanel::Release()
{
}

void CUIObjPanel::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		if (PtInRect(&m_tCloseRect, ptCurr))
		{
			Set_Dead_Cascade();
			//Get_Parent()->Set_Dead_Cascade();;
			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}

		if (PtInRect(&m_tHeaderRect, ptCurr))
		{
			m_bMouseTrack = true;
			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
			
		}

		if (PtInRect(&m_tRect, ptCurr))
		{
			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}

		if (PtInRect(&m_tScrollRect, ptCurr))
		{
			m_bMouseScrollTrack = true;
			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}
	}
}

void CUIObjPanel::On_Mouse_Key_Up(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		if (m_bMouseTrack)
		{
			m_bMouseTrack = false;
			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}

		if (m_bMouseScrollTrack)
		{
			m_bMouseScrollTrack = false;
			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}
	}
}

void CUIObjPanel::On_Mouse_Key_Pressing(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		if (m_bMouseTrack)
		{
			POINT ptCurr = pMouse->Get_Pt_Curr();
			POINT ptPrev = pMouse->Get_Pt_Prev();
			long movedX = ptCurr.x - ptPrev.x;
			long movedY = ptCurr.y - ptPrev.y;

			m_tInfo.fX += movedX;
			m_tInfo.fY += movedY;

			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}

		if (m_bMouseScrollTrack)
		{
			POINT ptCurr = pMouse->Get_Pt_Curr();
			POINT ptPrev = pMouse->Get_Pt_Prev();
			long movedX = ptCurr.x - ptPrev.x;
			long movedY = ptCurr.y - ptPrev.y;

			m_iYScrollLength += movedY;

			if (m_iYScrollLength < 0)
			{
				m_iYScrollLength = 0;
			}
			
			auto maxY = m_pUIContentBox->Get_Info()->fCY - m_iYScrollHeight;

			if (m_iYScrollLength > maxY)
			{
				m_iYScrollLength = maxY;
			}

			m_fYScrollPercent = m_iYScrollLength / maxY;

			pMouse->Mouse_TargetBringToTop();
			pMouse->Mouse_PreventEvent();
		}
	}
}
