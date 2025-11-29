#include "pch.h"
#include "CObjCollisionLine.h"

CObjCollisionLine::CObjCollisionLine()
{
	Set_DbgName(_T("CObjClimableLine"));
}

CObjCollisionLine::~CObjCollisionLine()
{
	Release();
}

void CObjCollisionLine::Initialize()
{
	CObjLine::Initialize();
}

int CObjCollisionLine::Update()
{
	auto iResult = CObjLine::Update();
	if (iResult != OBJ_NOEVENT)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CObjCollisionLine::Late_Update()
{
	CObjLine::Late_Update();
}

void CObjCollisionLine::Render(HDC hDC)
{
	if (m_iOption == LCT_CLIMABLE)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		CObjLine::Render(hDC);

		HPEN hOldPen2 = (HPEN)SelectObject(hDC, hOldPen);
		DeleteObject(hOldPen2);
		DeleteObject(hNewPen);
	}
	else if (m_iOption == LCT_NOCLIMABLE)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		CObjLine::Render(hDC);

		HPEN hOldPen2 = (HPEN)SelectObject(hDC, hOldPen);
		DeleteObject(hOldPen2);
		DeleteObject(hNewPen);

		
	}
}

void CObjCollisionLine::Release()
{
	CObjLine::Release();
}
