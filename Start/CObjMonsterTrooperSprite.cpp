#include "pch.h"
#include "CObjMonsterTrooperSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterTrooper.h"
CObjMonsterTrooperSprite::CObjMonsterTrooperSprite()
{
}

CObjMonsterTrooperSprite::~CObjMonsterTrooperSprite()
{
}

void CObjMonsterTrooperSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 79;
	m_tInfo.fCY = 85;


	m_eFrameKey = FKI_Spr_MONSTER_TROOPER_SHEET;
	m_eCurState = FSI_MONSTER_TROOPER_PODPOPUP;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterTrooperSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterTrooper* parent = dynamic_cast<CObjMonsterTrooper*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterTrooper::AST_PODPOPUP_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_PODPOPUP;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_PODPOPUP_ING;
			}
			break;
			case CObjMonsterTrooper::AST_PODPOPUP_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterTrooper::AST_PODPOPUP_END;
				}
			}
			break;
			case CObjMonsterTrooper::AST_PODPOPUP_END:
			{
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_IDLE_START;
			}
			break;









			case CObjMonsterTrooper::AST_PODINSERT_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_PODINSERT;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_PODINSERT_ING;
			}
			break;
			case CObjMonsterTrooper::AST_PODINSERT_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterTrooper::AST_PODINSERT_END;
				}
			}
			break;
			case CObjMonsterTrooper::AST_PODINSERT_END:
			{
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_IDLE_START;
			}
			break;


			case CObjMonsterTrooper::AST_RIGHT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_RIGHT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_IDLE_ING;
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_IDLE_END:
			{
				
			}
			break;


			case CObjMonsterTrooper::AST_LEFT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_LEFT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_IDLE_ING;
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_IDLE_END:
			{

			}
			break;



			case CObjMonsterTrooper::AST_RIGHT_RUNNING_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_RIGHT_RUNNING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_RUNNING_ING;
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_RUNNING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_RUNNING_END:
			{

			}
			break;

			case CObjMonsterTrooper::AST_LEFT_RUNNING_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_LEFT_RUNNING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_RUNNING_ING;
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_RUNNING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_RUNNING_END:
			{

			}
			break;


			case CObjMonsterTrooper::AST_RIGHT_EXCHOLDSTART_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_RIGHT_EXCHOLDSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_EXCHOLDSTART_ING;
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_EXCHOLDSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_EXCHOLDSTART_END;
				}
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_EXCHOLDSTART_END:
			{
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_EXCHOLDBACK_START;;
			}
			break;

			case CObjMonsterTrooper::AST_LEFT_EXCHOLDSTART_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_LEFT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_EXCHOLDSTART_ING;
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_EXCHOLDSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_EXCHOLDSTART_END;
				}
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_EXCHOLDSTART_END:
			{
				parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_EXCHOLDBACK_START;
			}
			break;




			case CObjMonsterTrooper::AST_RIGHT_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_RIGHT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_DEAD_ING;
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterTrooper::AST_RIGHT_DEAD_END;
				}
			}
			break;
			case CObjMonsterTrooper::AST_RIGHT_DEAD_END:
			{
				
			}
			break;

			case CObjMonsterTrooper::AST_LEFT_DEAD_START:
			{
				m_eCurState = FSI_MONSTER_TROOPER_LEFT_DEAD;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_DEAD_ING;
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_DEAD_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterTrooper::AST_LEFT_DEAD_END;
				}
			}
			break;
			case CObjMonsterTrooper::AST_LEFT_DEAD_END:
			{
				
			}
			break;











			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterTrooperSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterTrooperSprite::Render(HDC hDC)
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

void CObjMonsterTrooperSprite::Release()
{
}

void CObjMonsterTrooperSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
