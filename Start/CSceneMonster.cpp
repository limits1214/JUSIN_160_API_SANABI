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


CSceneMonster::CSceneMonster()
{
}

CSceneMonster::~CSceneMonster()
{
    Release();
}

void CSceneMonster::Initialize()
{
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
	//CObjMonsterDummyFloater* pMobDummyFloater = new CObjMonsterDummyFloater;
	//pMobDummyFloater->Initialize();
	//pMobDummyFloater->Set_Pos(WINCX >> 1, WINCY >> 1);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater);

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
	pPlayer->Set_Pos((WINCX >> 1) - 200, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

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

}

int CSceneMonster::Update()
{
	CObjMgr::Get_Instance()->Update();
    return 0;
}

void CSceneMonster::Late_Update()
{
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER));

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
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
