#include "pch.h"
#include "CObjPlayer2SNBARMSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjPlayer2.h"

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
	m_tInfo.fCX = 120;
	m_tInfo.fCY = 61;

	m_eFrameKey = FKI_Spr_SNB_SHEET_NEW;
	m_eCurState = FSI_NEW_R_ARM_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjPlayer2SNBARMSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	AniStateUpdate();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2SNBARMSprite::Late_Update()
{
	Motion_Change();
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
		if (m_eCurState == FSI_END)
		{
			//m_ePreState = m_eCurState;
			m_eFrameKey = FKI_END;
			return;
		}
		else {
			m_eFrameKey = FKI_Spr_SNB_SHEET_NEW;
		}
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}


void CObjPlayer2SNBARMSprite::AniStateUpdate()
{
	CObjPlayer2* parent = dynamic_cast<CObjPlayer2*>(m_pParent);
	if (parent != nullptr)
	{
		DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();

		switch (parent->m_eAniStateSNBARM)
		{

		case CObjPlayer2::AST_RIGHT_ARM_IDLE_START:
		{
			m_eCurState = FSI_NEW_R_ARM_IDLE;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_IDLE_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_IDLE_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_IDLE_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_IDLE_START:
		{
			m_eCurState = FSI_NEW_L_ARM_IDLE;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_IDLE_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_IDLE_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_IDLE_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_RUNSTART_START:
		{
			m_eCurState = FSI_NEW_R_ARM_RUNSTART;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_RUNSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_RUNSTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNNING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNSTART_START:
		{
			m_eCurState = FSI_NEW_L_ARM_RUNSTART;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNSTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNNING_START;
		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_RUNNING_START:
		{
			m_eCurState = FSI_NEW_R_ARM_RUNNING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNNING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_RUNNING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_RUNNING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNNING_START:
		{
			m_eCurState = FSI_NEW_L_ARM_RUNNING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNNING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNNING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNNING_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_RUNSTOP_START:
		{
			m_eCurState = FSI_NEW_R_ARM_RUNSTOP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNSTOP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_RUNSTOP_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNSTOP_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_RUNSTOP_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_IDLE_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNSTOP_START:
		{
			m_eCurState = FSI_NEW_L_ARM_RUNSTOP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNSTOP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNSTOP_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNSTOP_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_RUNSTOP_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_IDLE_START;
		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_JUMPING_START:
		{
			m_eCurState = FSI_NEW_R_ARM_JUMPING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_JUMPING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_JUMPING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_JUMPING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_JUMPING_START:
		{
			m_eCurState = FSI_NEW_L_ARM_JUMPING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_JUMPING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_JUMPING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_JUMPING_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_FALLSTART_START:
		{
			m_eCurState = FSI_NEW_R_ARM_FALLSTART;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_FALLSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_FALLSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_FALLSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_FALLSTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_FALLING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_FALLSTART_START:
		{
			m_eCurState = FSI_NEW_L_ARM_FALLSTART;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_FALLSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_FALLSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_FALLSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_FALLSTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_FALLING_START;
		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_FALLING_START:
		{
			m_eCurState = FSI_NEW_R_ARM_FALLING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_FALLING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_FALLING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_FALLING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_FALLING_START:
		{
			m_eCurState = FSI_NEW_L_ARM_FALLING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_FALLING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_FALLING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_FALLING_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_ARM_LANDING_START:
		{
			m_eCurState = FSI_NEW_R_ARM_LANDING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_LANDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_LANDING_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_LANDING_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_LANDING_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_IDLE_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_LANDING_START:
		{
			m_eCurState = FSI_NEW_L_ARM_LANDING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_LANDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_LANDING_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_LANDING_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_LANDING_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_IDLE_START;
		}
		break;


		case CObjPlayer2::AST_RIGHT_ARM_LAND2RUN_START:
		{
			m_eCurState = FSI_NEW_R_ARM_LAND2RUN;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_LAND2RUN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_LAND2RUN_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_LAND2RUN_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_LAND2RUN_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_RUNNING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_LAND2RUN_START:
		{
			m_eCurState = FSI_NEW_L_ARM_LAND2RUN;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_LAND2RUN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_LAND2RUN_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_LAND2RUN_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_LAND2RUN_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_RUNNING_START;
		}
		break;



		case CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDE_START_START:
		{
			m_eCurState = FSI_NEW_R_ARM_WALL_SLIDE_START;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDE_START_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDE_START_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDE_START_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDE_START_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_SLIDE_START_START:
		{
			m_eCurState = FSI_NEW_L_ARM_WALL_SLIDE_START;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_WALL_SLIDE_START_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_SLIDE_START_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_WALL_SLIDE_START_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_SLIDE_START_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_WALL_SLIDING_START;
		}
		break;


		case CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDING_START:
		{
			m_eCurState = FSI_NEW_R_ARM_WALL_SLIDING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_SLIDING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_SLIDING_START:
		{
			m_eCurState = FSI_NEW_L_ARM_WALL_SLIDING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_WALL_SLIDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_SLIDING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_SLIDING_END:
		{

		}
		break;


		case CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBUP_START:
		{
			m_eCurState = FSI_NEW_R_ARM_WALL_CLIMBUP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBUP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBUP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBUP_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBUP_START:
		{
			m_eCurState = FSI_NEW_L_ARM_WALL_CLIMBUP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBUP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBUP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBUP_END:
		{

		}
		break;



		case CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBDOWN_START:
		{
			m_eCurState = FSI_NEW_R_ARM_WALL_CLIMBDOWN;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBDOWN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBDOWN_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_WALL_CLIMBDOWN_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBDOWN_START:
		{
			m_eCurState = FSI_NEW_L_ARM_WALL_CLIMBDOWN;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBDOWN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBDOWN_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_WALL_CLIMBDOWN_END:
		{

		}
		break;


		case CObjPlayer2::AST_RIGHT_ARM_SWING_START:
		{
			m_eCurState = FSI_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_SWING_ING;
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_SWING_ING:
		{
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_SWING_END:
		{
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWING_START:
		{
			m_eCurState = FSI_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_SWING_ING;
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWING_ING:
		{
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWING_END:
		{
		}
		break;





		case CObjPlayer2::AST_RIGHT_ARM_SWINGJUMP_START:
		{
			m_eCurState = FSI_NEW_R_ARM_SWING_JUMP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_SWINGJUMP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_SWINGJUMP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_SWINGJUMP_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWINGJUMP_START:
		{
			m_eCurState = FSI_NEW_L_ARM_SWING_JUMP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_SWINGJUMP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWINGJUMP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWINGJUMP_END:
		{

		}
		break;


		case CObjPlayer2::AST_RIGHT_ARM_SWINGJUMPUP_START:
		{
			m_eCurState = FSI_NEW_R_ARM_SWING_JUMP_UP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_SWINGJUMPUP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_SWINGJUMPUP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_SWINGJUMPUP_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWINGJUMPUP_START:
		{
			m_eCurState = FSI_NEW_L_ARM_SWING_JUMP_UP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_SWINGJUMPUP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWINGJUMPUP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_SWINGJUMPUP_END:
		{

		}
		break;




		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKSTART_START:
		{
			m_eCurState = FSI_NEW_R_ARM_CEILING_STICK_START;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKSTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKIDLE_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKSTART_START:
		{
			m_eCurState = FSI_NEW_L_ARM_CEILING_STICK_START;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKSTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKIDLE_START;
		}
		break;





		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKIDLE_START:
		{
			m_eCurState = FSI_NEW_R_ARM_CEILING_STICK_IDLE;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKIDLE_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKIDLE_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKIDLE_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKIDLE_START:
		{
			m_eCurState = FSI_NEW_L_ARM_CEILING_STICK_IDLE;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKIDLE_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKIDLE_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKIDLE_END:
		{

		}
		break;



		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKJUMP_START:
		{
			m_eCurState = FSI_NEW_R_ARM_CEILING_STICK_JUMP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKJUMP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKJUMP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKJUMP_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKJUMP_START:
		{
			m_eCurState = FSI_NEW_L_ARM_CEILING_STICK_JUMP;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKJUMP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKJUMP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKJUMP_END:
		{

		}
		break;





		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVESTART_START:
		{
			m_eCurState = FSI_NEW_R_ARM_CEILING_STICK_MOVE_START;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVESTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVESTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVESTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVESTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVESTART_START:
		{
			m_eCurState = FSI_NEW_L_ARM_CEILING_STICK_MOVE_START;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVESTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVESTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVESTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVESTART_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVING_START;
		}
		break;




		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVING_START:
		{
			m_eCurState = FSI_NEW_R_ARM_CEILING_STICK_MOVING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVING_END:
		{
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVING_START:
		{
			m_eCurState = FSI_NEW_L_ARM_CEILING_STICK_MOVING;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVING_ING:
		{
			Move_Frame();
			
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVING_END:
		{
		}
		break;



		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVEEND_START:
		{
			m_eCurState = FSI_NEW_R_ARM_CEILING_STICK_MOVE_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVEEND_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVEEND_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVEEND_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKMOVEEND_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_CEILINGSTICKIDLE_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVEEND_START:
		{
			m_eCurState = FSI_NEW_L_ARM_CEILING_STICK_MOVE_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVEEND_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVEEND_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVEEND_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKMOVEEND_END:
		{
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_CEILINGSTICKIDLE_START;
		}
		break;




		case CObjPlayer2::AST_RIGHT_ARM_DAMAGED_START:
		{
			m_eCurState = FSI_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_SWING_ING;
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_DAMAGED_ING:
		{
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_DAMAGED_END:
		{
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_DAMAGED_START:
		{
			m_eCurState = FSI_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_SWING_ING;
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_DAMAGED_ING:
		{
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_DAMAGED_END:
		{
		}
		break;


		

		case CObjPlayer2::AST_RIGHT_ARM_DASH_START:
		{
			m_eCurState = FSI_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_SWING_ING;
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_DASH_ING:
		{
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_DASH_END:
		{
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_DASH_START:
		{
			m_eCurState = FSI_END;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_SWING_ING;
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_DASH_ING:
		{
			//Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_DASH_END:
		{
		}
		break;



		case CObjPlayer2::AST_RIGHT_ARM_EXCHOLDBACK_START:
		{
			m_eCurState = FSI_NEW_R_ARM_EXCHOLDBACK;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_SWING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_EXCHOLDBACK_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_EXCHOLDBACK_END:
		{
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_EXCHOLDBACK_START:
		{
			m_eCurState = FSI_NEW_L_ARM_EXCHOLDBACK;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_SWING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_EXCHOLDBACK_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_EXCHOLDBACK_END:
		{
		}
		break;



		case CObjPlayer2::AST_RIGHT_ARM_EXCDASH_START:
		{
			m_eCurState = FSI_NEW_R_ARM_EXCDASH;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_RIGHT_ARM_EXCDASH_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_EXCDASH_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_EXCDASH_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_ARM_EXCDASH_END:
		{
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_EXCDASH_START:
		{
			m_eCurState = FSI_NEW_L_ARM_EXCDASH;
			parent->m_eAniStateSNBARM = CObjPlayer2::AST_LEFT_ARM_EXCDASH_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_EXCDASH_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_EXCDASH_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_ARM_EXCDASH_END:
		{
		}
		break;

		}
	}
}