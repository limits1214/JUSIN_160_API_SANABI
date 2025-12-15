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
#include "CObjMonsterDaughter.h"
#include "CTimeMgr.h"
#include "CObjPlayer2.h"
#include "CObjTrigger.h"
#include "CSceneMgr.h"
#include "CGameStorageMgr.h"
#include "CObjMonsterDummyFloater.h"

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
	m_bTriggerEnter = false;
	m_bTutoClear = false;
	// Å¸ÀÏ
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Prologue_Tileset.bmp", L"Spr_Prologue_Tileset");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_NEW_Sheet.bmp", STR_FKI_Spr_SNB_SHEET_NEW);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_GRAB_SHEET.bmp", STR_FKI_Spr_SNB_GRAB_SHEET);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/TUTOMAP.bmp", STR_FKI_TUTOMAP);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/Spr_PRLG_Forest_BG_Cloud_sheet.bmp", STR_FKI_Spr_BG_TUTO_CLOUD);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/ForestMountain.bmp", STR_FKI_Spr_BG_TUTO_MOUNTAIN);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/Spr_PRLG_Forest_BG_Sky800600.bmp", STR_FKI_Spr_BG_TUTO_SKY);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TUTO/TUTO_ANI-sheet.bmp", STR_FKI_Spr_TUTO_ANI_SHEET);

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);*/

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DAUGHTER/Birthdayballon.bmp", STR_FKI_BIRTHDAYBALLON_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DAUGHTER/DAUGHTER-Sheet.bmp", STR_FKI_Spr_MONSTER_DAUGHTER_SHEET);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_DummyFloater-Sheet.bmp", STR_FKI_Spr_MONSTER_DUMMYFLOATER_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/VFX_EXPLOSION-Sheet.bmp", STR_FKI_Spr_EXPLOSION_SHEET);

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


	CObjSprite* pBirthBallon = new CObjSprite;
	pBirthBallon->Initialize();
	pBirthBallon->Set_Pos(350, -(3600 - WINCY) + 460);
	pBirthBallon->Set_FrameKeyId(FKI_BIRTHDAYBALLON_SHEET);
	pBirthBallon->Set_Frame(FrameStateId_To_Frame(FSI_BIRTHDAYBALLON, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	pBirthBallon->Set_CX(256);
	pBirthBallon->Set_CY(59);
	pBirthBallon->Set_UseMainScroll(true);
	pBirthBallon->Set_MoveFrame(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBirthBallon);

	CObjMonsterDummyFloater* pMobDummyFloater = new CObjMonsterDummyFloater;
	pMobDummyFloater->Initialize();
	pMobDummyFloater->Set_Pos(1250, -(3600 - WINCY) + 750);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater);


	CObjMonsterDaughter* pDaughter = new CObjMonsterDaughter;
	pDaughter->Initialize();
	pDaughter->Set_Pos(350, -(3600 - WINCY) + 475);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDaughter);


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


	CObjPlayer2* pPlayer = new CObjPlayer2;
	pPlayer->Initialize();
	pPlayer->Set_Pos(400, -(3600 - WINCY) + 3300);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

	CObjTrigger* pTutoClearTrigger = new CObjTrigger;
	pTutoClearTrigger->Initialize();
	pTutoClearTrigger->Set_Target(pPlayer);
	pTutoClearTrigger->Set_Pos(350, -(3600 - WINCY) + 475);
	//pTutoClearTrigger->Set_Pos(850, -(3600 - WINCY) + 3330);
	pTutoClearTrigger->Set_CX(100);
	pTutoClearTrigger->Set_CY(100);
	pTutoClearTrigger->Set_TriggerLoopCallback([=]() {
		if (!m_bTriggerEnter)
		{
			m_bTriggerEnter = true;

			m_bTutoClear = true;
		}
	});
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTutoClearTrigger);



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


	if (m_bTutoClear)
	{
		CGameStorageMgr::Get_Instance()->Set_Chap1Clear(true);
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
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
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
	CScrollMgr::Get_Instance()->Scroll_Reset();
}
