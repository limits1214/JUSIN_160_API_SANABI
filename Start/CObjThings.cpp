#include "pch.h"
#include "CObjThings.h"
#include "CEditMgr.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CObjMouse.h"
#include "CScrollMgr.h"

CObjThings::CObjThings()
{
	Set_DbgName(_T("CObjThings"));
}

CObjThings::~CObjThings()
{
	Release();
}

void CObjThings::Initialize()
{


	if (m_eThings == TGS_PLAYER_POS)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_MONSTER_A_POS)
	{
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_MONSTER_G_POS)
	{
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_MONSTER_B_POS)
	{
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_BOSS_FIREBIRD_POS)
	{
		m_tInfo.fCX = 300.f;
		m_tInfo.fCY = 300.f;
	}
	else
	{
		m_tInfo.fCX = TILECX * 4;
		m_tInfo.fCY = TILECY * 4;
	}

	


	CUIObjText* pText = new CUIObjText;
	pText->Initialize();
	pText->Set_Text(ThginsId_To_Text(m_eThings));
	pText->Set_Pos(0, 0);
	pText->Set_Parent(this);
	pText->Set_ApplyScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText);

}

int CObjThings::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjThings::Late_Update()
{
}

void CObjThings::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CObjThings::Release()
{
}

void CObjThings::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		if (PtInRect(&m_tRect, ptCurr))
		{
			if (pMouse->Get_Last_Key() == VK_LBUTTON)
			{
				m_bMouseTrack = true;
			}
			else if (pMouse->Get_Last_Key() == VK_RBUTTON)
			{
				Set_Dead_Cascade();
			}
			
			pMouse->Mouse_PreventEvent();
		}
	}
}

void CObjThings::On_Mouse_Key_Up(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		if (m_bMouseTrack)
		{
			m_bMouseTrack = false;
			pMouse->Mouse_PreventEvent();
		}
		
	}
}

void CObjThings::On_Mouse_Key_Pressing(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		POINT ptPrev = pMouse->Get_Pt_Prev();
		
		if (m_bMouseTrack)
		{
			EDIT_MOUSE_PICKING_MODE pickingMode = CEditMgr::Get_Instance()->Get_MousePickingMode();
			if (pickingMode == EMPM_TILE_ORIGIN)
			{
				int	x = ptCurr.x / TILECX;
				int	y = ptCurr.y / TILECY;

				x *= TILECX;
				y *= TILECY;
				POINT _ptCurr = POINT{ x, y };

				m_tInfo.fX = _ptCurr.x + (TILECX >> 1);
				m_tInfo.fY = _ptCurr.y + (TILECY >> 1);
			}
			else if (pickingMode == EMPM_TILE_SIDE)
			{
				int	x = ptCurr.x / TILECX;
				int	y = ptCurr.y / TILECY;

				x *= TILECX;
				y *= TILECY;
				POINT _ptCurr = POINT{ x, y };

				m_tInfo.fX = _ptCurr.x;
				m_tInfo.fY = _ptCurr.y;
			}
			else
			{
				long movedX = ptCurr.x - ptPrev.x;
				long movedY = ptCurr.y - ptPrev.y;

				m_tInfo.fX += movedX;
				m_tInfo.fY += movedY;
			}
			pMouse->Mouse_PreventEvent();
		}
		
	}
}

void CObjThings::ChangeReal()
{

	switch (m_eThings)
	{
	case TGS_PLAYER_POS:
		break;
	case TGS_MONSTER_A_POS:
		break;
	case TGS_MONSTER_B_POS:
		break;
	case TGS_MONSTER_G_POS:
		break;
	case TGS_BOSS_FIREBIRD_POS:
		break;
	}

	Set_Dead_Cascade();
}
