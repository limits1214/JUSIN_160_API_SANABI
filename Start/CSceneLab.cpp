#include "pch.h"
#include "CSceneLab.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CObjEditArea.h"
#include "CUIObjText.h"
#include "CEditMgr.h"
#include "CObjThings.h"
#include "CBmpMgr.h"

#include "CObjMonsterDummyFloater.h"
#include "CObjMonsterFloatingBomb.h"
#include "CObjMonsterDummyRobot.h"
#include "CObjMonsterDefender.h"
#include "CObjMonsterWarrior.h"
#include "CObjMonsterTrooper.h"
#include "CObjMonsterSurveyDrone.h"
#include "CObjMonsterDaughter.h"
#include "CObjPlayer2.h"

CSceneLab::CSceneLab()
{
}

CSceneLab::~CSceneLab()
{
	Release();
}

void CSceneLab::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Prologue_Tileset.bmp", L"Spr_Prologue_Tileset");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UnstableKnockbackPlatformA_Sheet.bmp", STR_FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET);

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

	CObjEditArea* pEditArea = new CObjEditArea;
	pEditArea->Initialize();
	pEditArea->Set_CX(WINCX);
	pEditArea->Set_CY(WINCY);
	pEditArea->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_EDIT_AREA, pEditArea);








	CObjMonsterDummyFloater* pMobDummyFloater = new CObjMonsterDummyFloater;
	pMobDummyFloater->Initialize();
	pMobDummyFloater->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater);

	//CObjMonsterFloatingBomb* pFloatingBomb = new CObjMonsterFloatingBomb;
	//pFloatingBomb->Initialize();
	//pFloatingBomb->Set_Pos((WINCX >> 1) + 100, WINCY >> 1);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBomb);

	CObjMonsterDummyRobot* pDummyRobot = new CObjMonsterDummyRobot;
	pDummyRobot->Initialize();
	pDummyRobot->Set_Pos((WINCX >> 1) + 200, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDummyRobot);


	//
	CObjMonsterDefender* pDefender = new CObjMonsterDefender;
	pDefender->Initialize();
	pDefender->Set_Pos((WINCX >> 1) - 200, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender);

	CObjMonsterWarrior* pWarrior = new CObjMonsterWarrior;
	pWarrior->Initialize();
	pWarrior->Set_Pos((WINCX >> 1) + 400, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior);

	CObjMonsterTrooper* pTrooper = new CObjMonsterTrooper;
	pTrooper->Initialize();
	pTrooper->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + - 100);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pTrooper);

	//CObjMonsterSurveyDrone* pSurveyDrone = new CObjMonsterSurveyDrone;
	//pSurveyDrone->Initialize();
	//pSurveyDrone->Set_Pos((WINCX >> 1) + 100, (WINCY >> 1) + -100);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSurveyDrone);


	//CObjMonsterDaughter* pDaughter = new CObjMonsterDaughter;
	//pDaughter->Initialize();
	//pDaughter->Set_Pos((WINCX >> 1) -100, (WINCY >> 1) + 0);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDaughter);

	CEditMgr::Get_Instance()->Load_File(FNI_ETC, false, []() {
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

int CSceneLab::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneLab::Late_Update()
{
	// 플레이어가 렉트 충돌하면 플레이어에게 이벤트 호출
	
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLATFORM));
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_BULLET));
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
	CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_BULLET), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));


	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneLab::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneLab::Release()
{
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
