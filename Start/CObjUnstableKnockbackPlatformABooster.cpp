#include "pch.h"
#include "CObjUnstableKnockbackPlatformABooster.h"


#include "pch.h"
#include "CObjBossFireBird.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CObjBossFireBirdWing.h"
#include "CObjBossFireBirdGun.h"

CObjUnstableKnockbackPlatformABooster::CObjUnstableKnockbackPlatformABooster()
{
	Set_DbgName(_T("CObjUnstableKnockbackPlatformABooster"));
}

CObjUnstableKnockbackPlatformABooster::~CObjUnstableKnockbackPlatformABooster()
{
	Release();
}

void CObjUnstableKnockbackPlatformABooster::Initialize()
{
	//CObjCollisionRect::Initialize();
	//Set_Option(ERI_CLIMABLE);

	Set_UseMainScroll(true);
	m_tInfo.fCX = 198;
	m_tInfo.fCY = 77;


	m_eFrameKey = FKI_Spr_UnstableKnockbackPlatform_Booster_sheet;
	m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_BOOSTER;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());

}

int CObjUnstableKnockbackPlatformABooster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	//m_tInfo.fX += 0.1;

	return OBJ_NOEVENT;
}

void CObjUnstableKnockbackPlatformABooster::Late_Update()
{
	Motion_Change();
}

void CObjUnstableKnockbackPlatformABooster::Render(HDC hDC)
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

void CObjUnstableKnockbackPlatformABooster::Release()
{
}


void CObjUnstableKnockbackPlatformABooster::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}