#include "pch.h"
#include "CObjPlayer2GrabSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjPlayer2GrabSprite::CObjPlayer2GrabSprite()
{
	Set_DbgName(_T("CObjPlayer2GrabSprite"));
}

CObjPlayer2GrabSprite::~CObjPlayer2GrabSprite()
{
	Release();
}

void CObjPlayer2GrabSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 264;
	m_tInfo.fCY = 112;

	m_eFrameKey = FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET;
	m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjPlayer2GrabSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	AniStateUpdate();
	

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2GrabSprite::Late_Update()
{
}

void CObjPlayer2GrabSprite::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjPlayer2GrabSprite::Release()
{
}

void CObjPlayer2GrabSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}

void CObjPlayer2GrabSprite::AniStateUpdate()
{
	//Move_Frame();

}
