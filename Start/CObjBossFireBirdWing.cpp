#include "pch.h"
#include "CObjBossFireBirdWing.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjBossFireBirdWing::CObjBossFireBirdWing()
{
	Set_DbgName(_T("CObjBossFireBirdWing"));
}

CObjBossFireBirdWing::~CObjBossFireBirdWing()
{
	Release();
}

void CObjBossFireBirdWing::Initialize()
{
	Set_UseMainScroll(true);
	//m_tInfo.fCX = 1308;
	//m_tInfo.fCY = 134;


	//m_eFrameKey = FKI_Spr_BOSS_Firebird_Wing_DownLoop01_Sheet_tw1308_th134_sw5232_sh268_c8;


	m_tInfo.fCX = 1304;
	m_tInfo.fCY = 234;
	m_eFrameKey = FKI_Spr_BOSS_FirebirdWing_sheet;
	/*m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_DOWNLOOP1;
	m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_UPLOOP1;*/
	m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_DOWNLOOP;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFireBirdWing::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CObjBossFireBirdWing::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBirdWing::Render(HDC hDC)
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

void CObjBossFireBirdWing::Release()
{
}

void CObjBossFireBirdWing::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}