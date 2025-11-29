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

CSceneTutorial::CSceneTutorial()
{
}

CSceneTutorial::~CSceneTutorial()
{
    Release();
}

void CSceneTutorial::Initialize()
{
    // TEST BG
   // CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

    // IMG
   // CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");

    //CObjGrp* pGrp = new CObjGrp;
    //pGrp->Initialize();
    //pGrp->Set_Pos(WINCX >> 1, WINCY >> 1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_GRP, pGrp);

    // PLAYER
    CObjPlayer* pPlayer = new CObjPlayer;
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
    pPlayer->Initialize();
    pPlayer->Set_Pos(WINCX >> 1, WINCY >> 1);
    //pPlayer->Set_Parent(pGrp);

    //CObjInputController* pInputController = new CObjInputController;
    //pInputController->Initialize();
    //pInputController->Set_Pos(0, 0);
    //pInputController->Set_Parent(pGrp);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pInputController);

  


    // LINE
    CObjCollisionLine* pLine1 = new CObjCollisionLine;
    pLine1->Initialize();
    pLine1->Set_Line_Point({ 0,0 }, { 200, 200 });
    pLine1->Set_Pos(WINCX >> 1, (WINCY >> 1) + 60);
    pLine1->Set_Option(LCT_CLIMABLE);
    CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine1);

    CObjCollisionLine* pLine2 = new CObjCollisionLine;
    pLine2->Initialize();
    pLine2->Set_Line_Point({ 0,0 }, { 200, 0 });
    pLine2->Set_Pos((WINCX >> 1) - 200, (WINCY >> 1) - 40);
    pLine2->Set_Option(LCT_CLIMABLE);
    CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine2);

    CObjCollisionLine* pLine3 = new CObjCollisionLine;
    pLine3->Initialize();
    pLine3->Set_Line_Point({ 0,0 }, { 200, 0 });
    pLine3->Set_Pos((WINCX >> 1) + 200, (WINCY >> 1) + 160);
    pLine3->Set_Option(LCT_CLIMABLE);
    CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine3);


    CObjCollisionLine* pLine4 = new CObjCollisionLine;
    pLine4->Initialize();
    pLine4->Set_Line_Point({ 0,0 }, { 0, 200 });
    pLine4->Set_Pos((WINCX >> 1) - 300, (WINCY >> 1) - 140);
    pLine4->Set_Option(LCT_CLIMABLE);
    CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine4);



    CObjCollisionLine* pLine5 = new CObjCollisionLine;
    pLine5->Initialize();
    pLine5->Set_Line_Point({ 0,0 }, { 0, 200 });
    pLine5->Set_Pos((WINCX >> 1) + 300, (WINCY >> 1) + 60);
    pLine5->Set_Option(LCT_NOCLIMABLE);
    CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine5);
    
}

int CSceneTutorial::Update()
{
    auto a = CObjMgr::Get_Instance();
    CObjMgr::Get_Instance()->Update();
    return OBJ_NOEVENT;
}

void CSceneTutorial::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    
    CCollisionMgr::Collision_Line(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_LINE));
}

void CSceneTutorial::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneTutorial::Release()
{
    //CBmpMgr::Get_Instance()->Delete_Bmp(L"Ground");
}
