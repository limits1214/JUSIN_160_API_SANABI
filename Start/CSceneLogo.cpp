#include "pch.h"
#include "CSceneLogo.h"
#include "CBmpMgr.h"
#include "CKeyMgr2.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CObjGateSprite.h"
#include "CObjSprite.h"
#include "CSoundMgr.h"

CSceneLogo::CSceneLogo()
{
}

CSceneLogo::~CSceneLogo()
{
	Release();
}

void CSceneLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/LOGO.bmp", STR_FKI_LOGO);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BGBLACK.bmp", _T("BGBLACK"));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_LogoWithBG_KOR500.bmp", STR_FKI_SNB_LOGO_KOR);

	m_dwNextSceneTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	
	



	m_bStart = false;
}

int CSceneLogo::Update()
{
	if (m_bStart)
	{
		//CTimeMgr::Delay(&m_dwNextSceneTime, 1000, []() {

		//	CObjGateSprite* pGate = new CObjGateSprite;
		//	pGate->Initialize();
		//	CObjMgr::Get_Instance()->Add_Object(OBJ_GATE, pGate);

		//	CTimeMgr::Get_Instance()->Set_Timer([=]() {
		//		pGate->GateOpen();
		//		}, 1500);

		//	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		//	});
	}

	CObjMgr::Get_Instance()->Update();


	if (CKeyMgr2::Get_Instance()->Key_Down('P'))
	{
		m_bStart = true;
		//m_dwNextSceneTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

		//SFX_Epilogue_Logo.wav
		CSoundMgr::Get_Instance()->PlaySound(_T("SFX_Epilogue_Logo.wav"), SOUND_SFX_LOGO_INTRO, 1.f);

		CObjSprite* pLogo1Sprite = new CObjSprite;
		pLogo1Sprite->Initialize();
		pLogo1Sprite->Set_CX(45);
		pLogo1Sprite->Set_CY(55);
		pLogo1Sprite->Set_Pos(WINCX >> 1, WINCY >> 1);
		pLogo1Sprite->Set_FrameKeyId(FKI_LOGO);
		pLogo1Sprite->Set_MoveFrame(true);
		pLogo1Sprite->Set_Frame(FrameStateId_To_Frame(FSI_LOGO_NEOWIZ, CTimeMgr::Get_Instance()->Get_Tick_Count()));
		pLogo1Sprite->Do_UpdateRect();
		CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pLogo1Sprite);



		CObjSprite* pLogo2Sprite = new CObjSprite;
		pLogo2Sprite->Initialize();
		pLogo2Sprite->Set_CX(45);
		pLogo2Sprite->Set_CY(55);
		pLogo2Sprite->Set_Pos(WINCX >> 1, WINCY >> 1);
		pLogo2Sprite->Set_FrameKeyId(FKI_LOGO);
		pLogo2Sprite->Set_MoveFrame(true);
		pLogo2Sprite->Set_Frame(FrameStateId_To_Frame(FSI_LOGO_WONDERPOTION, CTimeMgr::Get_Instance()->Get_Tick_Count()));
		pLogo2Sprite->Do_UpdateRect();

		CObjSprite* pLogo3Sprite = new CObjSprite;
		pLogo3Sprite->Initialize();
		pLogo3Sprite->Set_CX(500);
		pLogo3Sprite->Set_CY(259);
		pLogo3Sprite->Set_Pos(WINCX >> 1, WINCY >> 1);
		pLogo3Sprite->Set_FrameKeyId(FKI_SNB_LOGO_KOR);
		//pLogo3Sprite->Set_MoveFrame(true);
		pLogo3Sprite->Set_Frame(FrameStateId_To_Frame(FSI_SNB_LOGO_KOR, CTimeMgr::Get_Instance()->Get_Tick_Count()));
		pLogo3Sprite->Do_UpdateRect();


		CTimeMgr::Get_Instance()->Set_Timer([=]() {
			pLogo1Sprite->Set_Dead();
			CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pLogo2Sprite);
			}, 2500);

		CTimeMgr::Get_Instance()->Set_Timer([=]() {
			pLogo2Sprite->Set_Dead();
			CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pLogo3Sprite);

			}, 5000);
		CObjGateSprite* pGate = new CObjGateSprite;
		pGate->Initialize();
		CTimeMgr::Get_Instance()->Set_Timer([=]() {
			//pLogo3Sprite->Set_Dead();



				
				CObjMgr::Get_Instance()->Add_Object(OBJ_GATE, pGate);

				CTimeMgr::Get_Instance()->Set_Timer([=]() {
					CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
					//CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING);
					pGate->GateOpen();
					}, 1500);

				

			}, 7500);
	}


	return OBJ_NOEVENT;
}

void CSceneLogo::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneLogo::Render(HDC hDC)
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

void CSceneLogo::Release()
{
	CBmpMgr::Get_Instance()->Delete_Bmp(_T("Logo"));
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE, OBJ_GATE });
}
