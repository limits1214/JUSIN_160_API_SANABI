#include "pch.h"
#include "CSceneBoss.h"
#include "CObjMgr.h"

CSceneBoss::CSceneBoss()
{
}

CSceneBoss::~CSceneBoss()
{
}

void CSceneBoss::Initialize()
{
}

int CSceneBoss::Update()
{
    CObjMgr::Get_Instance()->Update();
    return 0;
}

void CSceneBoss::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CSceneBoss::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneBoss::Release()
{
}
