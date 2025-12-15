#include "pch.h"
#include "CObjMonsterDefender.h"
#include "CObjMonsterDefenderSprite.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CObjPlayer2.h"
#include "CObjMonsterDefenderBullet.h"
#include "CObjCollisionRect.h"
#include "CCollisionMgr.h"
#include "CSoundMgr.h"


CObjMonsterDefender::CObjMonsterDefender()
{
}

CObjMonsterDefender::~CObjMonsterDefender()
{
}

void CObjMonsterDefender::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExcuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RIGHT_SET_START;

	m_bGrabbed = false;

	CObjMonsterDefenderSprite* pSprite = new CObjMonsterDefenderSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, -10);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);

	m_bGravity = true;
	m_fGravityDeltaSum = 0;

	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_dwShootInterval = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_dwFireRateInterval = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_bPlayerFound = false;
	m_bFire = false;

	m_fSpeed = 2.f;
	m_eMoveDir = DIR_LEFT;


}

int CObjMonsterDefender::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	DeltaUpdate();
	Apply_Gravity();

	if (m_eAniState == AST_RIGHT_DEAD_END)
	{
		Set_Dead_Cascade();
	}

	if (m_eAniState == AST_RIGHT_SET_START
		|| m_eAniState == AST_RIGHT_SET_ING
		|| m_eAniState == AST_RIGHT_SET_END
		||
		m_eAniState == AST_LEFT_SET_START
		|| m_eAniState == AST_LEFT_SET_ING
		|| m_eAniState == AST_LEFT_SET_END
		||
		m_eAniState == AST_RIGHT_EXCHOLDBACK_START
		|| m_eAniState == AST_RIGHT_EXCHOLDBACK_ING
		|| m_eAniState == AST_RIGHT_EXCHOLDBACK_END
		||
		m_eAniState == AST_RIGHT_DEAD_START
		|| m_eAniState == AST_RIGHT_DEAD_ING
		)
	{
		return OBJ_NOEVENT;
	}
	

	if (m_pTarget != nullptr)
	{
		CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(m_pTarget);
		if (pPlayer != nullptr)
		{
			float playerX = pPlayer->Get_Info()->fX;
			float playerY = pPlayer->Get_Info()->fY;
			float tmpWidth = playerX - m_tInfo.fX;
			float tmpHeight = playerY - m_tInfo.fY;
			float distance = sqrtf(tmpWidth * tmpWidth + tmpHeight * tmpHeight);

			float detectLen = 500;

			if (distance < detectLen)
			{
				m_bPlayerFound = true;
			}
			else
			{
				m_bPlayerFound = false;
			}


			if (!m_bGrabbed)
			{
				if (m_bPlayerFound)
				{
					if (m_tInfo.fX > playerX)
					{
						if (m_eAniState != AST_LEFT_IDLE_ING)
						{
							m_eAniState = AST_LEFT_IDLE_START;
						}
					}
					else
					{
						if (m_eAniState != AST_RIGHT_IDLE_ING)
						{
							m_eAniState = AST_RIGHT_IDLE_START;
						}
					}
				}
			}
		}
	}


	if (m_bPlayerFound)
	{
		CTimeMgr::Delay(&m_dwShootInterval, 1000,
			[&]()
			{
				m_bFire = true;
				m_iFireCnt = 1;
			}
		);

	}
	else
	{
		//if (!m_bGrabbed)
		//{
		//	if (m_eMoveDir == DIR_LEFT)
		//	{
		//		if (m_eAniState != AST_LEFT_RUNNING_ING)
		//		{
		//			m_eAniState = AST_LEFT_RUNNING_START;
		//		}
		//	}
		//	else if (m_eMoveDir == DIR_RIGHT)
		//	{
		//		if (m_eAniState != AST_RIGHT_RUNNING_ING)
		//		{
		//			m_eAniState = AST_RIGHT_RUNNING_START;
		//		}
		//	}
		//	else if (m_eMoveDir == DIR_UP)
		//	{
		//		if (m_eAniState != AST_LEFT_IDLE_ING)
		//		{
		//			m_eAniState = AST_LEFT_IDLE_START;
		//		}
		//	}
		//	else if (m_eMoveDir == DIR_DOWN)
		//	{
		//		if (m_eAniState != AST_RIGHT_IDLE_ING)
		//		{
		//			m_eAniState = AST_RIGHT_IDLE_START;
		//		}
		//	}
		//}
	}


	if (!m_bGrabbed && m_bFire)
	{
		CTimeMgr::Delay(&m_dwFireRateInterval, 200,
			[&]()
			{
				if (m_pTarget != nullptr)
				{
					CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(m_pTarget);
					if (pPlayer != nullptr)
					{
						float playerX = pPlayer->Get_Info()->fX;
						float playerY = pPlayer->Get_Info()->fY;
						float tmpWidth = playerX - m_tInfo.fX;
						float tmpHeight = playerY - m_tInfo.fY;
						float tmpRad = atan2f(tmpHeight, tmpWidth);
						float ang = tmpRad * 180.f / PI * -1;

						CObjMonsterDefenderBullet* pBullet = new CObjMonsterDefenderBullet;
						//pBullet->Set_Angle(ang);
						pBullet->Set_Target(m_pTarget);
						pBullet->Initialize();
						pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
					
						CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_DEFENDER_SHOOT);
						CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap1_Defender_Shoot.wav", SOUND_SFX_DEFENDER_SHOOT, 1.f);
					}
				}
				--m_iFireCnt;
				if (m_iFireCnt <= 0)
				{
					m_bFire = false;
				}
			});
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDefender::Late_Update()
{
}

void CObjMonsterDefender::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDefender::Release()
{
}

void CObjMonsterDefender::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	CObjCollisionRect* pRect = dynamic_cast<CObjCollisionRect*>(pObj);
	COLL_ETC_RECT_EX* pRectExCollEtc = static_cast<COLL_ETC_RECT_EX*>(etc);
	if (
		eCollID == COLL_RECT_EX && pRect != nullptr && pRectExCollEtc != nullptr
		)
	{
		COLL_ETC_RECT_EX rectExCollEtc = *pRectExCollEtc;
		float fDistance = rectExCollEtc.fDistance;
		int iRectOpt = pRect->Get_Option();

		if (iRectOpt == ERI_CLIMABLE || iRectOpt == ERI_NO_CLIMABLE)
		{
			switch (rectExCollEtc.eDir)
			{
			case DIR_UP:
			{
				// 플레이어가 바닥에 닿은 경우 밀어준다.
				Move(90.f, fDistance);

				// 중력 델타를 0으로 변경
				m_bGravity = true;
				m_fGravityDeltaSum = 0;
			}
			break;
			case DIR_DOWN:
			{
				// 플레이어가 위에 닿은 경우 밀어준다.
				Move(270.f, fDistance);
			}
			break;
			case DIR_LEFT:
			{
				// 플레이어가 왼쪽에 닿은 경우밀어준다.
				Move(180.f, fDistance);
			}
			break;
			case DIR_RIGHT:
			{
				// 플레이어가 오른쪽에 닿은 경우 밀어준다.
				Move(0.f, fDistance);
			}
			break;
			}
		}

	}
}

void CObjMonsterDefender::Excuted(CObj* pPlayer, float fRad)
{
	m_eAniState = AST_RIGHT_DEAD_START;
	m_bExcuted = true;

	//SFX_Ene_Explosion.wav
	CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_ENE_EXPLOSION);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Ene_Explosion.wav", SOUND_SFX_ENE_EXPLOSION, 1.f);
}

void CObjMonsterDefender::Grabbed(CObj* pPlayer)
{
	m_eAniState = AST_RIGHT_EXCHOLDBACK_START;
	m_bGrabbed = true;
}


void CObjMonsterDefender::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;
	m_dwTime = dwNowTime;

	m_fGravityDeltaSum += dwDelta;
}

void CObjMonsterDefender::Apply_Gravity()
{
	if (m_bGravity)
	{
		float fGravityDeltaMax = 1.5f;
		if (m_fGravityDeltaSum > fGravityDeltaMax)
		{
			m_fGravityDeltaSum = fGravityDeltaMax;
		}

		float fTmpG = 9.81f * (m_fGravityDeltaSum * m_fGravityDeltaSum) * 0.5f;
		float fScaledTmpY = fTmpG * 7.0f;

		Move(270.f, fScaledTmpY);
	}
}

void CObjMonsterDefender::Move(float fAngle, float fLength)
{
	m_tInfo.fX += cosf(fAngle * PI / 180.f) * fLength;
	m_tInfo.fY -= sinf(fAngle * PI / 180.f) * fLength;
}