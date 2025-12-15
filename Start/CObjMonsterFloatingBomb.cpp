#include "pch.h"
#include "CObjMonsterFloatingBomb.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterFloatingBombSprite.h"
#include "CObjMgr.h"
#include "CObjMouse.h"
#include "CScrollMgr.h"
#include "CObjPlayer.h"
#include "CObjMonsterFloatingBombHugeExplodeSprite.h"
#include "CObjBossFireBird.h"
#include "CCollisionMgr.h"
#include "CObjUnstableKnockbackPlatformA.h"

CObjMonsterFloatingBomb::CObjMonsterFloatingBomb()
{
	Set_DbgName(_T("CObjMonsterFloatingBomb"));
}

CObjMonsterFloatingBomb::~CObjMonsterFloatingBomb()
{
	Release();
}

void CObjMonsterFloatingBomb::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	CObjMonsterFloatingBombSprite* pPltSprite = new CObjMonsterFloatingBombSprite;
	pPltSprite->Initialize();
	pPltSprite->Set_Parent(this);
	pPltSprite->Set_Pos(12, 5);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pPltSprite);

	m_bExcuted = false;

	m_bAirMonster = true;
	m_iAngle = 45;

	m_bExploded = false;
}

int CObjMonsterFloatingBomb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bExcuted)
	{
		m_tInfo.fX += cosf(m_fExcutedRad) * 3;
		m_tInfo.fY += sinf(m_fExcutedRad) * 3;
	}
	else
	{
		m_tInfo.fX += cosf((float)m_iAngle * PI / 180.f) * 3;
		m_tInfo.fY -= sinf((float)m_iAngle * PI / 180.f) * 3;
	}



	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjMonsterFloatingBomb::Late_Update()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (m_tRect.top + iScrollY < 0)
	{
		// 바닥 충돌
		if (m_iAngle == 45)
		{
			m_iAngle = 315;
		}
		else if (m_iAngle == 135)
		{
			m_iAngle = 225;
		}
	}
	else if (m_tRect.bottom + iScrollY > WINCY)
	{
		// 위 충돌
		if (m_iAngle == 315)
		{
			m_iAngle = 45;
		}
		else if (m_iAngle == 225)
		{
			m_iAngle = 135;
		}
	}
	else if (m_tRect.left + iScrollX < 0)
	{
		// 오른쪽 충돌
		if (m_iAngle == 225)
		{
			m_iAngle = 315;
		}
		else if (m_iAngle == 135)
		{
			m_iAngle = 45;
		}
	}
	else if (m_tRect.right + iScrollX > WINCX)
	{
		// 왼쪽 충돌
		if (m_iAngle == 45)
		{
			m_iAngle = 135;
		}
		else if (m_iAngle == 315)
		{
			m_iAngle = 225;
		}
	}
}

void CObjMonsterFloatingBomb::Render(HDC hDC)
{
	
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterFloatingBomb::Release()
{
}

void CObjMonsterFloatingBomb::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	CObjBossFireBird* pBoss = dynamic_cast<CObjBossFireBird*>(pObj);
	if (eCollID == COLL_RECT && pBoss != nullptr)
	{
		if (m_bExcuted && !m_bExploded)
		{
			Explode();
			pBoss->Set_Knockback(true);
			pBoss->Set_KnockbackAngle(m_fExcutedRad * 180.f / PI * -1.f);
			
			return;
		}

	}

	CObjUnstableKnockbackPlatformA* pPlatform = dynamic_cast<CObjUnstableKnockbackPlatformA*>(pObj);
	COLL_ETC_RECT_EX* pRectExCollEtc = static_cast<COLL_ETC_RECT_EX*>(etc);
	if (eCollID == COLL_RECT_EX && pPlatform != nullptr)
	{
		COLL_ETC_RECT_EX rectExCollEtc = *pRectExCollEtc;
		float fDistance = rectExCollEtc.fDistance;
		
		switch (rectExCollEtc.eDir)
		{
		case DIR_UP:
		{
			// 플레이어가 바닥에 닿은 경우 밀어준다.
			//Move(90.f, fDistance);
			if (m_iAngle == 315)
			{
				m_iAngle = 45;
			}
			else if (m_iAngle == 225)
			{
				m_iAngle = 135;
			}
		}
		break;
		case DIR_DOWN:
		{
			// 플레이어가 위에 닿은 경우 밀어준다.
			//Move(270.f, fDistance);

			if (m_iAngle == 45)
			{
				m_iAngle = 315;
			}
			else if (m_iAngle == 135)
			{
				m_iAngle = 225;
			}

		}
		break;
		case DIR_LEFT:
		{
			// 플레이어가 왼쪽에 닿은 경우밀어준다.
			//Move(180.f, fDistance);

			if (m_iAngle == 45)
			{
				m_iAngle = 135;
			}
			else if (m_iAngle == 315)
			{
				m_iAngle = 225;
			}
		}
		break;
		case DIR_RIGHT:
		{
			// 플레이어가 오른쪽에 닿은 경우 밀어준다.
			//Move(0.f, fDistance);

			if (m_iAngle == 225)
			{
				m_iAngle = 315;
			}
			else if (m_iAngle == 135)
			{
				m_iAngle = 45;
			}
		}
		break;
		}
		
	}
}

void CObjMonsterFloatingBomb::Excuted(CObj* pPlayer, float fRad)
{
	m_bExcuted = true;
	m_fExcutedRad = fRad + PI;
}

void CObjMonsterFloatingBomb::Grabbed(CObj* pPlayer)
{
}

void CObjMonsterFloatingBomb::Explode()
{
	m_bExploded = true;
	Set_Dead_Cascade();

	CObjMonsterFloatingBombHugeExplodeSprite* pFloatingBombExplode = new CObjMonsterFloatingBombHugeExplodeSprite;
	pFloatingBombExplode->Initialize();
	pFloatingBombExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBombExplode);
}
