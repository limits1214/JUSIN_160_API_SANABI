#include "pch.h"
#include "CObjBossFireBirdBomber.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjBossFireBirdBomber::CObjBossFireBirdBomber()
{
	Set_DbgName(_T("CObjBossFireBirdBomber"));
}

CObjBossFireBirdBomber::~CObjBossFireBirdBomber()
{
	Release();
}

void CObjBossFireBirdBomber::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 336;
	m_tInfo.fCY = 116;
	m_eFrameKey = FKI_Spr_BOSS_FirebirdBomber_sheet;
	m_eCurState = FSI_BOSS_FIREBIRD_BOMBER_CLOSING;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFireBirdBomber::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CObjBossFireBirdBomber::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBirdBomber::Render(HDC hDC)
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

void CObjBossFireBirdBomber::Release()
{
}

void CObjBossFireBirdBomber::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}