#include "pch.h"
#include "CObjEditArea.h"
#include "CObjMouse.h"
#include "CEditMgr.h"

CObjEditArea::CObjEditArea()
{
	Set_DbgName(_T("CObjEditArea"));
}

CObjEditArea::~CObjEditArea()
{
	Release();
}

void CObjEditArea::Initialize()
{
}

int CObjEditArea::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjEditArea::Late_Update()
{
}

void CObjEditArea::Render(HDC hDC)
{
	int iXCnt = WINCX / TILECX;
	int iYCnt = WINCY / TILECY;

	if (CEditMgr::Get_Instance()->Get_ShowGrid())
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(80, 80, 80));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		for (int j = 0; j < iXCnt; ++j)
		{
			MoveToEx(hDC, TILECX * j, 0, nullptr);
			LineTo(hDC, TILECX * j, WINCY);
		}

		for (int i = 0; i < iYCnt; ++i)
		{
			MoveToEx(hDC, 0, TILECY * i, nullptr);
			LineTo(hDC, WINCX, TILECY * i);
		}

		HPEN hOldPen2 = (HPEN)SelectObject(hDC, hOldPen);
		DeleteObject(hOldPen2);
		DeleteObject(hNewPen);
	}

	//현재 마우스표시용
	EDIT_MOUSE_PICKING_MODE pickingMode = CEditMgr::Get_Instance()->Get_MousePickingMode();
	if (pickingMode == EMPM_TILE_ORIGIN)
	{
		POINT ptMouse = CEditMgr::Get_Instance()->Get_MousePoint();
		MoveToEx(hDC, ptMouse.x , ptMouse.y , nullptr);
		LineTo(hDC, ptMouse.x  + 16, ptMouse.y  + 16);

		MoveToEx(hDC, ptMouse.x + 16, ptMouse.y, nullptr);
		LineTo(hDC, ptMouse.x, ptMouse.y + 16);
	}
	else if (pickingMode == EMPM_TILE_SIDE)
	{
		POINT ptMouse = CEditMgr::Get_Instance()->Get_MousePoint();
		MoveToEx(hDC, ptMouse.x  - 8, ptMouse.y  - 8, nullptr);
		LineTo(hDC, ptMouse.x  + 8, ptMouse.y + 8);

		MoveToEx(hDC, ptMouse.x + 8, ptMouse.y - 8, nullptr);
		LineTo(hDC, ptMouse.x - 8, ptMouse.y + 8);
	}
	else
	{

	}
	
}

void CObjEditArea::Release()
{
}

void CObjEditArea::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		if (PtInRect(&m_tRect, ptCurr))
		{
			int	x = ptCurr.x / TILECX;
			int	y = ptCurr.y / TILECY;

			x *= TILECX;
			y *= TILECY;
			if (CEditMgr::Get_Instance()->Get_EditTile())
			{
				if (pMouse->Get_Last_Key() & VK_LBUTTON)
				{
					CEditMgr::Get_Instance()->EditAreaTileMLKeyDown({ x, y });
				}
				else if (pMouse->Get_Last_Key() & VK_RBUTTON)
				{
					CEditMgr::Get_Instance()->EditAreaTileMRKeyDown({ x, y });
				}
			}
			
			if (CEditMgr::Get_Instance()->Get_EditLine())
			{
				if (pMouse->Get_Last_Key() & VK_LBUTTON)
				{
					CEditMgr::Get_Instance()->EditAreaLineMLKeyDown({ x, y });
				}
				else if (pMouse->Get_Last_Key() & VK_RBUTTON)
				{
					CEditMgr::Get_Instance()->EditAreaLineMRKeyDown({ x, y });
				}
			}

			if (CEditMgr::Get_Instance()->Get_EditRect())
			{
				if (pMouse->Get_Last_Key() & VK_LBUTTON)
				{
					CEditMgr::Get_Instance()->EditAreaRectMLKeyDown({ x, y });
				}
				else if (pMouse->Get_Last_Key() & VK_RBUTTON)
				{
					CEditMgr::Get_Instance()->EditAreaRectMRKeyDown({ x, y });
				}
			}
			
		}
	}
}

void CObjEditArea::On_Mouse_Key_Up(CObj* pMouse)
{
}

void CObjEditArea::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CObjEditArea::On_Mouse_Pos(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		if (PtInRect(&m_tRect, ptCurr))
		{
			int	x = ptCurr.x / TILECX;
			int	y = ptCurr.y / TILECY;

			x *= TILECX;
			y *= TILECY;
			CEditMgr::Get_Instance()->Set_MousePoint({ x, y });
		}
		else
		{
			
		}
	}
}
