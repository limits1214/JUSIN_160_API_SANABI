#include "pch.h"
#include "CObjMonsterDummyRobot.h"
#include "CObjMonsterDummyRobotSprite.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CObjCollisionRect.h"
#include "CTimeMgr.h"
#include "CObjPlayer2.h"
#include "CObjMonsterBullet.h"
CObjMonsterDummyRobot::CObjMonsterDummyRobot()
{
}

CObjMonsterDummyRobot::~CObjMonsterDummyRobot()
{
}

void CObjMonsterDummyRobot::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExcuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RESPAWN_START;

	m_bGrabbed = false;

	CObjMonsterDummyRobotSprite* pSprite = new CObjMonsterDummyRobotSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
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
	m_dwMoveToggleInterval = CTimeMgr::Get_Instance()->Get_Tick_Count();
}

/*

플레이어 찾기 루틴
좌우 이동

플레이어 찾으면 멈추고 총알 발사

*/
int CObjMonsterDummyRobot::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eAniState == AST_DEAD_END)
	{
		Set_Dead_Cascade();
	}
	DeltaUpdate();
	Apply_Gravity();

	if (m_eAniState == AST_RESPAWN_START
		|| m_eAniState == AST_RESPAWN_ING
		|| m_eAniState == AST_RESPAWN_END
		||
		m_eAniState == AST_DEAD_START
		|| m_eAniState == AST_DEAD_ING
		||
		m_eAniState == AST_EXCSTART_START
		|| m_eAniState == AST_EXCSTART_ING
		|| m_eAniState == AST_EXCSTART_END
		||
		m_eAniState == AST_EXCHOLDBACK_START
		|| m_eAniState == AST_EXCHOLDBACK_ING
		|| m_eAniState == AST_EXCHOLDBACK_END
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

			float detectLen = 300;

			if (distance < detectLen)
			{
				m_bPlayerFound = true;
			}
			else
			{
				m_bPlayerFound = false;
			}

			

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
		if (!m_bGrabbed)
		{
			if (m_eMoveDir == DIR_LEFT)
			{
				Move(180.f, m_fSpeed);
				if (m_eAniState != AST_LEFT_RUNNING_ING)
				{
					m_eAniState = AST_LEFT_RUNNING_START;
				}
			}
			else if (m_eMoveDir == DIR_RIGHT)
			{
				Move(0.f, m_fSpeed);
				if (m_eAniState != AST_RIGHT_RUNNING_ING)
				{
					m_eAniState = AST_RIGHT_RUNNING_START;
				}
			}
			else if (m_eMoveDir == DIR_UP)
			{
				if (m_eAniState != AST_LEFT_IDLE_ING)
				{
					m_eAniState = AST_LEFT_IDLE_START;
				}
			}
			else if (m_eMoveDir == DIR_DOWN)
			{
				if (m_eAniState != AST_RIGHT_IDLE_ING)
				{
					m_eAniState = AST_RIGHT_IDLE_START;
				}
			}
		}
	}

	CTimeMgr::Delay(&m_dwMoveToggleInterval, 1000,
		[&]()
		{
			if (m_eMoveDir == DIR_LEFT)
			{
				m_eMoveDir = DIR_UP;
			}
			else if (m_eMoveDir == DIR_RIGHT)
			{
				m_eMoveDir = DIR_DOWN;
			}
			else if (m_eMoveDir == DIR_UP)
			{
				m_eMoveDir = DIR_RIGHT;
			}
			else if (m_eMoveDir == DIR_DOWN)
			{
				m_eMoveDir = DIR_LEFT;
			}
		}
	);
	


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

						CObjMonsterBullet* pBullet = new CObjMonsterBullet;
						pBullet->Set_Angle(ang);
						pBullet->Initialize();
						pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
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

void CObjMonsterDummyRobot::Late_Update()
{
}

void CObjMonsterDummyRobot::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDummyRobot::Release()
{
}

void CObjMonsterDummyRobot::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
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

void CObjMonsterDummyRobot::Excuted(CObj* pPlayer, float fRad)
{
	m_eAniState = AST_DEAD_START;
	m_bExcuted = true;
}

void CObjMonsterDummyRobot::Grabbed(CObj* pPlayer)
{
	m_eAniState = AST_EXCSTART_START;;
	m_bGrabbed = true;
}

void CObjMonsterDummyRobot::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;
	m_dwTime = dwNowTime;

	m_fGravityDeltaSum += dwDelta;
}

void CObjMonsterDummyRobot::Apply_Gravity()
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
void CObjMonsterDummyRobot::Move(float fAngle, float fLength)
{
	m_tInfo.fX += cosf(fAngle * PI / 180.f) * fLength;
	m_tInfo.fY -= sinf(fAngle * PI / 180.f) * fLength;
}