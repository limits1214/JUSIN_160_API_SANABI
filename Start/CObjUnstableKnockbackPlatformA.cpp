#include "pch.h"
#include "CObjUnstableKnockbackPlatformA.h"
#include "CTimeMgr.h"



#include "pch.h"
#include "CObjBossFireBird.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CObjBossFireBirdWing.h"
#include "CObjBossFireBirdGun.h"

CObjUnstableKnockbackPlatformA::CObjUnstableKnockbackPlatformA()
{
	Set_DbgName(_T("CObjUnstableKnockbackPlatformA"));
}

CObjUnstableKnockbackPlatformA::~CObjUnstableKnockbackPlatformA()
{
	Release();
}

void CObjUnstableKnockbackPlatformA::Initialize()
{
	//CObjCollisionRect::Initialize();
	Set_Option(ERI_CLIMABLE);

	Set_UseMainScroll(true);
	m_tInfo.fCX = 264;
	m_tInfo.fCY = 112;


	m_eFrameKey = FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET;
	m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());

}

int CObjUnstableKnockbackPlatformA::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	//m_tInfo.fX += 0.1;

	return OBJ_NOEVENT;
}

void CObjUnstableKnockbackPlatformA::Late_Update()
{
	Motion_Change();
}

void CObjUnstableKnockbackPlatformA::Render(HDC hDC)
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

void CObjUnstableKnockbackPlatformA::Release()
{
}

void CObjUnstableKnockbackPlatformA::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}


void CObjUnstableKnockbackPlatformA::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}