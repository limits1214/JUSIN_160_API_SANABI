#include "pch.h"
#include "CSceneMenu.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjButton.h"
#include "CObjMgr.h"
#include "CEditMgr.h"
#include "CObjGameUiChapterBtn.h"
#include "CObjThings.h"
#include "CObjSprite.h"
CSceneMenu::CSceneMenu()
{
}

CSceneMenu::~CSceneMenu()
{
	Release();
}

void CSceneMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6.bmp", STR_FKI_UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UIBUTTON-Sheet.bmp", STR_FKI_UIBUTTON_SHEET);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UIBUTTONBG.bmp", STR_FKI_UIBUTTON_BG_SHEET);

	CObjSprite* pMenuBG = new CObjSprite;
	pMenuBG->Initialize();
	pMenuBG->Set_Pos(WINCX >> 1, WINCY >> 1);
	pMenuBG->Set_FrameKeyId(FKI_UIBUTTON_BG_SHEET);
	pMenuBG->Set_CX(800);
	pMenuBG->Set_CY(600);
	//pMenuBG->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pMenuBG);

	CEditMgr::Get_Instance()->Load_File(FNI_MENU, false, []() {
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

int CSceneMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CSceneMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneMenu::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneMenu::Release()
{
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE, OBJ_GATE });
}
