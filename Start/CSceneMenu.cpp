#include "pch.h"
#include "CSceneMenu.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjButton.h"
#include "CObjMgr.h"
#include "CEditMgr.h"
#include "CObjGameUiChapterBtn.h"
#include "CObjThings.h"

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
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
