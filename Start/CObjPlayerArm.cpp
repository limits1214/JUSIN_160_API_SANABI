#include "pch.h"
#include "CObjPlayerArm.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjPlayer.h"

CObjPlayerArm::CObjPlayerArm()
{
	Set_DbgName(_T("CObjPlayerArm"));
}

CObjPlayerArm::~CObjPlayerArm()
{
	Release();
}

void CObjPlayerArm::Initialize()
{
	m_tInfo.fCX = 112.f;
	m_tInfo.fCY = 104.f;

	m_eFrameKey = FKI_Spr_SNB_SHEET_2;
	m_eCurState = FSI_SNBARM_R_IDLE;

	m_bUseMainScroll = true;
}

int CObjPlayerArm::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// 입력받고 그릴지 아니면 그리고 입력받을지...
	__super::Update_Rect();

	auto parent = dynamic_cast<CObjPlayer*>(m_pParent);
	if (parent != nullptr)
	{
		auto state = parent->Get_PlayerState();
		if (state == FSI_SNB_R_RUNNING)
		{
			m_eCurState = FSI_SNBARM_R_RUNNING;
		}
		else if (state == FSI_SNB_R_IDLE)
		{
			m_eCurState = FSI_SNBARM_R_IDLE;
		}
		else if (state == FSI_SNB_R_RUNSTART)
		{
			m_eCurState = FSI_SNBARM_R_RUNSTART;
		}
		else if (state == FSI_SNB_R_RUNSTOP)
		{
			m_eCurState = FSI_SNBARM_R_RUNSTOP;
		}
	}


	Move_Frame();
}

void CObjPlayerArm::Late_Update()
{
	Motion_Change();
}

void CObjPlayerArm::Render(HDC hDC)
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

void CObjPlayerArm::Release()
{
}

void CObjPlayerArm::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}