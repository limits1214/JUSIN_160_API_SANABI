#include "pch.h"
#include "CSceneLab.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CObjEditArea.h"
#include "CUIObjText.h"
#include "CEditMgr.h"
#include "CObjThings.h"
#include "CBmpMgr.h"

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

	//for (int i = 0; i < 20; ++i)
	//{
	//	for (int j = 0; j < 20; ++j)
	//	{
	//		CUIObjText* p = new CUIObjText();
	//		p->Initialize();
	//		p->Set_Text(L"1");
	//		p->Set_Pos(200 + i * 10,  200 +j * 10);
	//		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, p);
	//	}
	//}

	CObjEditArea* pEditArea = new CObjEditArea;
	pEditArea->Initialize();
	pEditArea->Set_CX(WINCX);
	pEditArea->Set_CY(WINCY);
	pEditArea->Set_Pos(WINCX >> 1, WINCY >> 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_EDIT_AREA, pEditArea);

	CEditMgr::Get_Instance()->Load_File(FNI_LAB1_LINECOLL, false, []() {
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

int CSceneLab::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneLab::Late_Update()
{
	// 플레이어가 렉트 충돌하면 플레이어에게 이벤트 호출
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
	//CCollisionMgr::Collision_Line(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_LINE));
	//CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER));

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
