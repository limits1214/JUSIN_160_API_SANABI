#include "pch.h"
#include "CObjMonsterBulletBoomSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjMonsterBulletBoomSprite::CObjMonsterBulletBoomSprite()
{
}

CObjMonsterBulletBoomSprite::~CObjMonsterBulletBoomSprite()
{
}

void CObjMonsterBulletBoomSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 42;
	m_tInfo.fCY = 26;


	m_eFrameKey = FKI_Spr_BULLET_BOOM_SHEET;
	m_eCurState = FSI_Spr_BULLET_BOOM;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());

}

int CObjMonsterBulletBoomSprite::Update()
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

void CObjMonsterBulletBoomSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterBulletBoomSprite::Render(HDC hDC)
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

void CObjMonsterBulletBoomSprite::Release()
{
}

void CObjMonsterBulletBoomSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
