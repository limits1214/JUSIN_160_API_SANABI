#include "pch.h"
#include "CObjRect.h"

CObjRect::CObjRect()
{
	Set_DbgName(_T("CObjRect"));
}

CObjRect::~CObjRect()
{
	Release();
}

void CObjRect::Initialize()
{
}

int CObjRect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjRect::Late_Update()
{
}

void CObjRect::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjRect::Release()
{
}
