#include "pch.h"
#include "CObjBossFirebirdBody.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjBossFirebirdBody::CObjBossFirebirdBody()
{
	Set_DbgName(_T("CObjBossFirebirdBody"));
}

CObjBossFirebirdBody::~CObjBossFirebirdBody()
{
	Release();
}

void CObjBossFirebirdBody::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 688;
	m_tInfo.fCY = 352;

	m_eFrameKey = FKI_Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8;
	m_eCurState = FSI_BOSS_FIREBIRD_BODY_NORMAL_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFirebirdBody::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CObjBossFirebirdBody::Late_Update()
{
	Motion_Change();
}

void CObjBossFirebirdBody::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	//Rectangle(hDC, m_tRect.left , m_tRect.top , m_tRect.right , m_tRect.bottom );
	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjBossFirebirdBody::Release()
{
}

void CObjBossFirebirdBody::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}