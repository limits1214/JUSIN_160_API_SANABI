#include "pch.h"
#include "CObjChain.h"

CObjChain::CObjChain()
{
}

CObjChain::~CObjChain()
{
	Release();
}

void CObjChain::Initialize()
{
}

int CObjChain::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// 입력받고 그릴지 아니면 그리고 입력받을지...
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjChain::Late_Update()
{
}

void CObjChain::Render(HDC hDC)
{
}

void CObjChain::Release()
{
}
