#include "pch.h"
#include "CSceneTileEdit.h"
#include "CObjMgr.h"
#include "CUIObjRectButton.h"
#include "CUIObjText.h"
#include "CUIObjTileEditDbgPanel.h"
#include "CObjSprite.h"
#include "CBmpMgr.h"
#include "CObjEditArea.h"

CSceneTileEdit::CSceneTileEdit()
{
}

CSceneTileEdit::~CSceneTileEdit()
{
	Release();
}

void CSceneTileEdit::Initialize()
{
	


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"TILE_TEST");

	CUIObjRectButton* pPanelOpenBtn = new CUIObjRectButton;
	pPanelOpenBtn->Initialize();
	pPanelOpenBtn->Set_CX(100);
	pPanelOpenBtn->Set_CY(20);
	pPanelOpenBtn->Set_Pos(50, 10);
	pPanelOpenBtn->Set_OnKeyDown([=]() {
		CUIObjTileEditDbgPanel* tileEditDbgPandel = new CUIObjTileEditDbgPanel;
		tileEditDbgPandel->Initialize();
		tileEditDbgPandel->Set_CX(WINCX >> 2);
		tileEditDbgPandel->Set_CY(WINCY >> 2);
		tileEditDbgPandel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
		tileEditDbgPandel->Set_Header_Text(_T("TILE_EDIT_PANEL"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, tileEditDbgPandel);

		});
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pPanelOpenBtn);

	CUIObjText* pPanelOpenBtnText = new CUIObjText;
	pPanelOpenBtnText->Initialize();
	pPanelOpenBtnText->Set_CX(100);
	pPanelOpenBtnText->Set_CY(20);
	pPanelOpenBtnText->Set_Pos(0, 0);
	pPanelOpenBtnText->Set_Parent(pPanelOpenBtn);
	pPanelOpenBtnText->Set_Text(_T("OPEN"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pPanelOpenBtnText);

	//CObjSprite* pSprite = new CObjSprite;
	//pSprite->Initialize();
	//pSprite->Set_CX(128);
	//pSprite->Set_CY(64);
	//pSprite->Set_Pos(WINCX >> 1, WINCY >> 1);
	//pSprite->Set_FrameKey(_T("TEST_TILE"));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pSprite);


	CObjEditArea* pEditArea = new CObjEditArea;
	pEditArea->Initialize();
	pEditArea->Set_CX(WINCX);
	pEditArea->Set_CY(WINCY);
	pEditArea->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_EDIT_AREA, pEditArea);

}

int CSceneTileEdit::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneTileEdit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneTileEdit::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneTileEdit::Release()
{
	CObjMgr::Get_Instance()->Dead_ID(OBJ_EDIT_AREA);
}
