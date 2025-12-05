#include "pch.h"
#include "CObjBossFireBirdGun.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjBossFireBirdGun::CObjBossFireBirdGun()
{
	Set_DbgName(_T("CObjBossFireBirdGun"));
}

CObjBossFireBirdGun::~CObjBossFireBirdGun()
{
	Release();
}

void CObjBossFireBirdGun::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 440;
	m_tInfo.fCY = 78;

	m_eFrameKey = FKI_Spr_BOSS_FirebirdGun_sheet;
	//m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTLOOP;
	//m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTEND;
	m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTREADYLOOP;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFireBirdGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CObjBossFireBirdGun::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBirdGun::Render(HDC hDC)
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

void CObjBossFireBirdGun::Release()
{
}
void CObjBossFireBirdGun::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}