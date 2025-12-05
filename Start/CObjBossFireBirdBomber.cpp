#include "pch.h"
#include "CObjBossFireBirdBomber.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjBossFireBird.h"

CObjBossFireBirdBomber::CObjBossFireBirdBomber()
{
	Set_DbgName(_T("CObjBossFireBirdBomber"));
}

CObjBossFireBirdBomber::~CObjBossFireBirdBomber()
{
	Release();
}

void CObjBossFireBirdBomber::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 336;
	m_tInfo.fCY = 116;
	m_eFrameKey = FKI_Spr_BOSS_FirebirdBomber_sheet;
	m_eCurState = FSI_END;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFireBirdBomber::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	{
		CObjBossFireBird* parent = dynamic_cast<CObjBossFireBird*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniStateBomber)
			{
			case CObjBossFireBird::ANI_STATE_BOMBER::IDLE:
				m_eCurState = FSI_END;
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::OPENSTART:
			{
				m_eCurState = FSI_BOSS_FIREBIRD_BOMBER_OPENING;
				parent->m_eAniStateBomber = CObjBossFireBird::ANI_STATE_BOMBER::OPENING;
				Move_Frame();
			}
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::OPENING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniStateBomber = CObjBossFireBird::ANI_STATE_BOMBER::OPENEND;
				}
			}
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::OPENEND:
			{
				parent->m_eAniStateBomber = CObjBossFireBird::ANI_STATE_BOMBER::OPENKEEP;
			}
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::OPENKEEP:
			{
				m_eCurState = FSI_BOSS_FIREBIRD_BOMBER_OPENKEEP;
			}
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::CLOSESTART:

			{
				m_eCurState = FSI_BOSS_FIREBIRD_BOMBER_CLOSING;
				parent->m_eAniStateBomber = CObjBossFireBird::ANI_STATE_BOMBER::CLOSING;
				Move_Frame();
			}
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::CLOSING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniStateBomber = CObjBossFireBird::ANI_STATE_BOMBER::CLOSEEND;
				}
			}
				break;
			case CObjBossFireBird::ANI_STATE_BOMBER::CLOSEEND:
			{
				parent->m_eAniStateBomber = CObjBossFireBird::ANI_STATE_BOMBER::IDLE;
			}
				break;
			}
		}
	}

	__super::Update_Rect();
	

	return OBJ_NOEVENT;
}

void CObjBossFireBirdBomber::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBirdBomber::Render(HDC hDC)
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

void CObjBossFireBirdBomber::Release()
{
}

void CObjBossFireBirdBomber::Motion_Change()
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
			m_eFrameKey = FKI_Spr_BOSS_FirebirdBomber_sheet;
		}
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}