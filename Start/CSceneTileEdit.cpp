#include "pch.h"
#include "CSceneTileEdit.h"
#include "CObjMgr.h"

CSceneTileEdit::CSceneTileEdit()
{
}

CSceneTileEdit::~CSceneTileEdit()
{
	Release();
}

void CSceneTileEdit::Initialize()
{
}

int CSceneTileEdit::Update()
{
	CObjMgr::Get_Instance()->Update();
	return OBJ_NOEVENT;
}

void CSceneTileEdit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneTileEdit::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneTileEdit::Release()
{
}
