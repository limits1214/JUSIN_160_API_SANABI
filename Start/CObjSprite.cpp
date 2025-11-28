#include "pch.h"
#include "CObjSprite.h"
#include "CBmpMgr.h"

CObjSprite::CObjSprite()
{
	Set_DbgName(_T("CObjSprite"));
	ZeroMemory(m_szFrameKey, sizeof(m_szFrameKey));
}

CObjSprite::~CObjSprite()
{
	Release();
}

void CObjSprite::Initialize()
{
}

int CObjSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjSprite::Late_Update()
{
}

void CObjSprite::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_szFrameKey);

	GdiTransparentBlt(hDC,				// 복사 받을 DC
		m_tRect.left ,	// 복사 받을 공간의 LEFT	
		m_tRect.top ,				// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
		hMemDC,				// 복사 할 DC
		0,					// 복사할 이미지의 LEFT, TOP
		0,
		(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거할 색상
}

void CObjSprite::Release()
{
}
