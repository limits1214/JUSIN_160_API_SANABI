#include "pch.h"
#include "CSceneEnding.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"
#include "CObjSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CKeyMgr2.h"
#include "CObjGateSprite.h"
#include "CSceneMgr.h"
CSceneEnding::CSceneEnding()
{
}

CSceneEnding::~CSceneEnding()
{
	Release();
}

void CSceneEnding::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/EndingMari.bmp", STR_FKI_ENDING_MARI);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/EndingMariBG.bmp", STR_FKI_ENDING_MARI_BG);

	CObjSprite* pEndingMariBG = new CObjSprite;
	pEndingMariBG->Initialize();
	pEndingMariBG->Set_Pos(WINCX >> 1, WINCY >> 1);
	pEndingMariBG->Set_FrameKeyId(FKI_ENDING_MARI_BG);
	pEndingMariBG->Set_Frame(FrameStateId_To_Frame(FSI_ENDING_MARI_BG, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	pEndingMariBG->Set_CX(800);
	pEndingMariBG->Set_CY(600);
	pEndingMariBG->Set_UseMainScroll(false);
	pEndingMariBG->Set_MoveFrame(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pEndingMariBG);

	CObjSprite* pEndingMari = new CObjSprite;
	pEndingMari->Initialize();
	pEndingMari->Set_Pos((WINCX >> 1) - 200, WINCY >> 1);
	pEndingMari->Set_FrameKeyId(FKI_ENDING_MARI);
	pEndingMari->Set_Frame(FrameStateId_To_Frame(FSI_ENDING_MARI, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	pEndingMari->Set_CX(290);
	pEndingMari->Set_CY(400);
	pEndingMari->Set_UseMainScroll(false);
	pEndingMari->Set_MoveFrame(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pEndingMari);

	CSoundMgr::Get_Instance()->PlayBGM(_T("BGM_Event_MariTheme.wav"), 1.f);
}

int CSceneEnding::Update()
{
	CObjMgr::Get_Instance()->Update();


	if (CKeyMgr2::Get_Instance()->Key_Down('L'))
	{
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

void CSceneEnding::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneEnding::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BGBLACK");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneEnding::Release()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE, OBJ_GATE });
}
