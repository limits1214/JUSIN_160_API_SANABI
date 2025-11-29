#include "pch.h"
#include "CObjClimableLine.h"

CObjClimableLine::CObjClimableLine()
{
	Set_DbgName(_T("CObjClimableLine"));
}

CObjClimableLine::~CObjClimableLine()
{
	Release();
}

void CObjClimableLine::Initialize()
{
	CObjLine::Initialize();
}

int CObjClimableLine::Update()
{
	auto iResult = CObjLine::Update();
	if (iResult != OBJ_NOEVENT)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CObjClimableLine::Late_Update()
{
	CObjLine::Late_Update();
}

void CObjClimableLine::Render(HDC hDC)
{
	CObjLine::Render(hDC);
}

void CObjClimableLine::Release()
{
	CObjLine::Release();
}
