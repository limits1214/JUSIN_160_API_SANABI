#include "pch.h"
#include "CObjMgr.h"
#include "CSceneStage.h"
#include "CAbstractFactory.h"
#include "CBmpMgr.h"

CSceneStage::CSceneStage()
{
}

CSceneStage::~CSceneStage()
{
	Release();
}

void CSceneStage::Initialize()
{
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
}

int CSceneStage::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	BitBlt(hDC,	
		0,
		0,
		1920,			// 복사 받을 공간의 가로 
		1280,			// 복사 받을 공간의 세로 
		hGroundDC,				// 복사 할 DC
		0,					// 복사할 이미지의 LEFT, TOP
		0,
		SRCCOPY);			// 그대로 복사
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneStage::Release()
{
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_DBG_UI });
	CBmpMgr::Get_Instance()->Delete_Bmp(L"Ground");
}
