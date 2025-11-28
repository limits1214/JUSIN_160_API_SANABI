#include "pch.h"
#include "CObjGrp.h"

CObjGrp::CObjGrp()
{
	Set_DbgName(_T("CObjGrp"));
}

CObjGrp::~CObjGrp()
{
	Release();
}

void CObjGrp::Initialize()
{
}

int CObjGrp::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	return OBJ_NOEVENT;
}

void CObjGrp::Late_Update()
{
}

void CObjGrp::Render(HDC hDC)
{
}

void CObjGrp::Release()
{
}
