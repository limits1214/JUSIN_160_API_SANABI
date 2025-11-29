#pragma once

#include "Define.h"

class CEditMgr
{
public:
	bool Get_ShowGrid() { return m_bShowGrid; }
	void Set_ShowGrid(bool bShowGrid) { m_bShowGrid = bShowGrid; }

	bool Get_EditTile() { return m_bEditTile; }
	void Set_EditTile(bool bEditTile) { m_bEditTile = bEditTile; m_eTile = TILE_ID_END; }

	bool Get_EditLine() { return m_bEditLine; }
	void Set_EditLine(bool bEditLine) { m_bEditLine = bEditLine; ZeroMemory(&m_ptLastLine, sizeof(POINT)); m_bFirstLine = true; m_eLine = LINE_ID_END; }

	bool Get_EditSprite() { return m_bEditSprite; }
	void Set_EditSprite(bool bEditSprite) { m_bEditSprite = bEditSprite; }

	void Set_FileName(FILE_NAME_ID eFileName) { m_eFileName = eFileName; }
	FILE_NAME_ID Get_FileName() { return m_eFileName; }

	void Set_Tile(TILE_ID eTile) { m_eTile = eTile; }
	TILE_ID Get_Tile() { return m_eTile; }

	void Set_MousePoint(POINT ptMouse) { m_ptMouse = ptMouse; }
	POINT Get_MousePoint() { return m_ptMouse; }

	void EditAreaTileMLKeyDown(POINT ptMouse);
	void EditAreaTileMRKeyDown(POINT ptMouse);

	void EditAreaLineMLKeyDown(POINT ptMouse);
	void EditAreaLineMRKeyDown(POINT ptMouse);

	void EditAreaSpriteMLKeyDown(POINT ptMouse);
	void EditAreaSpriteMRKeyDown(POINT ptMouse);

	void Set_MousePickingMode(EDIT_MOUSE_PICKING_MODE eMode) { m_eMousePickingMode = eMode; }
	EDIT_MOUSE_PICKING_MODE Get_MousePickingMode() { return m_eMousePickingMode; }

	void Set_Line(LINE_ID eLine) { m_eLine = eLine; };
	LINE_ID Get_Line() { return m_eLine; };

	void Save_File(FILE_NAME_ID eID);
	void Load_File(FILE_NAME_ID eID);
	

private:
	bool m_bShowGrid;
	bool m_bEditTile;
	bool m_bEditLine;
	bool m_bEditSprite;

	FILE_NAME_ID m_eFileName;
	TILE_ID m_eTile;

	POINT m_ptMouse;
	EDIT_MOUSE_PICKING_MODE m_eMousePickingMode;

	LINE_ID m_eLine;

	bool m_bFirstLine;
	POINT m_ptLastLine;

// SINGLETON
private:
	CEditMgr();
	CEditMgr& operator=(CEditMgr&) = delete;
	CEditMgr(const CEditMgr&) = delete;
	~CEditMgr();

public:
	static CEditMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CEditMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CEditMgr* m_pInstance;
};

