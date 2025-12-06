#include "pch.h"
#include "CObjBossFireBirdGun.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjBossFireBird.h"


CObjBossFireBirdGun::CObjBossFireBirdGun()
{
	Set_DbgName(_T("CObjBossFireBirdGun"));
}

CObjBossFireBirdGun::~CObjBossFireBirdGun()
{
	Release();
}

void CObjBossFireBirdGun::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 440;
	m_tInfo.fCY = 78;
	//m_tInfo.fCY = 440;
	m_tInfo.fCY = 106;

	m_eFrameKey = FKI_Spr_BOSS_FirebirdGun_sheet;
	//m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTLOOP;
	//m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTEND;
	m_eCurState = FSI_END;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFireBirdGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	{
		CObjBossFireBird* parent = dynamic_cast<CObjBossFireBird*>(m_pParent);
		if (parent != nullptr)
		{
			DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
			switch (parent->m_eAniStateGun)
			{
			case CObjBossFireBird::ANI_STATE_GUN::GUN_IDLE:
			{
				m_eCurState = FSI_END;
			}
				break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTSTART_START:
			{
				m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTSTART;
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTSTART_ING;
				Move_Frame();
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTSTART_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTSTART_END;
				}
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTSTART_END:
			{
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTREADYLOOP_START;
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTREADYLOOP_START:
			{
				m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTREADYLOOP;
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTREADYLOOP_ING;
				Move_Frame();
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTREADYLOOP_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTREADYLOOP_END;
				}
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTREADYLOOP_END:
			{
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTLOOP_START;
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTLOOP_START:
			{
				m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTLOOP;
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTLOOP_ING;
				Move_Frame();
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTLOOP_ING:
			{
				Move_Frame();
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTLOOP_END:
			{
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTLOOP_KEEP:
			{
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTEND_START:
			{
				m_eCurState = FSI_BOSS_FIREBIRD_GUN_SHOOTEND;
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTEND_ING;
				Move_Frame();
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTEND_ING:
			{
				Move_Frame();
				int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
				if (m_tFrame.iStart == end)
				{
					parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTEND_END;
				}
			}
			break;
			case CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTEND_END:
			{
				parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUN_IDLE;
			}
			break;
			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjBossFireBirdGun::Late_Update()
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

void CObjBossFireBirdGun::Render(HDC hDC)
{
	HDC		hPlgDC = CBmpMgr::Get_Instance()->Find_Image(_T("PLG"));
	HDC		hTmpDC = CBmpMgr::Get_Instance()->Find_Image(_T("TMP"));
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

	/*
	

	BitBlt(hTmpDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		SRCCOPY);

	PlgBlt(hPlgDC,
		m_tPoint,
		hTmpDC,
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

	BitBlt(hTmpDC,
		0, 0,
		1920,
		1080,
		hResetDC,
		0,
		0,
		SRCCOPY);

	BitBlt(hPlgDC,
		0, 0,
		1920,
		1080,
		hResetDC,
		0,
		0,
		SRCCOPY);
	
	*/
}

void CObjBossFireBirdGun::Release()
{
}
void CObjBossFireBirdGun::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		if (m_eCurState == FSI_END)
		{
			m_eFrameKey = FKI_END;
			return;
		}
		else {
			m_eFrameKey = FKI_Spr_BOSS_FirebirdGun_sheet;
		}
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}