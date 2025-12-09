#include "pch.h"
#include "CSceneTutorial.h"
#include "CObjMgr.h"
#include "CObjPlayer.h"
#include "CBmpMgr.h"
#include "CObjCollisionLine.h"
#include "CCollisionMgr.h"
#include "CObjSprite.h"
#include "CObjGrp.h"
#include "CObjInputController.h"
#include "CScrollMgr.h"
#include "CEditMgr.h"
#include "CObjThings.h"
#include "CObjBg.h"
#include "CObjBgTutoCloud.h"
#include "CObjBgTutoMountain.h"

#include "CObjTutoAni.h"

CSceneTutorial::CSceneTutorial()
{
}

CSceneTutorial::~CSceneTutorial()
{
    Release();
}

void CSceneTutorial::Initialize()
{
	// Å¸ÀÏ
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Prologue_Tileset.bmp", L"Spr_Prologue_Tileset");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_NEW_Sheet.bmp", STR_FKI_Spr_SNB_SHEET_NEW);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_GRAB_SHEET.bmp", STR_FKI_Spr_SNB_GRAB_SHEET);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/TUTOMAP.bmp", STR_FKI_TUTOMAP);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/Spr_PRLG_Forest_BG_Cloud_sheet.bmp", STR_FKI_Spr_BG_TUTO_CLOUD);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/ForestMountain.bmp", STR_FKI_Spr_BG_TUTO_MOUNTAIN);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/Spr_PRLG_Forest_BG_Sky800600.bmp", STR_FKI_Spr_BG_TUTO_SKY);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/TUTO_ANI-sheet.bmp", STR_FKI_Spr_TUTO_ANI_SHEET);


	CObjBg* pBg = new CObjBg;
	pBg->Initialize();
	pBg->Set_FrameKeyId(FKI_Spr_BG_TUTO_SKY);
	pBg->Set_Pos(WINCX >> 1, WINCY >> 1);
	pBg->Set_CX(800);
	pBg->Set_CY(600);
	//pBg->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBg);

	CObjBgTutoMountain* pMountain = new CObjBgTutoMountain;
	pMountain->Initialize();
	pMountain->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pMountain);

	CObjBgTutoCloud* pCloud = new CObjBgTutoCloud;
	pCloud->Initialize();
	pCloud->Set_Pos(WINCX >> 1, WINCY >> 1);
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pCloud);
	


	int cx = 2400;
	int cy = 1800;
	CObjSprite* pTutoMap = new CObjSprite;
	pTutoMap->Initialize();
	pTutoMap->Set_Pos(cx >> 1, -(cy >> 1) + WINCY);
	pTutoMap->Set_FrameKeyId(FKI_TUTOMAP);
	pTutoMap->Set_CX(cx);
	pTutoMap->Set_CY(cy);
	pTutoMap->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTutoMap);


	CObjTutoAni* pTutoAni = new CObjTutoAni;
	pTutoAni->Set_Option(0);
	pTutoAni->Initialize();
	pTutoAni->Set_Pos(WINCX >> 1, WINCY >> 1);
	pTutoAni->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTutoAni);
	
	CEditMgr::Get_Instance()->Load_File(FNI_TUTORIAL, false, []() {
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_THINGS))
		{
			CObjThings* pTgs = dynamic_cast<CObjThings*>(pObj);
			if (pTgs != nullptr)
			{
				pTgs->ChangeReal();
			}
		}
		});
}

int CSceneTutorial::Update()
{
    CObjMgr::Get_Instance()->Update();
    return OBJ_NOEVENT;
}

void CSceneTutorial::Late_Update()
{
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));

    CObjMgr::Get_Instance()->Late_Update();

  }

void CSceneTutorial::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneTutorial::Release()
{
   
}
