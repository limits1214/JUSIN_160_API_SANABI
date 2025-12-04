#include "pch.h"
#include "CObjCollisionRect.h"

CObjCollisionRect::CObjCollisionRect()
{
	Set_DbgName(_T("CObjCollisionRect"));
}

CObjCollisionRect::~CObjCollisionRect()
{
	Release();
}

void CObjCollisionRect::Initialize()
{
	CObjRect::Initialize();

	m_bUseMainScroll = true;
}

int CObjCollisionRect::Update()
{
	auto iResult = CObjRect::Update();
	if (iResult != OBJ_NOEVENT)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CObjCollisionRect::Late_Update()
{
	CObjRect::Late_Update();
}

void CObjCollisionRect::Render(HDC hDC)
{
	if (m_iOption == ERI_CLIMABLE)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		CObjRect::Render(hDC);

		HPEN hOldPen2 = (HPEN)SelectObject(hDC, hOldPen);
		DeleteObject(hOldPen2);
		DeleteObject(hNewPen);
	}
	else if (m_iOption == ERI_NO_CLIMABLE)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		CObjRect::Render(hDC);

		HPEN hOldPen2 = (HPEN)SelectObject(hDC, hOldPen);
		DeleteObject(hOldPen2);
		DeleteObject(hNewPen);


	}
	else if (m_iOption == ERI_DAMAGE)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);

		CObjRect::Render(hDC);

		HPEN hOldPen2 = (HPEN)SelectObject(hDC, hOldPen);
		DeleteObject(hOldPen2);
		DeleteObject(hNewPen);
	}
}

void CObjCollisionRect::Release()
{
	CObjRect::Release();
}
