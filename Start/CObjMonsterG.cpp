#include "pch.h"
#include "CObjMonsterG.h"

CObjMonsterG::CObjMonsterG()
{
    Set_DbgName(_T("CObjMonsterG"));
}

CObjMonsterG::~CObjMonsterG()
{
    Release();
}

void CObjMonsterG::Initialize()
{
}

int CObjMonsterG::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterG::Late_Update()
{
}

void CObjMonsterG::Render(HDC hDC)
{
}

void CObjMonsterG::Release()
{
}
