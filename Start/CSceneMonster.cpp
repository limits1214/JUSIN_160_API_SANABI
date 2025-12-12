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


	CObjMonsterDummyFloater* pMobDummyFloater = new CObjMonsterDummyFloater;
	pMobDummyFloater->Initialize();
	pMobDummyFloater->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMobDummyFloater);

	CObjMonsterFloatingBomb* pFloatingBomb = new CObjMonsterFloatingBomb;
	pFloatingBomb->Initialize();
	pFloatingBomb->Set_Pos((WINCX >> 1) + 100, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBomb);

	CObjMonsterDummyRobot* pDummyRobot = new CObjMonsterDummyRobot;
	pDummyRobot->Initialize();
	pDummyRobot->Set_Pos((WINCX >> 1) + 200, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDummyRobot);


	//
	CObjMonsterDefender* pDefender = new CObjMonsterDefender;
	pDefender->Initialize();
	pDefender->Set_Pos((WINCX >> 1) + 300, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pDefender);

	CObjMonsterWarrior* pWarrior = new CObjMonsterWarrior;
	pWarrior->Initialize();
	pWarrior->Set_Pos((WINCX >> 1) + 400, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWarrior);


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
