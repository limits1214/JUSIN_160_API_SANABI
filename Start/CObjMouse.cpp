#include "pch.h"
#include "CObjMouse.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CMouseEvent.h"

CObjMouse::CObjMouse()
	:m_bTargetBringToTop(false), m_bPreventEvent(false), m_pBringToTopObj(nullptr)
{
	Set_DbgName(_T("Mouse"));
	Set_RDO(RDO_9);
}

CObjMouse::~CObjMouse()
{
	Release();
}

void CObjMouse::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
}

int CObjMouse::Update()
{
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	m_ptPrev = m_ptCurr;
	m_ptCurr = pt;

	m_sLastKey = 0;
	PropagateMouseEvent<CMousePosEvent>([=](CMousePosEvent* pMouse) {pMouse->On_Mouse_Pos(this); });
	
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		m_sLastKey = VK_LBUTTON;
		PropagateMouseEvent<CMouseKeyEvent>([=](CMouseKeyEvent* pMouse) {pMouse->On_Mouse_Key_Down(this); });
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		m_sLastKey = VK_RBUTTON;
		PropagateMouseEvent<CMouseKeyEvent>([=](CMouseKeyEvent* pMouse) {pMouse->On_Mouse_Key_Down(this); });
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_sLastKey = VK_LBUTTON;
		PropagateMouseEvent<CMouseKeyEvent>([=](CMouseKeyEvent* pMouse) {pMouse->On_Mouse_Key_Pressing(this); });
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	{
		m_sLastKey = VK_RBUTTON;
		PropagateMouseEvent<CMouseKeyEvent>([=](CMouseKeyEvent* pMouse) {pMouse->On_Mouse_Key_Pressing(this); });
	}


	if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
	{
		m_sLastKey = VK_LBUTTON;
		PropagateMouseEvent<CMouseKeyEvent>([=](CMouseKeyEvent* pMouse) {pMouse->On_Mouse_Key_Up(this); });
	}
	else if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
	{
		m_sLastKey = VK_RBUTTON;
		PropagateMouseEvent<CMouseKeyEvent>([=](CMouseKeyEvent* pMouse) {pMouse->On_Mouse_Key_Up(this); });
	}

	__super::Update_Rect();

	m_sLastKey = 0;
	return OBJ_NOEVENT;
}

void CObjMouse::Late_Update()
{

}

void CObjMouse::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMouse::Release()
{
}

TCHAR* CObjMouse::Dbg_Text()
{
	TCHAR szText[256];

	const INFO* info = this->Get_Info();

	swprintf_s(szText, _T("INFO\nfX: %f\nfY: %f\nfCX: %f\nfCY: %f\n\n"), info->fX, info->fY, info->fCX, info->fCY);

	TCHAR* pText = new TCHAR[lstrlen(szText) + 1];
	lstrcpy(pText, szText);

	return pText;
}


template<typename T, typename F>
void CObjMouse::PropagateMouseEvent(F func)
{
	m_bPreventEvent = false;
	m_bTargetBringToTop = false;
	bool bFirstActive = true;


	list<CObj*> renderOrderList[RDO_END];
	CObjMgr::Get_Instance()->Make_Render_Order(renderOrderList);

	for (int i = (RDO_END - 1); i >= 0; --i)
	{
		for (auto riter = renderOrderList[i].rbegin(); riter != renderOrderList[i].rend(); ++riter)
		{
			auto* pObj = (*riter);
			if (!pObj->Get_Active())
			{
				continue;
			}
			auto pMouse = dynamic_cast<T*>(pObj);
			if (pMouse != nullptr)
			{
				func(pMouse);

				if (m_bTargetBringToTop && bFirstActive)
				{
					if (m_pBringToTopObj != nullptr)
					{
						if (CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pBringToTopObj) != OBJ_END)
						{
							m_pBringToTopObj->Set_RDOTempRestore();
						}
						else
						{
							m_pBringToTopObj = nullptr;
						}
					}
					m_pBringToTopObj = pObj;
					m_pBringToTopObj->Set_RDOTempChange(RDO_8);
					
					bFirstActive = false;
				}

				if (m_bPreventEvent)
				{
					break;
				}
			}
			if (m_bPreventEvent)
			{
				break;
			}
		}
	}
}
