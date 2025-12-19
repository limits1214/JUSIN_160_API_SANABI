#include "pch.h"
#include "CObjUnstableKnockbackPlatformA.h"
#include "CTimeMgr.h"



#include "pch.h"
#include "CObjBossFireBird.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CObjBossFireBirdWing.h"
#include "CObjBossFireBirdGun.h"
#include "CObjUnstableKnockbackPlatformASprite.h"
#include "CObjUnstableKnockbackPlatformABooster.h"
#include "CObjBossBullet.h"
#include "CObjBossShootExplode.h"
#include "CObjMonsterFloatingBomb.h"
#include "CObjBossBodySlap.h"

CObjUnstableKnockbackPlatformA::CObjUnstableKnockbackPlatformA()
{
	Set_DbgName(_T("CObjUnstableKnockbackPlatformA"));
}

CObjUnstableKnockbackPlatformA::~CObjUnstableKnockbackPlatformA()
{
	Release();
}

void CObjUnstableKnockbackPlatformA::Initialize()
{
	m_eAniState = IDLE_START;
	m_bComback = false;

	//CObjCollisionRect::Initialize();
	Set_Option(ERI_CLIMABLE);

	Set_UseMainScroll(true);
	m_tInfo.fCX = 260;
	m_tInfo.fCY = 110;

	CObjUnstableKnockbackPlatformASprite* pSprite = new CObjUnstableKnockbackPlatformASprite;
	pSprite->Initialize();
	pSprite->Set_Pos(0, 0);
	pSprite->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pSprite);

	CObjUnstableKnockbackPlatformABooster* pBooster = new CObjUnstableKnockbackPlatformABooster;
	pBooster->Initialize();
	pBooster->Set_Pos(0, 58);
	pBooster->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pBooster);


	m_bDestroyed = false;
}

int CObjUnstableKnockbackPlatformA::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	
	if (m_eAniState == DESTROY_ING)
	{
		m_tInfo.fY += 5.f;
	

		if (m_tInfo.fY > 1000)
		{
			m_eAniState = DESTROY_END;
		}
	}

	if (m_eAniState == DESTROY_END)
	{
		m_eAniState = IDLE_START;
		m_bComback = true;
	}

	if (m_bComback)
	{
		m_eAniState = IDLE_START;
		m_tInfo.fY -= 5.f;
		if (m_fComebackY > m_tInfo.fY - 5.f && m_fComebackY < m_tInfo.fY + 5.f)
		{
			m_tInfo.fY = m_fComebackY;
			m_bComback = false;
			Set_Option(ERI_CLIMABLE);
			m_bDestroyed = false;
		}
	}
	
	

	return OBJ_NOEVENT;
}

void CObjUnstableKnockbackPlatformA::Late_Update()
{
	
}

void CObjUnstableKnockbackPlatformA::Render(HDC hDC)
{
	
}

void CObjUnstableKnockbackPlatformA::Release()
{
}

void CObjUnstableKnockbackPlatformA::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	if (m_bDestroyed)
	{
		return;
	}

	CObjCollisionRect::On_Collision(pObj, eCollID, etc);
	CObjBossShootExplode* pShootExplode = dynamic_cast<CObjBossShootExplode*>(pObj);
	CObjBossBullet* pBossBullet = dynamic_cast<CObjBossBullet*>(pObj);
	CObjBossBodySlap* pBossBodySlap = dynamic_cast<CObjBossBodySlap*>(pObj);
	if (eCollID == COLL_RECT && pShootExplode != nullptr
		||
		eCollID == COLL_RECT && pBossBullet != nullptr
		||
		eCollID == COLL_RECT && pBossBodySlap != nullptr
		
		)
	{
		if (m_eAniState == IDLE_ING)
		{
			m_eAniState = DAMAGED_START;
		}
		else if (m_eAniState == IDLE_WARING_ING)
		{
			m_eAniState = DAMAGED_WARNING_START;
		}
		else if (m_eAniState == IDLE_DOUBLEWARNING_ING)
		{
			m_eAniState = DESTROY_START;
			Set_Option(ERI_NO_CLIMABLE);

			bool bCanSpawn = true;
			for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER))
			{
				auto pFloatingBomb = dynamic_cast<CObjMonsterFloatingBomb*>(pObj);
				if (pFloatingBomb != nullptr)
				{
					bCanSpawn = false;
					break;
				}
			}
			m_bDestroyed = true;
			if (bCanSpawn)
			{
				CObjMonsterFloatingBomb* pFloatingBomb = new CObjMonsterFloatingBomb;
				pFloatingBomb->Initialize();
				pFloatingBomb->Set_Pos(m_tInfo.fX ,m_tInfo.fY);
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBomb);
			}
		}
	}
}


void CObjUnstableKnockbackPlatformA::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}