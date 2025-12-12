#include "pch.h"
#include "CObjMonsterDummyFloaterSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterDummyFloater.h"
CObjMonsterDummyFloaterSprite::CObjMonsterDummyFloaterSprite()
{
}

CObjMonsterDummyFloaterSprite::~CObjMonsterDummyFloaterSprite()
{
}

void CObjMonsterDummyFloaterSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 59;
	m_tInfo.fCY = 67;


	m_eFrameKey = FKI_Spr_MONSTER_DUMMYFLOATER_SHEET;
	m_eCurState = FSI_MONSTER_DUMMYFLOATER_RESPAWN;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterDummyFloaterSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterDummyFloater* parent = dynamic_cast<CObjMonsterDummyFloater*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterDummyFloater::AST_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYFLOATER_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyFloater::AST_IDLE_ING;
			}
			break;
			case CObjMonsterDummyFloater::AST_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyFloater::AST_IDLE_END:
			{
			}
			break;


			case CObjMonsterDummyFloater::AST_RESPAWN_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYFLOATER_RESPAWN;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyFloater::AST_RESPAWN_ING;
			}
			break;
			case CObjMonsterDummyFloater::AST_RESPAWN_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDummyFloater::AST_RESPAWN_END;
				}
			}
			break;
			case CObjMonsterDummyFloater::AST_RESPAWN_END:
			{
				parent->m_eAniState = CObjMonsterDummyFloater::AST_IDLE_START;
			}
			break;


			case CObjMonsterDummyFloater::AST_EXCSTART_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYFLOATER_EXCSTART;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyFloater::AST_EXCSTART_ING;
			}
			break;
			case CObjMonsterDummyFloater::AST_EXCSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjMonsterDummyFloater::AST_EXCSTART_END;
				}
			}
			break;
			case CObjMonsterDummyFloater::AST_EXCSTART_END:
			{
				parent->m_eAniState = CObjMonsterDummyFloater::AST_EXCHOLDBACK_START;
			}
			break;


			case CObjMonsterDummyFloater::AST_EXCHOLDBACK_START:
			{
				m_eCurState = FSI_MONSTER_DUMMYFLOATER_EXCHOLDEDBACK;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDummyFloater::AST_EXCHOLDBACK_ING;
			}
			break;
			case CObjMonsterDummyFloater::AST_EXCHOLDBACK_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDummyFloater::AST_EXCHOLDBACK_END:
			{
			}
			break;

			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDummyFloaterSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterDummyFloaterSprite::Render(HDC hDC)
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

void CObjMonsterDummyFloaterSprite::Release()
{
}

void CObjMonsterDummyFloaterSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
