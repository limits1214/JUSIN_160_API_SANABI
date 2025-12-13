#include "pch.h"
#include "CObjMonsterDummyRobotSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterDummyRobot.h"

CObjMonsterDummyRobotSprite::CObjMonsterDummyRobotSprite()
{
}

CObjMonsterDummyRobotSprite::~CObjMonsterDummyRobotSprite()
{
}

void CObjMonsterDummyRobotSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 65;
	m_tInfo.fCY = 48;


	m_eFrameKey = FKI_Spr_MONSTER_DUMMYROBOT_SHEET;
	m_eCurState = FSI_MONSTER_DUMMYROBOT_RESPAWN;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterDummyRobotSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterDummyRobot* parent = dynamic_cast<CObjMonsterDummyRobot*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterDummyRobot::AST_RESPAWN_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_RESPAWN;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_RESPAWN_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_RESPAWN_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDummyRobot::AST_RESPAWN_END;
				}
			}
			break;
			case CObjMonsterDummyRobot::AST_RESPAWN_END:
			{
				parent->m_eAniState = CObjMonsterDummyRobot::AST_RIGHT_IDLE_START;
			}
			break;



			case CObjMonsterDummyRobot::AST_LEFT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_LEFT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_LEFT_IDLE_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_LEFT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyRobot::AST_LEFT_IDLE_END:
			{
				
			}
			break;

			case CObjMonsterDummyRobot::AST_RIGHT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_RIGHT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_RIGHT_IDLE_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_RIGHT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyRobot::AST_RIGHT_IDLE_END:
			{

			}
			break;


			case CObjMonsterDummyRobot::AST_LEFT_RUNNING_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_LEFT_RUNNING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_LEFT_RUNNING_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_LEFT_RUNNING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyRobot::AST_LEFT_RUNNING_END:
			{

			}
			break;


			case CObjMonsterDummyRobot::AST_RIGHT_RUNNING_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_RIGHT_RUNNING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_RIGHT_RUNNING_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_RIGHT_RUNNING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyRobot::AST_RIGHT_RUNNING_END:
			{

			}
			break;



			case CObjMonsterDummyRobot::AST_EXCSTART_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_EXCSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_EXCSTART_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_EXCSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDummyRobot::AST_EXCSTART_END;
				}
			}
			break;
			case CObjMonsterDummyRobot::AST_EXCSTART_END:
			{
				parent->m_eAniState = CObjMonsterDummyRobot::AST_EXCHOLDBACK_START;
			}
			break;




			case CObjMonsterDummyRobot::AST_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyRobot::AST_EXCHOLDBACK_END:
			{

			}
			break;



			case CObjMonsterDummyRobot::AST_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYROBOT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyRobot::AST_DEAD_ING;
			}
			break;
			case CObjMonsterDummyRobot::AST_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDummyRobot::AST_DEAD_END;
				}
			}
			break;
			case CObjMonsterDummyRobot::AST_DEAD_END:
			{

			}
			break;






			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDummyRobotSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterDummyRobotSprite::Render(HDC hDC)
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

void CObjMonsterDummyRobotSprite::Release()
{
}

void CObjMonsterDummyRobotSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
