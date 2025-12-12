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
#include "CSoundMgr.h"
#include "CObjTutoAni.h"

CSceneTutorial::CSceneTutorial()
	:m_pCloud1(nullptr), m_pCloud2(nullptr)
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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);


	CObjBg* pBg = new CObjBg;
	pBg->Initialize();
	pBg->Set_FrameKeyId(FKI_Spr_BG_TUTO_SKY);
	pBg->Set_Pos(WINCX >> 1, WINCY >> 1);
	pBg->Set_CX(800);
	pBg->Set_CY(600);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBg);

	//cw: 1426, cy:528
	CObjBgTutoMountain* pMountain = new CObjBgTutoMountain;
	pMountain->Initialize();
	pMountain->Set_Pos(WINCX >> 1, (WINCY >> 1) + 40);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pMountain);

	// cw: 1171, cy: 369
	CObjBgTutoCloud* pCloud1 = new CObjBgTutoCloud;
	pCloud1->Initialize();
	pCloud1->Set_Pos(1171 * 0.5f, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pCloud1);
	m_pCloud1 = pCloud1;

	CObjBgTutoCloud* pCloud2 = new CObjBgTutoCloud;
	pCloud2->Initialize();
	pCloud2->Set_Pos((1171 * 0.5f) - 1171, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pCloud2);
	m_pCloud2 = pCloud2;
	


	// map image
	int cx = 4800;
	int cy = 3600;
	CObjSprite* pTutoMap = new CObjSprite;
	pTutoMap->Initialize();
	pTutoMap->Set_Pos(cx >> 1, -(cy >> 1) + WINCY);
	pTutoMap->Set_FrameKeyId(FKI_TUTOMAP);
	pTutoMap->Set_CX(cx);
	pTutoMap->Set_CY(cy);
	pTutoMap->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTutoMap);


	CObjTutoAni* pTutoAni = new CObjTutoAni;
	pTutoAni->Set_Option(1);
	pTutoAni->Initialize();
	pTutoAni->Set_Pos(WINCX + 120, (WINCY >> 1) - 50);
	pTutoAni->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTutoAni);


	// 
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



	CSoundMgr::Get_Instance()->PlayBGM(_T("BGM_PRLG1_ForestDaughter01.wav"), 1.f);
}

int CSceneTutorial::Update()
{
    CObjMgr::Get_Instance()->Update();

	if (m_pCloud1 != nullptr && m_pCloud2 != nullptr)
	{
		m_pCloud1->Set_PosX(+0.05f);
		m_pCloud2->Set_PosX(+0.05f);

		auto cloud1Rect = m_pCloud1->Get_Rect();
		auto cloud2Rect = m_pCloud2->Get_Rect();

		if (cloud1Rect->left >= 1171)
		{
			m_pCloud1->Set_PosX(-(1171 + 1171));
			auto tmp = m_pCloud1;
			m_pCloud1 = m_pCloud2;
			m_pCloud2 = tmp;
		}
	}
	
    return OBJ_NOEVENT;
}

void CSceneTutorial::Late_Update()
{
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER));


    CObjMgr::Get_Instance()->Late_Update();

  }

void CSceneTutorial::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneTutorial::Release()
{
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
