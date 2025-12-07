#include "pch.h"
#include "CObjBossFireBirdWing.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjBossFireBird.h"

CObjBossFireBirdWing::CObjBossFireBirdWing()
{
	Set_DbgName(_T("CObjBossFireBirdWing"));
}

CObjBossFireBirdWing::~CObjBossFireBirdWing()
{
	Release();
}

void CObjBossFireBirdWing::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 1304;
	m_tInfo.fCY = 234;
	//m_tInfo.fCY = 1304;

	m_eFrameKey = FKI_Spr_BOSS_FirebirdWing_sheet;

	m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_NEU;

	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFireBirdWing::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	{
		CObjBossFireBird* parent = dynamic_cast<CObjBossFireBird*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			if (parent->m_eAniStateBroken == CObjBossFireBird::ANI_STATE_BROKEN::NORMAL)
			{
				switch (parent->m_eAniStateWing)
				{
				case CObjBossFireBird::ANI_STATE_WING::NEU:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_NEU;
				}
					break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_NEUTOUP;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_END:
				{
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::UP_KEEP;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_KEEP:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_UPKEEP;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_UPTONEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_END:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_NEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_NEUTODOWN;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_END:
				{
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::DOWN_KEEP;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::DOWN_KEEP:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_DOWNKEEP;
				}
				break;

				case CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_DOWNTONEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_END:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_NORMAL_NEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU;
				}
				break;
				}
			}
			else if (parent->m_eAniStateBroken == CObjBossFireBird::ANI_STATE_BROKEN::BROKEN)
			{
				switch (parent->m_eAniStateWing)
				{
				case CObjBossFireBird::ANI_STATE_WING::NEU:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_NEU;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_NEUTOUP;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_UP_END:
				{
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::UP_KEEP;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_KEEP:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_UPKEEP;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_UPTONEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::UP_TO_NEU_END:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_NEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_NEUTODOWN;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::NEU_TO_DOWN_END:
				{
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::DOWN_KEEP;
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::DOWN_KEEP:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_DOWNKEEP;
				}
				break;

				case CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_START:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_DOWNTONEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_ING;
					Move_Frame();
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_ING:
				{
					Move_Frame();
					int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
					if (m_tFrame.iStart == end)
					{
						parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_END;
					}
				}
				break;
				case CObjBossFireBird::ANI_STATE_WING::DOWN_TO_NEU_END:
				{
					m_eCurState = FSI_BOSS_FIREBIRD_WING_BROKEN_NEU;
					parent->m_eAniStateWing = CObjBossFireBird::ANI_STATE_WING::NEU;
				}
				break;
				}
			}
		}

	}



	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjBossFireBirdWing::Late_Update()
{
	Motion_Change();

	CObjBossFireBird* parent = dynamic_cast<CObjBossFireBird*>(m_pParent);
	if (parent != nullptr)
	{
		float angle = parent->Get_Angle();
		float		fDistance = sqrtf((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) +
			(m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

		// ÁÂ »ó´Ü

		m_tPoint[0].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 135.f) * PI / 180.f));
		m_tPoint[0].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 135.f) * PI / 180.f));

		// ¿ì »ó´Ü

		m_tPoint[1].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 45.f) * PI / 180.f));
		m_tPoint[1].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 45.f) * PI / 180.f));

		// ÁÂ »ó´Ü

		m_tPoint[2].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 225.f) * PI / 180.f));
		m_tPoint[2].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 225.f) * PI / 180.f));
	}
}

void CObjBossFireBirdWing::Render(HDC hDC)
{
	HDC		hPlgDC = CBmpMgr::Get_Instance()->Find_Image(_T("PLG"));
	HDC		hResetDC = CBmpMgr::Get_Instance()->Find_Image(_T("RESET"));
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));

	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);

	/*BitBlt(hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		SRCCOPY);

	PlgBlt(hPlgDC,
		m_tPoint,
		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		NULL, NULL, NULL);

	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);

	BitBlt(hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0,0,
		SRCCOPY);*/
}

void CObjBossFireBirdWing::Release()
{
}

void CObjBossFireBirdWing::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}