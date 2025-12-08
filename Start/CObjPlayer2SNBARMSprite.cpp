#include "pch.h"
#include "CObjPlayer2SNBARMSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjPlayer2SNBARMSprite::CObjPlayer2SNBARMSprite()
{
	Set_DbgName(_T("CObjPlayer2SNBARMSprite"));
}

CObjPlayer2SNBARMSprite::~CObjPlayer2SNBARMSprite()
{
	Release();
}

void CObjPlayer2SNBARMSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 264;
	m_tInfo.fCY = 112;

	m_eFrameKey = FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET;
	m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjPlayer2SNBARMSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2SNBARMSprite::Late_Update()
{
}

void CObjPlayer2SNBARMSprite::Render(HDC hDC)
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

void CObjPlayer2SNBARMSprite::Release()
{
}

void CObjPlayer2SNBARMSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
