#include "pch.h"
#include "CObjMonsterSurveyDroneSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterSurveyDrone.h"
CObjMonsterSurveyDroneSprite::CObjMonsterSurveyDroneSprite()
{
}

CObjMonsterSurveyDroneSprite::~CObjMonsterSurveyDroneSprite()
{
}

void CObjMonsterSurveyDroneSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 57;
	m_tInfo.fCY = 48;


	m_eFrameKey = FKI_Spr_MONSTER_SURVEYDRONE_SHEET;
	m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_RESPAWN;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterSurveyDroneSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterSurveyDrone* parent = dynamic_cast<CObjMonsterSurveyDrone*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterSurveyDrone::AST_RIGHT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_IDLE_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_IDLE_END:
			{
			}
			break;

			case CObjMonsterSurveyDrone::AST_RIGHT_RESPAWN_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_RESPAWN;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_RESPAWN_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_RESPAWN_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_RESPAWN_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_RESPAWN_END:
			{
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_IDLE_START;
			}
			break;

			case CObjMonsterSurveyDrone::AST_RIGHT_PHOTO_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_PHOTO;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_PHOTO_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_PHOTO_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_PHOTO_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_PHOTO_END:
			{
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_IDLE_START;
			}
			break;

			case CObjMonsterSurveyDrone::AST_RIGHT_DESTROY_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_DESTROY;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_DESTROY_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_DESTROY_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_DESTROY_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_DESTROY_END:
			{
			}
			break;

			case CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDSTART_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_EXCHOLDSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDSTART_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDSTART_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDSTART_END:
			{
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDBACK_START;
			}
			break;

			case CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_RIGHT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterSurveyDrone::AST_RIGHT_EXCHOLDBACK_END:
			{
			}
			break;

			case CObjMonsterSurveyDrone::AST_LEFT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_LEFT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_IDLE_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_IDLE_END:
			{
			}
			break;

			case CObjMonsterSurveyDrone::AST_LEFT_RESPAWN_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_LEFT_RESPAWN;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_RESPAWN_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_RESPAWN_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_RESPAWN_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_RESPAWN_END:
			{
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_IDLE_START;
			}
			break;

			case CObjMonsterSurveyDrone::AST_LEFT_PHOTO_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_LEFT_PHOTO;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_PHOTO_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_PHOTO_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_PHOTO_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_PHOTO_END:
			{
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_IDLE_START;
			}
			break;

			case CObjMonsterSurveyDrone::AST_LEFT_DESTROY_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_LEFT_DESTROY;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_DESTROY_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_DESTROY_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_DESTROY_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_DESTROY_END:
			{

			}
			break;

			case CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDSTART_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_LEFT_EXCHOLDSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDSTART_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDSTART_END;
				}
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDSTART_END:
			{
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDBACK_START;
			}
			break;

			case CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_SURVEYDRONE_LEFT_EXCHOLDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterSurveyDrone::AST_LEFT_EXCHOLDBACK_END:
			{
			}
			break;

			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterSurveyDroneSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterSurveyDroneSprite::Render(HDC hDC)
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

void CObjMonsterSurveyDroneSprite::Release()
{
}

void CObjMonsterSurveyDroneSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
