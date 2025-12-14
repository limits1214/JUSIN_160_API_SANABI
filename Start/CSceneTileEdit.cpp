#include "pch.h"
#include "CSceneTileEdit.h"
#include "CObjMgr.h"
#include "CUIObjRectButton.h"
#include "CUIObjText.h"
#include "CUIObjTileEditDbgPanel.h"
#include "CObjSprite.h"
#include "CBmpMgr.h"
#include "CObjEditArea.h"
#include "CKeyMgr2.h"
#include "CScrollMgr.h"

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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Prologue_Tileset.bmp", L"Spr_Prologue_Tileset");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60.bmp", STR_FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UnstableKnockbackPlatformA_Sheet.bmp", STR_FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/TUTOMAP.bmp", STR_FKI_TUTOMAP);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MonsterMap.bmp", STR_FKI_MONSTER_MAP);

	//int cx = 4800;
	//int cy = 3600;
	//CObjSprite* pTutoMap = new CObjSprite;
	//pTutoMap->Initialize();
	//pTutoMap->Set_Pos(cx >> 1, -(cy >> 1) + WINCY);
	//pTutoMap->Set_FrameKeyId(FKI_TUTOMAP);
	//pTutoMap->Set_CX(cx);
	//pTutoMap->Set_CY(cy);
	//pTutoMap->Set_UseMainScroll(true);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pTutoMap);

	int moncx = 5600;
	int moncy = 4200;
	CObjSprite* pMonMap = new CObjSprite;
	pMonMap->Initialize();
	pMonMap->Set_Pos(moncx >> 1, -(moncy >> 1) + WINCY);
	pMonMap->Set_FrameKeyId(FKI_MONSTER_MAP);
	pMonMap->Set_CX(moncx);
	pMonMap->Set_CY(moncy);
	pMonMap->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pMonMap);

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

	{
		// À§
		if (CKeyMgr2::Get_Instance()->Key_Pressing('I'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollY(TILECX);
		}

		// ¿Þ
		if (CKeyMgr2::Get_Instance()->Key_Pressing('J'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollX(TILECX);
		}

		// ¾Æ
		if (CKeyMgr2::Get_Instance()->Key_Pressing('K'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollY(-TILECX);
		}

		// ¿À
		if (CKeyMgr2::Get_Instance()->Key_Pressing('L'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollX(-TILECX);
		}
	}

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
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
