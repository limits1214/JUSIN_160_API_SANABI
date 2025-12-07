#include "pch.h"
#include "CObjUnstableKnockbackPlatformASprite.h"
#include "CTimeMgr.h"
#include "CObjBossFireBird.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"


#include "CObjUnstableKnockbackPlatformA.h"

CObjUnstableKnockbackPlatformASprite::CObjUnstableKnockbackPlatformASprite()
{
	Set_DbgName(_T("CObjUnstableKnockbackPlatformASprite"));
}

CObjUnstableKnockbackPlatformASprite::~CObjUnstableKnockbackPlatformASprite()
{
	Release();
}

void CObjUnstableKnockbackPlatformASprite::Initialize()
{
	//CObjCollisionRect::Initialize();
	//Set_Option(ERI_CLIMABLE);

	Set_UseMainScroll(true);
	m_tInfo.fCX = 264;
	m_tInfo.fCY = 112;


	m_eFrameKey = FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET;
	m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());

}

int CObjUnstableKnockbackPlatformASprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	{
		CObjUnstableKnockbackPlatformA* parent = dynamic_cast<CObjUnstableKnockbackPlatformA*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniState)
			{


			case CObjUnstableKnockbackPlatformA::IDLE_START:
			{
				m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLE;
				m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::IDLE_ING;
			}
				break;
			case CObjUnstableKnockbackPlatformA::IDLE_ING:
			{
				Move_Frame();
			}
				break;
			case CObjUnstableKnockbackPlatformA::IDLE_END:
				break;



			case CObjUnstableKnockbackPlatformA::DAMAGED_START:
			{
				m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_DAMAGED;
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::DAMAGED_ING;
			}
				break;
			case CObjUnstableKnockbackPlatformA::DAMAGED_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjUnstableKnockbackPlatformA::DAMAGED_END;
				}
			}
				break;
			case CObjUnstableKnockbackPlatformA::DAMAGED_END:
			{
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::IDLE_WARING_START;
			}
				break;



			case CObjUnstableKnockbackPlatformA::IDLE_WARING_START:
			{
				m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLEWARNING;
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::IDLE_WARING_ING;
			}
				break;
			case CObjUnstableKnockbackPlatformA::IDLE_WARING_ING:
			{
				Move_Frame();
			}
				break;
			case CObjUnstableKnockbackPlatformA::IDLE_WARING_END:
				break;

				

			case CObjUnstableKnockbackPlatformA::DAMAGED_WARNING_START:
			{
				m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_DAMAGEDWARNING;
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::DAMAGED_WARNING_ING;
			}
				break;
			case CObjUnstableKnockbackPlatformA::DAMAGED_WARNING_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniState = CObjUnstableKnockbackPlatformA::DAMAGED_WARNING_END;
				}
			}
				break;
			case CObjUnstableKnockbackPlatformA::DAMAGED_WARNING_END:
			{
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::IDLE_DOUBLEWARNING_START;
			}
				break;




			case CObjUnstableKnockbackPlatformA::IDLE_DOUBLEWARNING_START:
			{
				m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_IDLEDOUBLEWARNING;
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::IDLE_DOUBLEWARNING_ING;
			}
				break;
			case CObjUnstableKnockbackPlatformA::IDLE_DOUBLEWARNING_ING:
			{
				Move_Frame();
			}
				break;
			case CObjUnstableKnockbackPlatformA::IDLE_DOUBLEWARNING_END:
				break;



			case CObjUnstableKnockbackPlatformA::DESTROY_START:
			{
				m_eCurState = FSI_UNSTABLE_KNOCKBACK_PLATFORM_A_DESTROY;
				parent->m_eAniState = CObjUnstableKnockbackPlatformA::DESTROY_ING;
			}
				break;
			case CObjUnstableKnockbackPlatformA::DESTROY_ING:
			{
				Move_Frame();
			}
				break;
			case CObjUnstableKnockbackPlatformA::DESTROY_END:
				break;
			}
		}

	}

	

	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CObjUnstableKnockbackPlatformASprite::Late_Update()
{
	Motion_Change();
}

void CObjUnstableKnockbackPlatformASprite::Render(HDC hDC)
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

void CObjUnstableKnockbackPlatformASprite::Release()
{
}


void CObjUnstableKnockbackPlatformASprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}