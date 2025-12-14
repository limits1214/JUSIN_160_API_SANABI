#include "pch.h"
#include "CObjMonsterMapBG.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

CObjMonsterMapBG::CObjMonsterMapBG()
	:m_bMoveFrame(false)
{
	//Set_DbgName(_T("CObjSprite"));
	//ZeroMemory(m_szFrameKey, sizeof(m_szFrameKey));
}

CObjMonsterMapBG::~CObjMonsterMapBG()
{
	Release();
}

void CObjMonsterMapBG::Initialize()
{
}

int CObjMonsterMapBG::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bMoveFrame)
		Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterMapBG::Late_Update()
{
}

void CObjMonsterMapBG::Render(HDC hDC)
{
	float		iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float		iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	iScrollX *= 1.f / 7.f;
	iScrollY *= 1.f / 7.f;
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));

	//GdiTransparentBlt(hDC,				// 복사 받을 DC
	//	m_tRect.left ,	// 복사 받을 공간의 LEFT	
	//	m_tRect.top ,				// 복사 받을 공간의 TOP
	//	(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
	//	(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	0,					// 복사할 이미지의 LEFT, TOP
	//	0,
	//	(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
	//	(INT)m_tInfo.fCY,
	//	RGB(255, 255, 255));	// 제거할 색상


	BmpRender(
		hDC,
		m_tRect.left + (int)iScrollX, m_tRect.top + (int)iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjMonsterMapBG::Release()
{
}
