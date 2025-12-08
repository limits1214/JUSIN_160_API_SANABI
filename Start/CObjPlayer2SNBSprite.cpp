#include "pch.h"
#include "CObjPlayer2SNBSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjPlayer2.h"

CObjPlayer2SNBSprite::CObjPlayer2SNBSprite()
{
	Set_DbgName(_T("CObjPlayer2SNBSprite"));
}

CObjPlayer2SNBSprite::~CObjPlayer2SNBSprite()
{
	Release();
}

void CObjPlayer2SNBSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 60;
	m_tInfo.fCY = 61;

	m_eFrameKey = FKI_Spr_SNB_SHEET_NEW;
	m_eCurState = FSI_NEW_L_SNB_LAND2RUN;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjPlayer2SNBSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	AniStateUpdate();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2SNBSprite::Late_Update()
{
	Motion_Change();
}

void CObjPlayer2SNBSprite::Render(HDC hDC)
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

void CObjPlayer2SNBSprite::Release()
{
}

void CObjPlayer2SNBSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}


void CObjPlayer2SNBSprite::AniStateUpdate()
{
	

	CObjPlayer2* parent = dynamic_cast<CObjPlayer2*>(m_pParent);
	if (parent != nullptr)
	{
		DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();

		switch (parent->m_eAniStateSNB)
		{

		case CObjPlayer2::AST_RIGHT_SNB_IDLE_START:
		{
			m_eCurState = FSI_NEW_R_SNB_IDLE;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_IDLE_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_IDLE_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_IDLE_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_IDLE_START:
		{
			m_eCurState = FSI_NEW_L_SNB_IDLE;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_IDLE_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_IDLE_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_IDLE_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_RUNSTART_START:
		{
			m_eCurState = FSI_NEW_R_SNB_RUNSTART;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_RUNSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_RUNSTART_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNNING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNSTART_START:
		{
			m_eCurState = FSI_NEW_L_SNB_RUNSTART;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNSTART_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNNING_START;
		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_RUNNING_START:
		{
			m_eCurState = FSI_NEW_R_SNB_RUNNING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNNING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_RUNNING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_RUNNING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNNING_START:
		{
			m_eCurState = FSI_NEW_L_SNB_RUNNING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNNING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNNING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNNING_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_RUNSTOP_START:
		{
			m_eCurState = FSI_NEW_R_SNB_RUNSTOP;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNSTOP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_RUNSTOP_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNSTOP_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_RUNSTOP_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_IDLE_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNSTOP_START:
		{
			m_eCurState = FSI_NEW_L_SNB_RUNSTOP;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNSTOP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNSTOP_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNSTOP_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_RUNSTOP_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_IDLE_START;
		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_JUMPING_START:
		{
			m_eCurState = FSI_NEW_R_SNB_JUMPING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_JUMPING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_JUMPING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_JUMPING_END:
		{
			
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_JUMPING_START:
		{
			m_eCurState = FSI_NEW_L_SNB_JUMPING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_JUMPING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_JUMPING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_JUMPING_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_FALLSTART_START:
		{
			m_eCurState = FSI_NEW_R_SNB_FALLSTART;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_FALLSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_FALLSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_FALLSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_FALLSTART_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_FALLING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_FALLSTART_START:
		{
			m_eCurState = FSI_NEW_L_SNB_FALLSTART;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_FALLSTART_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_FALLSTART_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_FALLSTART_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_FALLSTART_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_FALLING_START;
		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_FALLING_START:
		{
			m_eCurState = FSI_NEW_R_SNB_FALLING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_FALLING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_FALLING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_FALLING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_FALLING_START:
		{
			m_eCurState = FSI_NEW_L_SNB_FALLING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_FALLING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_FALLING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_FALLING_END:
		{

		}
		break;

		case CObjPlayer2::AST_RIGHT_SNB_LANDING_START:
		{
			m_eCurState = FSI_NEW_R_SNB_LANDING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_LANDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_LANDING_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_LANDING_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_LANDING_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_IDLE_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_LANDING_START:
		{
			m_eCurState = FSI_NEW_L_SNB_LANDING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_LANDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_LANDING_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_LANDING_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_LANDING_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_IDLE_START;
		}
		break;


		case CObjPlayer2::AST_RIGHT_SNB_LAND2RUN_START:
		{
			m_eCurState = FSI_NEW_R_SNB_LAND2RUN;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_LAND2RUN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_LAND2RUN_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_LAND2RUN_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_LAND2RUN_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_RUNNING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_LAND2RUN_START:
		{
			m_eCurState = FSI_NEW_L_SNB_LAND2RUN;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_LAND2RUN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_LAND2RUN_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_LAND2RUN_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_LAND2RUN_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_RUNNING_START;
		}
		break;



		case CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDE_START_START:
		{
			m_eCurState = FSI_NEW_R_SNB_WALL_SLIDE_START;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDE_START_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDE_START_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDE_START_END;
			}
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDE_START_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDING_START;
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_SLIDE_START_START:
		{
			m_eCurState = FSI_NEW_L_SNB_WALL_SLIDE_START;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_WALL_SLIDE_START_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_SLIDE_START_ING:
		{
			Move_Frame();
			int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
			if (m_tFrame.iStart == end)
			{
				parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_WALL_SLIDE_START_END;
			}
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_SLIDE_START_END:
		{
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_WALL_SLIDING_START;
		}
		break;


		case CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDING_START:
		{
			m_eCurState = FSI_NEW_R_SNB_WALL_SLIDING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_SLIDING_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_SLIDING_START:
		{
			m_eCurState = FSI_NEW_L_SNB_WALL_SLIDING;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_WALL_SLIDING_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_SLIDING_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_SLIDING_END:
		{

		}
		break;


		case CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBUP_START:
		{
			m_eCurState = FSI_NEW_R_SNB_WALL_CLIMBUP;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBUP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBUP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBUP_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBUP_START:
		{
			m_eCurState = FSI_NEW_L_SNB_WALL_CLIMBUP;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBUP_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBUP_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBUP_END:
		{

		}
		break;



		case CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBDOWN_START:
		{
			m_eCurState = FSI_NEW_R_SNB_WALL_CLIMBDOWN;
			parent->m_eAniStateSNB = CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBDOWN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBDOWN_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_RIGHT_SNB_WALL_CLIMBDOWN_END:
		{

		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBDOWN_START:
		{
			m_eCurState = FSI_NEW_L_SNB_WALL_CLIMBDOWN;
			parent->m_eAniStateSNB = CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBDOWN_ING;
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBDOWN_ING:
		{
			Move_Frame();
		}
		break;
		case CObjPlayer2::AST_LEFT_SNB_WALL_CLIMBDOWN_END:
		{

		}
		break;




		}
	}
}