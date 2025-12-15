#include "pch.h"
#include "CSceneMonster.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CEditMgr.h"
#include "CObjThings.h"
#include "CCollisionMgr.h"
#include "CObjMonsterDummyFloater.h"
#include "CObjMonsterFloatingBomb.h"
#include "CObjMonsterDummyRobot.h"
#include "CObjMonsterDefender.h"
#include "CObjMonsterWarrior.h"
#include "CObjMonsterTrooper.h"
#include "CObjMonsterSurveyDrone.h"
#include "CObjMonsterDaughter.h"
#include "CObjPlayer2.h"
#include "CObjSprite.h"
#include "CTimeMgr.h"
#include "CObjMonsterMapBG.h"
#include "CScrollMgr.h"
#include "CObjTrigger.h"
#include "CGameStorageMgr.h"
#include "CSceneMgr.h"
#include "CObjGateSprite.h"

CSceneMonster::CSceneMonster()
{
}

CSceneMonster::~CSceneMonster()
{
    Release();
}

void CSceneMonster::Initialize()
{
	m_dwSurveyDronIntervalTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_bRoom1Enter = false;
	m_bRoom2Enter = false;
	m_bRoom3Enter = false;

	m_bClearTriggerEnter = false;
	m_bMonsterClear = false;




	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_NEW_Sheet.bmp", STR_FKI_Spr_SNB_SHEET_NEW);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_GRAB_SHEET.bmp", STR_FKI_Spr_SNB_GRAB_SHEET);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_DummyFloater-Sheet.bmp", STR_FKI_Spr_MONSTER_DUMMYFLOATER_SHEET);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_DummyRobot-Sheet.bmp", STR_FKI_Spr_MONSTER_DUMMYROBOT_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_Defender-Sheet.bmp", STR_FKI_Spr_MONSTER_DEFENDER_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_WARRIOR-Sheet.bmp", STR_FKI_Spr_MONSTER_WARRIOR_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_Trooper-Sheet.bmp", STR_FKI_Spr_MONSTER_TROOPER_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE/ENE_SurveyorDrone-Sheet.bmp", STR_FKI_Spr_MONSTER_SURVEYDRONE_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DAUGHTER/DAUGHTER-Sheet.bmp", STR_FKI_Spr_MONSTER_DAUGHTER_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/VFX_EXPLOSION-Sheet.bmp", STR_FKI_Spr_EXPLOSION_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sprsht_Bullet-sheet.bmp", STR_FKI_Spr_MONSTER_BULLET_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BulletPLG.bmp", _T("BulletPLG"));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BulletRESET.bmp", _T("BulletRESET"));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Snb_Obj_Bullet_boom.bmp", STR_FKI_Spr_BULLET_BOOM_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DefenderBulletPLG.bmp", _T("DefenderBulletPLG"));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DefenderBulletRESET.bmp", _T("DefenderBulletRESET"));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ENE_DefenderBullet.bmp", STR_FKI_Spr_DEFENDER_BULLET_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MonsterMap.bmp", STR_FKI_MONSTER_MAP);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MonsterMapBgNeon.bmp", STR_FKI_MONSTER_MAP_BGNEON);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MonsterMapBoardGirl-Sheet.bmp", STR_FKI_MONSTER_MAP_BOARDSIGN);



	CObjMonsterDummyFloater* pMobDummyFloater1 = new CObjMonsterDummyFloater;
	pMobDummyFloater1->Initialize();
	pMobDummyFloater1->Set_Pos(4300, -(4200 - WINCY) + 1200);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater1);

	CObjMonsterDummyFloater* pMobDummyFloater2 = new CObjMonsterDummyFloater;
	pMobDummyFloater2->Initialize();
	pMobDummyFloater2->Set_Pos(4500, -(4200 - WINCY) + 1000);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater2);

	CObjMonsterDummyFloater* pMobDummyFloater3 = new CObjMonsterDummyFloater;
	pMobDummyFloater3->Initialize();
	pMobDummyFloater3->Set_Pos(4700, -(4200 - WINCY) + 800);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater3);

	//CObjMonsterFloatingBomb* pFloatingBomb = new CObjMonsterFloatingBomb;
	//pFloatingBomb->Initialize();
	//pFloatingBomb->Set_Pos((WINCX >> 1) + 100, WINCY >> 1);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBomb);

	//CObjMonsterDummyRobot* pDummyRobot = new CObjMonsterDummyRobot;
	//pDummyRobot->Initialize();
	//pDummyRobot->Set_Pos((WINCX >> 1) + 200, WINCY >> 1);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDummyRobot);


	//
	//CObjMonsterDefender* pDefender = new CObjMonsterDefender;
	//pDefender->Initialize();
	//pDefender->Set_Pos((WINCX >> 1) - 200, WINCY >> 1);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender);

	//CObjMonsterWarrior* pWarrior = new CObjMonsterWarrior;
	//pWarrior->Initialize();
	//pWarrior->Set_Pos((WINCX >> 1) + 400, WINCY >> 1);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior);

	//CObjMonsterTrooper* pTrooper = new CObjMonsterTrooper;
	//pTrooper->Initialize();
	//pTrooper->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + - 100);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper);

	//CObjMonsterSurveyDrone* pSurveyDrone = new CObjMonsterSurveyDrone;
	//pSurveyDrone->Initialize();
	//pSurveyDrone->Set_Pos((WINCX >> 1) + 100, (WINCY >> 1) + -100);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSurveyDrone);


	//CObjMonsterDaughter* pDaughter = new CObjMonsterDaughter;
	//pDaughter->Initialize();
	//pDaughter->Set_Pos((WINCX >> 1) -100, (WINCY >> 1) + 0);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDaughter);

	int bgcx = 1600;
	int bgcy = 1200;
	CObjMonsterMapBG* pMonBg = new CObjMonsterMapBG;
	pMonBg->Initialize();
	pMonBg->Set_Pos(bgcx >> 1, -(bgcy >> 1) + WINCY);
	pMonBg->Set_FrameKeyId(FKI_MONSTER_MAP_BGNEON);
	pMonBg->Set_Frame(FrameStateId_To_Frame(FSI_MONSTER_BG_NEON, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	pMonBg->Set_CX(bgcx);
	pMonBg->Set_CY(bgcy);
	pMonBg->Set_UseMainScroll(false);
	pMonBg->Set_MoveFrame(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pMonBg);


	// map image
	int cx = 5600;
	int cy = 4200;
	CObjSprite* pMonMap = new CObjSprite;
	pMonMap->Initialize();
	pMonMap->Set_Pos(cx >> 1, -(cy >> 1) + WINCY);
	pMonMap->Set_FrameKeyId(FKI_MONSTER_MAP);
	pMonMap->Set_CX(cx);
	pMonMap->Set_CY(cy);
	pMonMap->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pMonMap);

	// 4200 - 600
	// -(4200 - WINCY)
	CObjSprite* pBoardSignBoy = new CObjSprite;
	pBoardSignBoy->Initialize();
	pBoardSignBoy->Set_Pos(2360, -(4200 - WINCY) + 2586);
	pBoardSignBoy->Set_FrameKeyId(FKI_MONSTER_MAP_BOARDSIGN);
	pBoardSignBoy->Set_Frame(FrameStateId_To_Frame(FSI_MONSTER_BOARDSIGN_BOY, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	pBoardSignBoy->Set_CX(210);
	pBoardSignBoy->Set_CY(459);
	pBoardSignBoy->Set_UseMainScroll(true);
	pBoardSignBoy->Set_MoveFrame(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBoardSignBoy);

	
	CObjSprite* pBoardSignGirl = new CObjSprite;
	pBoardSignGirl->Initialize();
	pBoardSignGirl->Set_Pos(4000, -(4200 - WINCY) + 1000);
	pBoardSignGirl->Set_FrameKeyId(FKI_MONSTER_MAP_BOARDSIGN);
	pBoardSignGirl->Set_Frame(FrameStateId_To_Frame(FSI_MONSTER_BOARDSIGN_GIRL, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	pBoardSignGirl->Set_CX(210);
	pBoardSignGirl->Set_CY(459);
	pBoardSignGirl->Set_UseMainScroll(true);
	pBoardSignGirl->Set_MoveFrame(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBoardSignGirl);


	CObjPlayer2* pPlayer = new CObjPlayer2;
	pPlayer->Initialize();
	pPlayer->Set_Pos(320, -(4200 - WINCY) + 4000);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);


	CObjMonsterDummyRobot* pDummyRobot = new CObjMonsterDummyRobot;
	pDummyRobot->Initialize();
	pDummyRobot->Set_Pos(1776, -(4200 - WINCY) + 2850);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDummyRobot);


	CObjTrigger* pTrigger1 = new CObjTrigger;
	pTrigger1->Initialize();
	pTrigger1->Set_Target(pPlayer);
	pTrigger1->Set_Pos(2540, -(4200 - WINCY) + 2740);
	pTrigger1->Set_CX(300);
	pTrigger1->Set_CY(300);
	pTrigger1->Set_TriggerLoopCallback([=]() {
		if (!m_bRoom1Enter)
		{
			m_bRoom1Enter = true;

			CObjMonsterTrooper* pTrooper1 = new CObjMonsterTrooper;
			pTrooper1->Initialize();
			pTrooper1->Set_Target(pPlayer);
			pTrooper1->Set_Pos(2800, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper1);

			CObjMonsterTrooper* pTrooper2 = new CObjMonsterTrooper;
			pTrooper2->Initialize();
			pTrooper2->Set_Target(pPlayer);
			pTrooper2->Set_Pos(2950, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper2);

			CObjMonsterTrooper* pTrooper3 = new CObjMonsterTrooper;
			pTrooper3->Initialize();
			pTrooper3->Set_Target(pPlayer);
			pTrooper3->Set_Pos(3150, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper3);

			CObjMonsterTrooper* pTrooper4 = new CObjMonsterTrooper;
			pTrooper4->Initialize();
			pTrooper4->Set_Target(pPlayer);
			pTrooper4->Set_Pos(3300, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper4);

			CObjMonsterDefender* pDefender1 = new CObjMonsterDefender;
			pDefender1->Initialize();
			pDefender1->Set_Target(pPlayer);
			pDefender1->Set_Pos(3000, -(4200 - WINCY) + 2600);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender1);
		}
		});
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTrigger1);

	CObjTrigger* pTrigger2 = new CObjTrigger;
	pTrigger2->Initialize();
	pTrigger2->Set_Target(pPlayer);
	pTrigger2->Set_Pos(3660, -(4200 - WINCY) + 2740);
	pTrigger2->Set_CX(300);
	pTrigger2->Set_CY(300);
	pTrigger2->Set_TriggerLoopCallback([=]() {
		if (!m_bRoom2Enter)
		{
			m_bRoom2Enter = true;

			CObjMonsterDefender* pDefender1 = new CObjMonsterDefender;
			pDefender1->Initialize();
			pDefender1->Set_Target(pPlayer);
			pDefender1->Set_Pos(4180, -(4200 - WINCY) + 2600);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender1);

			CObjMonsterTrooper* pTrooper1 = new CObjMonsterTrooper;
			pTrooper1->Initialize();
			pTrooper1->Set_Target(pPlayer);
			pTrooper1->Set_Pos(4100, -(4200 - WINCY) + 2600);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper1);

			CObjMonsterTrooper* pTrooper2 = new CObjMonsterTrooper;
			pTrooper2->Initialize();
			pTrooper2->Set_Target(pPlayer);
			pTrooper2->Set_Pos(4260, -(4200 - WINCY) + 2600);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper2);






			CObjMonsterDefender* pDefender2 = new CObjMonsterDefender;
			pDefender2->Initialize();
			pDefender2->Set_Target(pPlayer);
			pDefender2->Set_Pos(3970, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender2);

			CObjMonsterTrooper* pTrooper3 = new CObjMonsterTrooper;
			pTrooper3->Initialize();
			pTrooper3->Set_Target(pPlayer);
			pTrooper3->Set_Pos(3890, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper3);

			CObjMonsterTrooper* pTrooper4 = new CObjMonsterTrooper;
			pTrooper4->Initialize();
			pTrooper4->Set_Target(pPlayer);
			pTrooper4->Set_Pos(4050, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper4);





			CObjMonsterDefender* pDefender3 = new CObjMonsterDefender;
			pDefender3->Initialize();
			pDefender3->Set_Target(pPlayer);
			pDefender3->Set_Pos(4350, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender3);

			CObjMonsterTrooper* pTrooper5 = new CObjMonsterTrooper;
			pTrooper5->Initialize();
			pTrooper5->Set_Target(pPlayer);
			pTrooper5->Set_Pos(4270, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper5);

			CObjMonsterTrooper* pTrooper6 = new CObjMonsterTrooper;
			pTrooper6->Initialize();
			pTrooper6->Set_Target(pPlayer);
			pTrooper6->Set_Pos(4430, -(4200 - WINCY) + 2950);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper6);
		}
		});
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTrigger2);


	CObjTrigger* pTrigger3 = new CObjTrigger;
	pTrigger3->Initialize();
	pTrigger3->Set_Target(pPlayer);
	pTrigger3->Set_Pos(4165, -(4200 - WINCY) + 2125);
	pTrigger3->Set_CX(300);
	pTrigger3->Set_CY(300);
	pTrigger3->Set_TriggerLoopCallback([=]() {
		if (!m_bRoom3Enter)
		{
			m_bRoom3Enter = true;

			
			CObjMonsterTrooper* pTrooper1 = new CObjMonsterTrooper;
			pTrooper1->Initialize();
			pTrooper1->Set_Target(pPlayer);
			pTrooper1->Set_Pos(4180, -(4200 - WINCY) + 1700);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper1);

			CObjMonsterTrooper* pTrooper2 = new CObjMonsterTrooper;
			pTrooper2->Initialize();
			pTrooper2->Set_Target(pPlayer);
			pTrooper2->Set_Pos(4100, -(4200 - WINCY) + 1700);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper2);

			CObjMonsterTrooper* pTrooper3 = new CObjMonsterTrooper;
			pTrooper3->Initialize();
			pTrooper3->Set_Target(pPlayer);
			pTrooper3->Set_Pos(4260, -(4200 - WINCY) + 1700);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper3);


			CObjMonsterWarrior* pWarrior1 = new CObjMonsterWarrior;
			pWarrior1->Initialize();
			pWarrior1->Set_Target(pPlayer);
			pWarrior1->Set_Pos(3900, -(4200 - WINCY) + 1700);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior1);

			CObjMonsterWarrior* pWarrior2 = new CObjMonsterWarrior;
			pWarrior2->Initialize();
			pWarrior2->Set_Target(pPlayer);
			pWarrior2->Set_Pos(3900, -(4200 - WINCY) + 1800);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior2);

			CObjMonsterWarrior* pWarrior3 = new CObjMonsterWarrior;
			pWarrior3->Initialize();
			pWarrior3->Set_Target(pPlayer);
			pWarrior3->Set_Pos(3900, -(4200 - WINCY) + 1900);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior3);

			CObjMonsterWarrior* pWarrior4 = new CObjMonsterWarrior;
			pWarrior4->Initialize();
			pWarrior4->Set_Target(pPlayer);
			pWarrior4->Set_Pos(4450, -(4200 - WINCY) + 1700);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior4);

			CObjMonsterWarrior* pWarrior5 = new CObjMonsterWarrior;
			pWarrior5->Initialize();
			pWarrior5->Set_Target(pPlayer);
			pWarrior5->Set_Pos(4450, -(4200 - WINCY) + 1800);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior5);

			CObjMonsterWarrior* pWarrior6 = new CObjMonsterWarrior;
			pWarrior6->Initialize();
			pWarrior6->Set_Target(pPlayer);
			pWarrior6->Set_Pos(4450, -(4200 - WINCY) + 1900);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior6);



			CObjMonsterDefender* pDefender1 = new CObjMonsterDefender;
			pDefender1->Initialize();
			pDefender1->Set_Target(pPlayer);
			pDefender1->Set_Pos(3820, -(4200 - WINCY) + 2000);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender1);

			//CObjMonsterDefender* pDefender2 = new CObjMonsterDefender;
			//pDefender2->Initialize();
			//pDefender2->Set_Target(pPlayer);
			//pDefender2->Set_Pos(3950, -(4200 - WINCY) + 2000);
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender2);

			//CObjMonsterDefender* pDefender3 = new CObjMonsterDefender;
			//pDefender3->Initialize();
			//pDefender3->Set_Target(pPlayer);
			//pDefender3->Set_Pos(4350, -(4200 - WINCY) + 2000);
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender3);

			CObjMonsterDefender* pDefender4 = new CObjMonsterDefender;
			pDefender4->Initialize();
			pDefender4->Set_Target(pPlayer);
			pDefender4->Set_Pos(4500, -(4200 - WINCY) + 2000);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender4);


		}
		});
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pTrigger3);


	CEditMgr::Get_Instance()->Load_File(FNI_MONSTER, false, []() {
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_THINGS))
		{
			CObjThings* pTgs = dynamic_cast<CObjThings*>(pObj);
			if (pTgs != nullptr)
			{
				pTgs->ChangeReal();
			}
		}
		});


	for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
	{
		CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
		if (pPlayer != nullptr)
		{
			for (auto*& pMonsterObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER))
			{
				pMonsterObj->Set_Target(pPlayer);
			}
		}
	}



	CObjTrigger* pMonsterClearTrigger = new CObjTrigger;
	pMonsterClearTrigger->Initialize();
	pMonsterClearTrigger->Set_Target(pPlayer);
	pMonsterClearTrigger->Set_Pos(5060, -(4200 - WINCY) + 600);
	//pMonsterClearTrigger->Set_Pos(600, -(4200 - WINCY) + 4000);
	pMonsterClearTrigger->Set_CX(100);
	pMonsterClearTrigger->Set_CY(100);
	pMonsterClearTrigger->Set_TriggerLoopCallback([=]() {
		if (!m_bClearTriggerEnter)
		{
			m_bClearTriggerEnter = true;

			m_bMonsterClear = true;
		}
		});
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pMonsterClearTrigger);


	CSoundMgr::Get_Instance()->PlayBGM(_T("BGM_Chap2_Main_Intro.wav"), 1.f);
}

int CSceneMonster::Update()
{
	CObjMgr::Get_Instance()->Update();


	CTimeMgr::Delay(&m_dwSurveyDronIntervalTime, 10000, []() {
		
		CObjPlayer2* pPlayer = nullptr;
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			auto player = dynamic_cast<CObjPlayer2*>(pObj);
			if (player != nullptr)
			{
				pPlayer = player;
				break;
			}
		}

		if (pPlayer != nullptr)
		{
			int droneCnt = 0;
			for (auto*& pMon : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER))
			{
				auto drone = dynamic_cast<CObjMonsterSurveyDrone*>(pMon);
				if (drone != nullptr)
				{
					++droneCnt;
				}
			}

			if (droneCnt < 3)
			{

				auto padX = (rand() % 200) - 100 ;
				auto padY = rand() % 100;
				CObjMonsterSurveyDrone* pSurveyDrone = new CObjMonsterSurveyDrone;
				pSurveyDrone->Initialize();
				pSurveyDrone->Set_Pos(pPlayer->Get_Info()->fX + padX, pPlayer->Get_Info()->fY - padY);
				pSurveyDrone->Set_Target(pPlayer);
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSurveyDrone);
			}
		}
		
		});


	if (m_bMonsterClear)
	{
		CGameStorageMgr::Get_Instance()->Set_Chap2Clear(true);


		dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateClose();

		CTimeMgr::Get_Instance()->Set_Timer([=]() {
			CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
			}, 1000);

		CTimeMgr::Get_Instance()->Set_Timer([=]() {
			dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateOpen();
			}, 1500);
	}
    return 0;
}

void CSceneMonster::Late_Update()
{
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_BULLET));
	
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));

	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_BULLET), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));


	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneMonster::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneMonster::Release()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE, OBJ_GATE });
	CScrollMgr::Get_Instance()->Scroll_Reset();
}
