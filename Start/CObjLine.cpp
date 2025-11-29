#include "pch.h"
#include "CObjLine.h"
#include "CScrollMgr.h"
CObjLine::CObjLine()
{
}

CObjLine::~CObjLine()
{
	Release();
}

void CObjLine::Initialize()
{
}

int CObjLine::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Line();

	return OBJ_NOEVENT;
}

void CObjLine::Late_Update()
{
}

void CObjLine::Render(HDC hDC)
{


	float fIncline = Get_LineIncline();
	if (fIncline < 0)
	{
		MoveToEx(hDC, m_tRect.left , m_tRect.bottom , nullptr);
		LineTo(hDC, m_tRect.right , m_tRect.top );
	}
	else
	{
		MoveToEx(hDC, m_tRect.left , m_tRect.top , nullptr);
		LineTo(hDC, m_tRect.right , m_tRect.bottom);
	}
}

void CObjLine::Release()
{
}

void CObjLine::Update_Line()
{
	float fWidth = fabsf(m_tLine.tRight.fX - m_tLine.tLeft.fX);
	float fHeight = fabsf(m_tLine.tRight.fY - m_tLine.tLeft.fY);
	m_tInfo.fCX = fWidth;
	m_tInfo.fCY = fHeight;

	__super::Update_Rect();
}
