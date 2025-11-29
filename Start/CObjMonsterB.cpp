#include "pch.h"
#include "CObjMonsterB.h"

CObjMonsterB::CObjMonsterB()
{
	Set_DbgName(_T("CObjMonsterB"));
}

CObjMonsterB::~CObjMonsterB()
{
	Release();
}

void CObjMonsterB::Initialize()
{
}

int CObjMonsterB::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterB::Late_Update()
{
}

void CObjMonsterB::Render(HDC hDC)
{
}

void CObjMonsterB::Release()
{
}
