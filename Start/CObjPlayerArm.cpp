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
		else if (state == FSI_SNB_R_JUMPING)
		{
			m_eCurState = FSI_SNBARM_R_JUMPING;
		}
		else if (state == FSI_SNB_R_FALLSTART)
		{
			m_eCurState = FSI_SNBARM_R_FALLSTART;
		}
		else if (state == FSI_SNB_R_FALLING)
		{
			m_eCurState = FSI_SNBARM_R_FALLING;
		}
		else if (state == FSI_SNB_R_WALLCLIMBUP)
		{
			m_eCurState = FSI_SNBARM_R_WALLCLIMBUP;
		}
		else if (state == FSI_SNB_R_WALLCLIMBDOWN)
		{
			m_eCurState = FSI_SNBARM_R_WALLCLIMBDOWN;
		}
		else if (state == FSI_SNB_R_SWING)
		{
			m_eCurState = (FRAME_STATE_ID)999;
		}
		else if (state == FSI_SNB_R_DAMAGED)
		{
			m_eCurState = FSI_SNBARM_R_DAMAGED;
		}
		else if (state == FSI_SNB_R_DAMAGEDDASH)
		{
			m_eCurState = (FRAME_STATE_ID)999;
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
		if (m_eCurState == 999)
		{
			m_ePreState = m_eCurState;
			m_eFrameKey = FKI_END;
			return;
		}
		else {
			m_eFrameKey = FKI_Spr_SNB_SHEET_2;
		}
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}