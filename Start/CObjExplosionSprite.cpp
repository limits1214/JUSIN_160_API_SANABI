#include "pch.h"
#include "CObjExplosionSprite.h"

#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjExplosionSprite::CObjExplosionSprite()
{
}

CObjExplosionSprite::~CObjExplosionSprite()
{
}

void CObjExplosionSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 166;
	m_tInfo.fCY = 189;


	m_eFrameKey = FKI_Spr_EXPLOSION_SHEET;
	//m_eCurState = FSI_EXPLOSION_SMALL;
	//m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
	//m_iOption = 0;
	if (m_iOption == 0)
	{
		m_eCurState = FSI_EXPLOSION_SMALL;
		m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
	}
	else if (m_iOption == 1)
	{
		m_eCurState = FSI_EXPLOSION_BIG;
		m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
	}

}

int CObjExplosionSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	
	Move_Frame();

	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
	if (m_tFrame.iStart == end)
	{
		Set_Dead_Cascade();
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjExplosionSprite::Late_Update()
{
	Motion_Change();
}

void CObjExplosionSprite::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjExplosionSprite::Release()
{
}

void CObjExplosionSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
