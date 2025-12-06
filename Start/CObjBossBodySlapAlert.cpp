#include "pch.h"
#include "CObjBossBodySlapAlert.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjBossBodySlapAlert::CObjBossBodySlapAlert()

{
}

CObjBossBodySlapAlert::~CObjBossBodySlapAlert()
{
	Release();
}

void CObjBossBodySlapAlert::Initialize()
{
	m_bUseMainScroll = true;

	m_tInfo.fCX = 35;
	m_tInfo.fCY = 346;
	m_eFrameKey = FKI_Spr_BOSS_BodySlapAlert_sheet;

	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_BODY_SLAP_ALERT, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossBodySlapAlert::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	int end = FrameStateId_To_Frame(FSI_BOSS_BODY_SLAP_ALERT, dwNow).iEnd;
	if (m_tFrame.iStart == end)
	{
		Set_Dead();
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBossBodySlapAlert::Late_Update()
{
}

void CObjBossBodySlapAlert::Render(HDC hDC)
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

void CObjBossBodySlapAlert::Release()
{
}
