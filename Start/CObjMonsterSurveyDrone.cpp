#include "pch.h"
#include "CObjMonsterSurveyDrone.h"
#include "CObjMonsterSurveyDroneSprite.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CObjPlayer2.h"
#include "CObjExplosionSprite.h"


CObjMonsterSurveyDrone::CObjMonsterSurveyDrone()
{
}

CObjMonsterSurveyDrone::~CObjMonsterSurveyDrone()
{
	Release();
}

void CObjMonsterSurveyDrone::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExcuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RIGHT_RESPAWN_START;

	CObjMonsterSurveyDroneSprite* pSprite = new CObjMonsterSurveyDroneSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);

	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_fLemnisDeltaSum = 0;
	m_bOriginSet = false;

	m_bTracing = true;

	m_bHovering = false;

	m_dwPhotoTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_bGrabbed = false;
}

int CObjMonsterSurveyDrone::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_eAniState == AST_RIGHT_RESPAWN_START
		|| m_eAniState == AST_RIGHT_RESPAWN_ING
		|| m_eAniState == AST_RIGHT_RESPAWN_END
		||
		m_eAniState == AST_LEFT_RESPAWN_START
		|| m_eAniState == AST_LEFT_RESPAWN_ING
		|| m_eAniState == AST_LEFT_RESPAWN_END
		)
	{
		return OBJ_NOEVENT;
	}

	if (!m_bOriginSet)
	{
		m_bOriginSet = true;
		m_fOriginX = m_tInfo.fX;
		m_fOriginY = m_tInfo.fY;
	}
	
	

	DeltaUpdate();

	CObjPlayer2* pPlayer = nullptr;
	if (m_pTarget != nullptr)
	{
		CObjPlayer2* _pPlayer = dynamic_cast<CObjPlayer2*>(m_pTarget);
		if (_pPlayer != nullptr)
		{
			pPlayer = _pPlayer;
		}
	}

	float traceX = 0;
	float traceY = 0;
	if (pPlayer != nullptr)
	{
		auto playerX = pPlayer->Get_Info()->fX;
		auto playerY = pPlayer->Get_Info()->fY;

		auto len = 1.f;

		auto tmpWidth = playerX - m_fOriginX;
		auto tmpHeight = (playerY - 40) - m_fOriginY;

		auto distance = sqrtf(tmpWidth * tmpWidth + tmpHeight * tmpHeight);

		// 쫒을때는 Min 까지
		float fTracingMinLen = 50;
		// 호버링중에는 Max까지 견딤
		float fTracingMaxLen = 200;

		if (m_bHovering)
		{
			if (distance > fTracingMaxLen)
			{
				auto rad = atan2f(tmpHeight, tmpWidth);
				traceX = cosf(rad) * len;
				traceY = sinf(rad) * len;

				m_bTracing = true;
				m_bHovering = false;
			}
			else
			{
			}
		}
		else
		{
			if (distance > fTracingMinLen)
			{
				auto rad = atan2f(tmpHeight, tmpWidth);
				traceX = cosf(rad) * len;
				traceY = sinf(rad) * len;

				m_bTracing = true;
				m_bHovering = false;
			}
			else
			{
				m_bTracing = false;
				m_bHovering = true;
			}
		}

		

		if (
			!(
				m_eAniState == AST_RIGHT_RESPAWN_START
				|| m_eAniState == AST_RIGHT_RESPAWN_ING
				|| m_eAniState == AST_RIGHT_RESPAWN_END
				||
				m_eAniState == AST_LEFT_RESPAWN_START
				|| m_eAniState == AST_LEFT_RESPAWN_ING
				|| m_eAniState == AST_LEFT_RESPAWN_END
				||
				m_eAniState == AST_RIGHT_EXCHOLDSTART_START
				|| m_eAniState == AST_RIGHT_EXCHOLDSTART_ING
				|| m_eAniState == AST_RIGHT_EXCHOLDSTART_END
				||
				m_eAniState == AST_LEFT_EXCHOLDSTART_START
				|| m_eAniState == AST_LEFT_EXCHOLDSTART_ING
				|| m_eAniState == AST_LEFT_EXCHOLDSTART_END
				||
				m_eAniState == AST_RIGHT_EXCHOLDBACK_START
				|| m_eAniState == AST_RIGHT_EXCHOLDBACK_ING
				|| m_eAniState == AST_RIGHT_EXCHOLDBACK_END
				||
				m_eAniState == AST_LEFT_EXCHOLDBACK_START
				|| m_eAniState == AST_LEFT_EXCHOLDBACK_ING
				|| m_eAniState == AST_LEFT_EXCHOLDBACK_END
				)
			)
		{
			if (tmpWidth > 0)
			{
				
				if (m_bHovering)
				{
					CTimeMgr::Delay(&m_dwPhotoTime, 2000,
						[&]()
						{
							m_eAniState = AST_RIGHT_PHOTO_START;
						}
					);
				}
				else
				{
					if (m_eAniState != AST_RIGHT_IDLE_ING)
					{
						m_eAniState = AST_RIGHT_IDLE_START;

					}
				}
				
			}
			else
			{
				
				if (m_bHovering)
				{
					CTimeMgr::Delay(&m_dwPhotoTime, 2000,
						[&]()
						{
							m_eAniState = AST_LEFT_PHOTO_START;
						}
					);
				}
				else
				{
					if (m_eAniState != AST_LEFT_IDLE_ING)
					{
						m_eAniState = AST_LEFT_IDLE_START;

					}
				}
				
			}
		}
		
		
	}
	
	float lemnisX = 0;
	float lemnisY = 0;

	float a = 20;
	float t = m_fLemnisDeltaSum;
	lemnisX = a * cosf(t) / (1.0f + sinf(t) * sinf(t));
	lemnisY = a * sinf(t) * cosf(t) / (1.0f + sinf(t) * sinf(t));


	m_fOriginX += traceX;
	m_fOriginY += traceY;


	if (!m_bGrabbed)
	{
		m_tInfo.fX = m_fOriginX + lemnisX + traceX;
		m_tInfo.fY = m_fOriginY + lemnisY + traceY;
	}
	

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterSurveyDrone::Late_Update()
{
}

void CObjMonsterSurveyDrone::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterSurveyDrone::Release()
{
}

void CObjMonsterSurveyDrone::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterSurveyDrone::Excuted(CObj* pPlayer, float fRad)
{
	m_bExcuted = true;
	Set_Dead_Cascade();
	CObjExplosionSprite* pExplosionSprite = new CObjExplosionSprite;
	pExplosionSprite->Set_Option(0);
	pExplosionSprite->Initialize();
	pExplosionSprite->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pExplosionSprite);
}

void CObjMonsterSurveyDrone::Grabbed(CObj* pPlayer)
{
	m_eAniState = AST_RIGHT_EXCHOLDSTART_START;
	m_bGrabbed = true;
}


void CObjMonsterSurveyDrone::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;
	m_dwTime = dwNowTime;

	m_fLemnisDeltaSum += dwDelta;
}