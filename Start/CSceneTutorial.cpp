#include "pch.h"
#include "CSceneTutorial.h"
#include "CObjMgr.h"
#include "CObjPlayer.h"
#include "CBmpMgr.h"
#include "CObjLine.h"
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
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

    // IMG
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");

    // PLAYER
    CObjPlayer* pPlayer = new CObjPlayer;
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
    pPlayer->Initialize();
    pPlayer->Set_Pos(WINCX >> 1, WINCY >> 1);

    // LINE
    CObjLine* pLine1 = new CObjLine;
    CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine1);
    pLine1->Initialize();
    pLine1->Set_Line_Point({ 0,0 }, { 200, 200 });
    pLine1->Set_Pos(WINCX >> 1, (WINCY >> 1) + 60);
    pLine1->Set_Visible(false);


    //CObjGrp* pGrp1 = new CObjGrp;
    //CObjMgr::Get_Instance()->Add_Object(OBJ_GRP, pGrp1);
    //pGrp1->Initialize();
    //pGrp1->Set_Pos(WINCX >> 1, WINCY >> 1);

    //CObjSprite* pSprite1 = new CObjSprite;
    //CObjMgr::Get_Instance()->Add_Object(OBJ_SPRITE, pSprite1);
    //pSprite1->Set_FrameKey(_T("Monster"));
    //pSprite1->Initialize();
    //pSprite1->Set_CX(300);
    //pSprite1->Set_CY(300);
    //pSprite1->Set_Pos(110, 0 );
    //pSprite1->Set_Parent(pGrp1);

    //CObjSprite* pSprite2 = new CObjSprite;
    //pSprite2->Set_FrameKey(_T("Monster"));
    //pSprite2->Initialize();
    //pSprite2->Set_CX(300);
    //pSprite2->Set_CY(300);
    //pSprite2->Set_Pos(0, 110);
    //pSprite2->Set_Parent(pGrp1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_SPRITE, pSprite2);


    //CObjInputController* pInputController = new CObjInputController;
    //pInputController->Initialize();
    //pInputController->Set_Pos(0, 0);
    //pInputController->Set_Parent(pGrp1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_INPUTCONTROLLER, pInputController);

    //CObjLine* pLine2 = new CObjLine;
    //CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, pLine2);
    //pLine2->Initialize();
    //pLine2->Set_Line_Point({ 0,0 }, { 200, -200 });
    //pLine2->Set_Pos(WINCX >> 1, (WINCY >> 1) + 260);
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
    HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
    
    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    BitBlt(hDC,
        iScrollX,
        iScrollY,
        1920,			// 복사 받을 공간의 가로 
        1280,			// 복사 받을 공간의 세로 
        hGroundDC,				// 복사 할 DC
        0,					// 복사할 이미지의 LEFT, TOP
        0,
        SRCCOPY);			// 그대로 복사
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneTutorial::Release()
{
    CBmpMgr::Get_Instance()->Delete_Bmp(L"Ground");
}
