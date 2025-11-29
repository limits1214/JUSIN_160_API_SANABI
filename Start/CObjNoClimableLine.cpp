#include "pch.h"
#include "CObjNoClimableLine.h"

CObjNoClimableLine::CObjNoClimableLine()
{
	Set_DbgName(_T("CObjNoClimableLine"));
}

CObjNoClimableLine::~CObjNoClimableLine()
{
	Release();
}

void CObjNoClimableLine::Initialize()
{
	CObjLine::Initialize();
}

int CObjNoClimableLine::Update()
{
	auto iResult = CObjLine::Update();
	if (iResult != OBJ_NOEVENT)
		return OBJ_DEAD;

	

	return OBJ_NOEVENT;
}

void CObjNoClimableLine::Late_Update()
{
	CObjLine::Late_Update();
}

void CObjNoClimableLine::Render(HDC hDC)
{
	CObjLine::Render(hDC);
}

void CObjNoClimableLine::Release()
{
	CObjLine::Release();
}
