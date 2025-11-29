#include "pch.h"
#include "CObjBossFireBird.h"

CObjBossFireBird::CObjBossFireBird()
{
    Set_DbgName(_T("CObjThgins"));
}

CObjBossFireBird::~CObjBossFireBird()
{
    Release();
}

void CObjBossFireBird::Initialize()
{
}

int CObjBossFireBird::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CObjBossFireBird::Late_Update()
{
}

void CObjBossFireBird::Render(HDC hDC)
{
}

void CObjBossFireBird::Release()
{
}
