#include "pch.h"
#include "CObjMonsterWarriorSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterWarrior.h"
CObjMonsterWarriorSprite::CObjMonsterWarriorSprite()
{
}

CObjMonsterWarriorSprite::~CObjMonsterWarriorSprite()
{
}

void CObjMonsterWarriorSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 225;
	m_tInfo.fCY = 210;


	m_eFrameKey = FKI_Spr_MONSTER_WARRIOR_SHEET;
	m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_SPAWN;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterWarriorSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterWarrior* parent = dynamic_cast<CObjMonsterWarrior*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterWarrior::AST_RIGHT_SPAWN_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_SPAWN;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_SPAWN_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_SPAWN_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_SPAWN_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_SPAWN_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_IDLE_START;
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_SPAWN_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_SPAWN;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_SPAWN_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_SPAWN_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_SPAWN_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_SPAWN_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_IDLE_START;
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_IDLE_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_IDLE_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_IDLE_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_IDLE_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_DEAD_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_DEAD_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_DEAD_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_DEAD_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_DEAD_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_DEAD_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_EXCHOLDSTART_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_EXCHOLDSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_EXCHOLDSTART_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_EXCHOLDSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_EXCHOLDSTART_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_EXCHOLDSTART_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_EXCHOLDBACK_START;
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_EXCHOLDSTART_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_EXCHOLDSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_EXCHOLDSTART_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_EXCHOLDSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_EXCHOLDSTART_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_EXCHOLDSTART_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_EXCHOLDBACK_START;
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_EXCHOLDBACK_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_EXCHOLDBACK_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_COMASTART_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_COMASTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMASTART_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_COMASTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMASTART_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_COMASTART_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMALOOP_START;
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_COMASTART_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_COMASTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_COMASTART_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_COMASTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_COMASTART_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_COMASTART_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_COMALOOP_START;
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_COMALOOP_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_COMALOOP;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMALOOP_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_COMALOOP_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_COMALOOP_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_LEFT_COMALOOP_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_COMALOOP;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMALOOP_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_COMALOOP_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_COMALOOP_END:
			{
			}
			break;

			case CObjMonsterWarrior::AST_RIGHT_COMAEND_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_COMAEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMAEND_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_COMAEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_COMAEND_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_COMAEND_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_IDLE_START;
			}
			break;


			case CObjMonsterWarrior::AST_LEFT_COMAEND_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_COMAEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_COMAEND_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_COMAEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_COMAEND_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_COMAEND_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_IDLE_START;
			}
			break;




			case CObjMonsterWarrior::AST_RIGHT_MOVESTART_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_MOVESTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVESTART_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_MOVESTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVESTART_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_MOVESTART_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVING_START;
			}
			break;


			case CObjMonsterWarrior::AST_RIGHT_MOVING_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_MOVING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVING_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_MOVING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_MOVING_END:
			{
			}
			break;



			case CObjMonsterWarrior::AST_RIGHT_MOVEEND_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_MOVEEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVEEND_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_MOVEEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVEEND_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_MOVEEND_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_IDLE_START;
			}
			break;







			case CObjMonsterWarrior::AST_RIGHT_ATTACKREADY_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_ATTACKREADY;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACKREADY_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_ATTACKREADY_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACKREADY_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_ATTACKREADY_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACK_START;
			}
			break;




			case CObjMonsterWarrior::AST_RIGHT_ATTACKEND_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_ATTACKEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACKEND_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_ATTACKEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACKEND_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_ATTACKEND_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_MOVING_START;
			}
			break;




			case CObjMonsterWarrior::AST_RIGHT_ATTACK_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_RIGHT_ATTACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACK_ING;
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_ATTACK_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACK_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_RIGHT_ATTACK_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_RIGHT_ATTACKEND_START;
			}
			break;





			









			case CObjMonsterWarrior::AST_LEFT_MOVESTART_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_MOVESTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVESTART_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_MOVESTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVESTART_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_MOVESTART_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVING_START;
			}
			break;


			case CObjMonsterWarrior::AST_LEFT_MOVING_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_MOVING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVING_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_MOVING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_MOVING_END:
			{
			}
			break;



			case CObjMonsterWarrior::AST_LEFT_MOVEEND_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_MOVEEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVEEND_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_MOVEEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVEEND_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_MOVEEND_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_IDLE_START;
			}
			break;







			case CObjMonsterWarrior::AST_LEFT_ATTACKREADY_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_ATTACKREADY;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACKREADY_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_ATTACKREADY_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACKREADY_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_ATTACKREADY_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACK_START;
			}
			break;




			case CObjMonsterWarrior::AST_LEFT_ATTACKEND_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_ATTACKEND;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACKEND_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_ATTACKEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACKEND_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_ATTACKEND_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_MOVING_START;
			}
			break;




			case CObjMonsterWarrior::AST_LEFT_ATTACK_START:
			{
				m_eCurState = FSI_MONSTER_WARRIOR_LEFT_ATTACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACK_ING;
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_ATTACK_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACK_END;
				}
			}
			break;
			case CObjMonsterWarrior::AST_LEFT_ATTACK_END:
			{
				parent->m_eAniState = CObjMonsterWarrior::AST_LEFT_ATTACKEND_START;
			}
			break;


			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterWarriorSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterWarriorSprite::Render(HDC hDC)
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

void CObjMonsterWarriorSprite::Release()
{
}

void CObjMonsterWarriorSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
