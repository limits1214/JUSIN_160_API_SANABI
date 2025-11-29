#include "pch.h"
#include "CEditMgr.h"
#include "CObjTile.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CObjClimableLine.h"
#include "CObjNoClimableLine.h"

CEditMgr* CEditMgr::m_pInstance = nullptr;


CEditMgr::CEditMgr()
	:m_bShowGrid(false),
	m_bEditLine(false),
	m_bEditSprite(false),
	m_bEditTile(false),
	m_eTile(TILE_ID_END),
	m_eFileName(FNI_END),
	m_eMousePickingMode(EMPM_END),
	m_bFirstLine(true),
	m_eLine(LINE_ID_END)
{
	ZeroMemory(&m_ptLastLine, sizeof(POINT));
}

CEditMgr::~CEditMgr()
{
}


void CEditMgr::EditAreaLineMLKeyDown(POINT ptMouse)
{
	if (m_eLine == LINE_ID_END || m_eLine == LINE_START)
	{
		return;
	}

	if (m_bFirstLine)
	{
		m_bFirstLine = false;
		m_ptLastLine = ptMouse;
	}
	else
	{
		LONG lWidth = ptMouse.x - m_ptLastLine.x;
		LONG lHeight = ptMouse.y - m_ptLastLine.y;
		LINEPOINT lpLeft = { (float)m_ptLastLine.x , (float)m_ptLastLine.y};
		LINEPOINT lpRight = { (float)ptMouse.x , (float)ptMouse.y };


		float posx = m_ptLastLine.x + lWidth * 0.5f;
		float posy = m_ptLastLine.y + lHeight * 0.5f;
		if (m_eLine == LINE_CLIMABLE)
		{
			CObjClimableLine* line = new CObjClimableLine;
			line->Initialize();
			line->Set_Pos(posx, posy);
			line->Set_Line_Point( lpLeft, lpRight);
			CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, line);
		}
		else if (m_eLine == LINE_NO_CLIMABLE)
		{
			CObjNoClimableLine* line = new CObjNoClimableLine;
			line->Initialize();
			line->Set_Pos(posx, posy);
			line->Set_Line_Point(lpLeft, lpRight);
			CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, line);
		}
		m_ptLastLine = ptMouse;
	}
}

void CEditMgr::EditAreaLineMRKeyDown(POINT ptMouse)
{
	if (m_eLine == LINE_ID_END || m_eLine == LINE_START || m_eLine == LINE_END)
	{
		return;
	}
}

void CEditMgr::EditAreaSpriteMLKeyDown(POINT ptMouse)
{
}

void CEditMgr::EditAreaSpriteMRKeyDown(POINT ptMouse)
{
}
void CEditMgr::EditAreaTileMRKeyDown(POINT ptMouse)
{
	if (m_eTile == TILE_ID_END || m_eTile == TILE_START)
	{
		return;
	}


	int x = ptMouse.x;
	int y = ptMouse.y;
	for (auto& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_TILE))
	{
		int fx = pObj->Get_Info()->fX / TILECX;
		int fy = pObj->Get_Info()->fY / TILECY;
		fx *= TILECX;
		fy *= TILECY;
		if (fx == x && fy == y)
		{
			pObj->Set_Dead();
		}
	}

}
void CEditMgr::EditAreaTileMLKeyDown(POINT ptMouse)
{
	if (m_eTile == TILE_ID_END || m_eTile == TILE_START || m_eTile == TILE_END)
	{
		return;
	}
	
	int x = ptMouse.x;
	int y = ptMouse.y;
	for (auto& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_TILE))
	{
		int fx = pObj->Get_Info()->fX / TILECX;
		int fy = pObj->Get_Info()->fY / TILECY;
		fx *= TILECX;
		fy *= TILECY;
		if (fx == x && fy == y)
		{
			pObj->Set_Dead();
		}
	}



	INFO tileInfo = Tile_Id_To_TileInfo(m_eTile);
	FRAME frame = FRAME{ int(tileInfo.fX / tileInfo.fCX),int(tileInfo.fX / tileInfo.fCX), int(tileInfo.fY / tileInfo.fCY), 0, 0 };

	CObjTile* pTile = new CObjTile;
	pTile->Initialize();
	pTile->Set_Pos(x, y);

	TCHAR szFrameKey[256];
	Tile_Id_To_FrameKey(m_eTile, szFrameKey);
	pTile->Set_FrameKey(szFrameKey);
	pTile->Set_Frame(frame);

	CObjMgr::Get_Instance()->Add_Object(OBJ_TILE, pTile);

	
}
