#include "pch.h"
#include "CObjMonsterDaughterSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterDaughter.h"
CObjMonsterDaughterSprite::CObjMonsterDaughterSprite()
{
}

CObjMonsterDaughterSprite::~CObjMonsterDaughterSprite()
{
}

void CObjMonsterDaughterSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 30;


	m_eFrameKey = FKI_Spr_MONSTER_DAUGHTER_SHEET;
	m_eCurState = FSI_MONSTER_DAUGHTER_RIGHT_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterDaughterSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjMonsterDaughter* parent = dynamic_cast<CObjMonsterDaughter*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{

			case CObjMonsterDaughter::AST_RIGHT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DAUGHTER_RIGHT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDaughter::AST_RIGHT_IDLE_ING;
			}
			break;
			case CObjMonsterDaughter::AST_RIGHT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDaughter::AST_RIGHT_IDLE_END:
			{
			}
			break;

			case CObjMonsterDaughter::AST_LEFT_IDLE_START:
			{
				m_eCurState = FSI_MONSTER_DAUGHTER_LEFT_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDaughter::AST_LEFT_IDLE_ING;
			}
			break;
			case CObjMonsterDaughter::AST_LEFT_IDLE_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDaughter::AST_LEFT_IDLE_END:
			{
			}
			break;

			case CObjMonsterDaughter::AST_RIGHT_RUNNING_START:
			{
				m_eCurState = FSI_MONSTER_DAUGHTER_RIGHT_RUNNING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDaughter::AST_RIGHT_RUNNING_ING;
			}
			break;
			case CObjMonsterDaughter::AST_RIGHT_RUNNING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDaughter::AST_RIGHT_RUNNING_END:
			{
			}
			break;

			case CObjMonsterDaughter::AST_LEFT_RUNNING_START:
			{
				m_eCurState = FSI_MONSTER_DAUGHTER_LEFT_RUNNING;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjMonsterDaughter::AST_LEFT_RUNNING_ING;
			}
			break;
			case CObjMonsterDaughter::AST_LEFT_RUNNING_ING:
			{
				Move_Frame();
			}
			break;
			case CObjMonsterDaughter::AST_LEFT_RUNNING_END:
			{
			}
			break;

			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDaughterSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterDaughterSprite::Render(HDC hDC)
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

void CObjMonsterDaughterSprite::Release()
{
}

void CObjMonsterDaughterSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
