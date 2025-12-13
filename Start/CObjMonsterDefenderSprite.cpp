#include "pch.h"
#include "CObjMonsterDefenderSprite.h"
#include "CObjMonsterDefender.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjMonsterDefenderSprite::CObjMonsterDefenderSprite()
{
}

CObjMonsterDefenderSprite::~CObjMonsterDefenderSprite()
{
}

void CObjMonsterDefenderSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 105;
	m_tInfo.fCY = 77;


	m_eFrameKey = FKI_Spr_MONSTER_DEFENDER_SHEET;
	m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_SET;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterDefenderSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterDefender* parent = dynamic_cast<CObjMonsterDefender*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterDefender::AST_RIGHT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_IDLE_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_IDLE_END:
			{
			}
			break;


			case CObjMonsterDefender::AST_RIGHT_SET_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_SET;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_SET_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_SET_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_SET_END;
				}
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_SET_END:
			{
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_IDLE_START;
			}
			break;


			case CObjMonsterDefender::AST_RIGHT_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_DEAD_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_DEAD_END;
				}

			}
			break;
			case CObjMonsterDefender::AST_RIGHT_DEAD_END:
			{
			}
			break;





			case CObjMonsterDefender::AST_RIGHT_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_EXCHOLDBACK_END:
			{
			}
			break;




			case CObjMonsterDefender::AST_RIGHT_STUNNED_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_STUNNED;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_STUNNED_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_STUNNED_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_STUNNED_END:
			{
			}
			break;





			case CObjMonsterDefender::AST_RIGHT_TURNSTART_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_TURNSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_TURNSTART_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_TURNSTART_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_TURNSTART_END:
			{
			}
			break;





			case CObjMonsterDefender::AST_RIGHT_TURNEND_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_RIGHT_TURNEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_RIGHT_TURNEND_ING;
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_TURNEND_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_RIGHT_TURNEND_END:
			{
			}
			break;






			case CObjMonsterDefender::AST_LEFT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_IDLE_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_LEFT_IDLE_END:
			{
			}
			break;




			case CObjMonsterDefender::AST_LEFT_SET_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_SET;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_SET_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_SET_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDefender::AST_LEFT_SET_END;
				}
			}
			break;
			case CObjMonsterDefender::AST_LEFT_SET_END:
			{
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_IDLE_START;
			}
			break;



			case CObjMonsterDefender::AST_LEFT_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_DEAD_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDefender::AST_LEFT_DEAD_END;
				}
			}
			break;
			case CObjMonsterDefender::AST_LEFT_DEAD_END:
			{
			}
			break;



			case CObjMonsterDefender::AST_LEFT_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_LEFT_EXCHOLDBACK_END:
			{
			}
			break;




			case CObjMonsterDefender::AST_LEFT_STUNNED_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_STUNNED;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_STUNNED_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_STUNNED_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_LEFT_STUNNED_END:
			{
			}
			break;


			case CObjMonsterDefender::AST_LEFT_TURNSTART_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_TURNSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_TURNSTART_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_TURNSTART_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_LEFT_TURNSTART_END:
			{
			}
			break;



			case CObjMonsterDefender::AST_LEFT_TURNEND_START:
			{
				m_eCurState = FSI_MONSTER_DEFENDER_LEFT_TURNEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDefender::AST_LEFT_TURNEND_ING;
			}
			break;
			case CObjMonsterDefender::AST_LEFT_TURNEND_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDefender::AST_LEFT_TURNEND_END:
			{
			}
			break;




			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDefenderSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterDefenderSprite::Render(HDC hDC)
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

void CObjMonsterDefenderSprite::Release()
{
}

void CObjMonsterDefenderSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
