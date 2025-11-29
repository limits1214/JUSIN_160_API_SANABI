#include "pch.h"
#include "CObjMonsterA.h"

CObjMonsterA::CObjMonsterA()
{
    Set_DbgName(_T("CObjMonsterA"));
}

CObjMonsterA::~CObjMonsterA()
{
    Release();
}

void CObjMonsterA::Initialize()
{
}

int CObjMonsterA::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    __super::Update_Rect();
    return OBJ_DEAD;
}

void CObjMonsterA::Late_Update()
{
}

void CObjMonsterA::Render(HDC hDC)
{
}

void CObjMonsterA::Release()
{
}
