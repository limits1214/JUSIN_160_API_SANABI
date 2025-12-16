#include "pch.h"
#include "CObjBossFireBird.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CObjBossFireBirdWing.h"
#include "CObjBossFireBirdGun.h"
#include "CObjBossFireBirdBomber.h"
#include "CObjBossFirebirdBody.h"
#include "CKeyMgr.h"
#include "CObjPlayer2.h"
#include "CObjBossBodySlapAlert.h"
#include "CObjBossBullet.h"
#include "CObjClusterBombExplode.h"
#include "CObjBossClusterAim.h"
#include "CObjBossBodySlap.h"
#include "CObjBossBackHeli.h"
#include "CObjBossFirebirdEndSprite.h"
#include "CSoundMgr.h"

CObjBossFireBird::CObjBossFireBird()
	: m_pClusterAim(nullptr)
{
    Set_DbgName(_T("CObjBossFireBird"));
}

CObjBossFireBird::~CObjBossFireBird()
{
    Release();
}

void CObjBossFireBird::Initialize()
{
	m_bBossHideToDown = false;
	m_bBossShowToUp = false;
	m_iTestCnt = 0;

    Set_UseMainScroll(true);
    m_tInfo.fCX = 300;
    m_tInfo.fCY = 300;

	m_fSpeed = 2.f;

	m_fAngle = 0.f;
	m_fPlayerFollowAngle = 0.f;

	m_eAniStateBomber = ANI_STATE_BOMBER::IDLE;
	m_eAniStateGun = ANI_STATE_GUN::GUN_IDLE;
	m_eAniStateBroken = ANI_STATE_BROKEN::NORMAL;
	m_eAniStateWing = ANI_STATE_WING::NEU;

	m_eState = STATE::PLAYER_FOLLOW_START;

	m_dwBombingIntervalDelay1 = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_dwBombingEndDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_dwBodySlapAlertDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_dwBodySlapEndDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_fClusterAimSpeed = 3.f;
	m_pClusterAim = nullptr;


	m_bRetreat = false;
	m_dwRetreatDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_iKnockbackedCnt = 0;
	m_iKnockBackFrameCnt = 0;
	m_bKnockBack = false;
	m_fKnockBackAngle = 0.f;

	m_iDamagedCnt = 0;

	m_bPhase2Start = false;
	m_bPhase2Pend = false;

	m_bEndStart = false;
	m_bEnd = false;

	CObjBossFireBirdBomber* pBomber = new CObjBossFireBirdBomber;
	pBomber->Initialize();
	pBomber->Set_Pos(0, 120);
	pBomber->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBomber);

	CObjBossFireBirdWing* pWing = new CObjBossFireBirdWing;
	pWing->Initialize();
	pWing->Set_Pos(0, -40);
	pWing->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWing);

	CObjBossFirebirdBody* pBody = new CObjBossFirebirdBody;
	pBody->Initialize();
	pBody->Set_Pos(0, 0);
	pBody->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBody);

	CObjBossFireBirdGun* pGun = new CObjBossFireBirdGun;
	pGun->Initialize();
	pGun->Set_Pos(-2, -30);
	pGun->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pGun);
}

int CObjBossFireBird::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

	for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
	{
		CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
		if (pPlayer != nullptr)
		{
			
			float playerX = pPlayer->Get_Info()->fX;
			float playerY = pPlayer->Get_Info()->fY;


			float width = m_tInfo.fX - playerX;
			float height = m_tInfo.fY - playerY;
			float distance = sqrtf(width * width + height * height);
			if (distance > 1000)
			{
				m_fSpeed = 20.f;
			}
			if (distance > 700)
			{
				m_fSpeed = 6.f;
			}
			if (distance > 300)
			{
				m_fSpeed = 3.f;
			}
			else
			{
				m_fSpeed = 2.;
			}
			
			break;
		}
	}


	//if (m_bPhase2Pend)
	//{
	//	return OBJ_NOEVENT;
	//}
	

	if (!m_bEnd )
	{
		if (m_bKnockBack)
		{
			--m_iKnockBackFrameCnt;
			m_tInfo.fX += cosf(m_fKnockBackAngle * PI / 180.f) * 10.f;
			m_tInfo.fY -= sinf(m_fKnockBackAngle * PI / 180.f) * 10.f;
			if (m_iKnockBackFrameCnt < 0)
			{
				m_bKnockBack = false;

				if (m_bPhase2Start)
				{
					//m_bPhase2Start = false;
					//m_bPhase2Pend = true;
					//CObjBossBackHeli* pBackHeli = new CObjBossBackHeli;
					//pBackHeli->Initialize();
					//pBackHeli->Set_Pos(WINCX , WINCY);
					//pBackHeli->Set_MoveTarget(0, 0);
					//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBackHeli);

					//CTimeMgr::Get_Instance()->Set_Timer(
					//	[=]() {
					//		pBackHeli->Set_Dead();
					//		m_bPhase2Pend = false;
					//		m_eAniStateBroken = BROKEN;
					//		//m_fSpeed = 2.f;
					//	}, 3000);
				}
				else if (m_bEndStart)
				{
					m_bEnd = true;
					CObjBossFirebirdEndSprite* pFireBirdEnd = new CObjBossFirebirdEndSprite;
					pFireBirdEnd->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pFireBirdEnd);
				}
			}
		}
		else
		{
			m_fPlayerFollowAngle += 1.f;
			State_Update();
		}
	}

	


    __super::Update_Rect();
	
    return OBJ_NOEVENT;
}

void CObjBossFireBird::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBird::Render(HDC hDC)
{
	// Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjBossFireBird::Release()
{
}

void CObjBossFireBird::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}


void CObjBossFireBird::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}

void CObjBossFireBird::Test_Key_Input()
{
	//if (m_eAniStateWing == DOWN_KEEP )
	//{
	//	m_eAniStateWing = ANI_STATE_WING::DOWN_TO_NEU_START;
	//}
	//else if (m_eAniStateWing == UP_KEEP)
	//{
	//	m_eAniStateWing = ANI_STATE_WING::UP_TO_NEU_START;
	//}
 
	//»ó½Â
	if (CKeyMgr::Get_Instance()->Key_Pressing('T'))
	{
		m_tInfo.fY -= m_fSpeed;

		if (m_eAniStateWing == NEU)
		{
			m_eAniStateWing = ANI_STATE_WING::NEU_TO_UP_START;
		}
		else if (m_eAniStateWing == UP_KEEP)
		{

		}
		else if (m_eAniStateWing == DOWN_KEEP)
		{
			m_eAniStateWing = ANI_STATE_WING::DOWN_TO_NEU_START;
		}
	}

	// ÇÏ°­
	if (CKeyMgr::Get_Instance()->Key_Pressing('G'))
	{
		m_tInfo.fY += m_fSpeed;

		if (m_eAniStateWing == NEU)
		{
			m_eAniStateWing = ANI_STATE_WING::NEU_TO_DOWN_START;
		}
		else if (m_eAniStateWing == UP_KEEP)
		{
			m_eAniStateWing = ANI_STATE_WING::UP_TO_NEU_START;
		}
		else if (m_eAniStateWing == DOWN_KEEP)
		{

		}
	}




	// ÁÂÃø
	if (CKeyMgr::Get_Instance()->Key_Pressing('F'))
	{
		m_tInfo.fX -= m_fSpeed;

		if (m_fAngle < 5)
			m_fAngle += 1.f;
	}

	// ¿ìÃø
	if (CKeyMgr::Get_Instance()->Key_Pressing('H'))
	{
		m_tInfo.fX += m_fSpeed;
		if (m_fAngle > -5)
			m_fAngle -= 1.f;
	}

	// ÆøÅºÃ¢ ¿­±â
	// Æ÷ÅºÃ¢ ´Ý±â
	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		if (m_eAniStateBomber == IDLE)
		{
			m_eAniStateBomber = OPENSTART;
		}
		else if (m_eAniStateBomber = OPENKEEP)
		{
			m_eAniStateBomber = CLOSESTART;
		}
	}

	// ÃÑ ²¨³»¼­ ¹ß»ç
	// ÃÑ ¹ß»çÁßÁöÈÄ Áý¾î³Ö±â
	// idle -> gunshootstart -> gunshootreadyloop -> gunshootloop
	//
	// gunshootend -> idle
	if (CKeyMgr::Get_Instance()->Key_Down('Y'))
	{
		if (m_eAniStateGun == IDLE)
		{
			m_eAniStateGun = GUNSHOOTSTART_START;
		}
		else if (m_eAniStateGun = GUNSHOOTLOOP_ING)
		{
			m_eAniStateGun = GUNSHOOTEND_START;
		}
	}

	// ¹Ùµð½½·¦ ¾Ë·¯Æ®
	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		for (auto*& pObj: *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (pPlayer != nullptr)
			{
				float playerY = pPlayer->Get_Info()->fY;
				
				auto xlen =  ((WINCX >> 1) + 224 * 6) - ((WINCX >> 1) - 224 * 6);
				auto alertXSize = 35;
				int total = xlen / alertXSize;

				for (int i = 0; i < total; ++i)
				{
					auto offset = ((WINCX >> 1) - 224 * 6) + i * alertXSize;
					CObjBossBodySlapAlert* pAlert = new CObjBossBodySlapAlert;
					pAlert->Initialize();
					pAlert->Set_Pos(offset, playerY);
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pAlert);
				}
				
			}
		}
	}

	// 360µµ ÃÑ¾Ë
	if (CKeyMgr::Get_Instance()->Key_Down('B'))
	{

		float targetX = (WINCX >> 1) + 100;
		float targetY = (WINCY >> 1) + 100;
		float bulletLen = 15;

		CObjClusterBombExplode* pExplode = new CObjClusterBombExplode;
		pExplode->Initialize();
		pExplode->Set_Pos(targetX, targetY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pExplode);

		for (int i = 0; i < bulletLen; ++i)
		{
			//CObjClusterBombExplode
			CObjBossBullet* pBullet = new CObjBossBullet;
			pBullet->Set_Option(0);
			pBullet->Initialize();
			pBullet->Set_Angle(rand());
			pBullet->Set_Pos(targetX, targetY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
		}
	}
}

void CObjBossFireBird::State_Update()
{
	switch (m_eState)
	{
	case PLAYER_FOLLOW_START:
	{
		m_eState = PLAYER_FOLLOW_ING;

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_eState = PLAYER_FOLLOW_END;
			}, 5000);
	}
	break;

	case PLAYER_FOLLOW_ING:
	{
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (pPlayer != nullptr)
			{
				DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
				float playerX = pPlayer->Get_Info()->fX;
				float playerY = pPlayer->Get_Info()->fY;


				float newX = playerX + cosf(m_fPlayerFollowAngle * PI / 180.f) * 100;
				float newY = playerY - sinf(m_fPlayerFollowAngle * PI / 180.f) * 100;

				float width = m_tInfo.fX - newX;
				float height = m_tInfo.fY - newY;

				float rad = atan2f(height, width) + PI;
				float ang = rad * 180.f / PI;
				float ang2 = ang * -1;
				Move(ang2, m_fSpeed);
			}
		}
		

	}
	break;

	case PLAYER_FOLLOW_END:
	{
		if (m_iTestCnt % 4 == 0)
		{
			m_eState = PATTERN1_BOMBING_START;
		}
		else if (m_iTestCnt % 4 == 1)
		{
			m_eState = PATTERN2_SHOOTING_START;
		}
		else if (m_iTestCnt % 4 == 2)
		{
			m_eState = PATTERN3_BODYSLAP_START;
		}
		else if (m_iTestCnt % 4 == 3)
		{
			m_eState = PATTERN4_CLUSTERBOMB_START;
		}
		else if (m_iTestCnt >= 4)
		{
			m_eState = PLAYER_FOLLOW_START;
		}
		++m_iTestCnt;

	}
	break;

	case PATTERN1_BOMBING_START:
	{
		m_eState = PATTERN1_BOMBING_ING;
		m_eAniStateBomber = OPENSTART;
		m_dwBombingEndDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();
		m_bBombingStart = false;
		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bBombingStart = true;
			}, 1000);
	}
	break;

	case PATTERN1_BOMBING_ING:
	{
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (pPlayer != nullptr)
			{
				DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
				float playerX = pPlayer->Get_Info()->fX;
				float playerY = pPlayer->Get_Info()->fY;

				float newX = playerX + cosf(m_fPlayerFollowAngle * PI / 180.f) * 100;
				float newY = (playerY - 450.f) - sinf(m_fPlayerFollowAngle * PI / 180.f) * 100;

				float width = m_tInfo.fX - newX;
				float height = m_tInfo.fY - newY;

				float rad = atan2f(height, width) + PI;
				float ang = rad * 180.f / PI;
				float ang2 = ang * -1;

				Move(ang2, m_fSpeed);

				if (m_bBombingStart)
				{
					CTimeMgr::Delay(&m_dwBombingIntervalDelay1, (500), [&]() {
						CObjBossBullet* pBossBullet = new CObjBossBullet;
						pBossBullet->Set_Option(1);
						pBossBullet->Initialize();
						pBossBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY + 150);
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBossBullet);

						CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BOMBING_START);
						CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingStart.wav", SOUND_SFX_BOMBING_START, 1.f);
						});
				}
				

				CTimeMgr::Delay(&m_dwBombingEndDelay, (8000), [&]() {
					m_eState = PATTERN1_BOMBING_END;
					});
			}
		}
	}
	break;

	case PATTERN1_BOMBING_END:
	{
		m_eState = PLAYER_FOLLOW_START;
		m_eAniStateBomber = CLOSESTART;
	}
	break;



	case PATTERN2_SHOOTING_START:
	{
		m_eState = PATTERN2_SHOOTING_ING;
		m_eAniStateGun = GUNSHOOTSTART_START;

		m_dwShootingEndDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();

		CObjPlayer2* pPlayer = nullptr;
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* _pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (_pPlayer != nullptr)
			{
				pPlayer = _pPlayer;
				break;
			}
		}



		CObjBossClusterAim* pBossClusterAim = new CObjBossClusterAim;
		pBossClusterAim->Initialize();
		if (pPlayer != nullptr)
		{
			pBossClusterAim->Set_Pos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
		}
		else
		{
			pBossClusterAim->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		}
		
		pBossClusterAim->Set_Shoot(false);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBossClusterAim);
		m_pClusterAim = pBossClusterAim;

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_pClusterAim->Set_Shoot(true);
			}, 3000);
	}
	break;

	case PATTERN2_SHOOTING_ING:
	{
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (pPlayer != nullptr)
			{
				DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
				float playerX = pPlayer->Get_Info()->fX;
				float playerY = pPlayer->Get_Info()->fY;


				float newX = playerX + cosf(m_fPlayerFollowAngle * PI / 180.f) * 100;
				float newY = playerY - sinf(m_fPlayerFollowAngle * PI / 180.f) * 100;

				float width = m_tInfo.fX - newX;
				float height = m_tInfo.fY - newY;

				float rad = atan2f(height, width) + PI;
				float ang = rad * 180.f / PI;
				float ang2 = ang * -1;
				Move(ang2, m_fSpeed);




				float aimX = m_pClusterAim->Get_Info()->fX;
				float aimY = m_pClusterAim->Get_Info()->fY;
				float aimWidth = aimX - playerX ;
				float aimHeight = aimY - playerY ;
				float aimRad = atan2f(aimHeight, aimWidth) + PI;
				float aimAng = aimRad * 180.f / PI;
				float aimAng2 = aimAng * -1;

				float newClusterX = aimX + cosf(aimRad * -1) * m_fClusterAimSpeed;
				float newClusterY = aimY - sinf(aimRad * -1) * m_fClusterAimSpeed;
				m_pClusterAim->Set_Pos(newClusterX, newClusterY);

			

				CTimeMgr::Delay(&m_dwShootingEndDelay, (10000), [&]() {
					m_eState = PATTERN2_SHOOTING_END;
					});
			}
		}
	}
	break;

	case PATTERN2_SHOOTING_END:
	{
		m_pClusterAim->Set_Dead();
		m_eAniStateGun = GUNSHOOTEND_START;
		//m_pClusterAim = nullptr;
		m_eState = PLAYER_FOLLOW_START;
	}
	break;

	case PATTERN3_BODYSLAP_START:
	{
		m_eState = PATTERN3_BODYSLAP_ING;
		m_bShowBodySlapAlert = false;

		m_bBossHideToDown = true;

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bBossHideToDown = false;
			}, 1000);
	
		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
				{
					CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
					if (pPlayer != nullptr)
					{
						m_fBodySlapPlayerX = pPlayer->Get_Info()->fX;
						m_fBodySlapPlayerY = pPlayer->Get_Info()->fY;
						auto xlen = (m_fBodySlapPlayerX + 224 * 3) - (m_fBodySlapPlayerY - 224 * 3);
						auto alertXSize = 35;
						int total = xlen / alertXSize;
						for (int i = 0; i < total; ++i)
						{
							auto offset = (m_fBodySlapPlayerX - 224 * 3) + i * alertXSize;
							CObjBossBodySlapAlert* pAlert = new CObjBossBodySlapAlert;
							pAlert->Initialize();
							pAlert->Set_Pos(offset, m_fBodySlapPlayerY);
							pAlert->Set_DelayTime(20 * i);
							CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pAlert);
						}

						CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BODYSLAPALERT);
						CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BodySlapWarning.wav", SOUND_SFX_BODYSLAPALERT, 1.f);
					}
				}
			}, 3000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
				{
					CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
					if (pPlayer != nullptr)
					{
						CObjBossBodySlap* pBossBodySlap = new CObjBossBodySlap;
						pBossBodySlap->Initialize();
						pBossBodySlap->Set_Pos(m_fBodySlapPlayerX - 224 * 3, m_fBodySlapPlayerY);
						CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBossBodySlap);
					//SFX_Chap4_Firebird_BodySlap.wav
						CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BODYSLAP);
						CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BodySlap.wav", SOUND_SFX_BODYSLAP, 1.f);
					}
				}
			}, 5000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bBossShowToUp = true;
			}, 7000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_eState = PATTERN3_BODYSLAP_END;
				m_bBossShowToUp = false;
			}, 8000);
	}
	break;

	case PATTERN3_BODYSLAP_ING:
	{
		if (m_bBossHideToDown)
		{
			Move(270.f, 15.f);
		}
		else if (m_bBossShowToUp)
		{
			Move(90.f, 15.f);
		}
		
	}
	break;

	case PATTERN3_BODYSLAP_END:
	{
		m_eState = PLAYER_FOLLOW_START;
	}
	break;

	case PATTERN4_CLUSTERBOMB_START:
	{
		m_eState = PATTERN4_CLUSTERBOMB_ING;
		m_dwClusterTraceOneDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();
		m_dwClusterBombShootOneDelay = CTimeMgr::Get_Instance()->Get_Tick_Count();
		m_bClusterAimTrace = true;
		m_bBossHideToDown = true;
		
		


		CObjPlayer2* pPlayer = nullptr;
		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* _pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (_pPlayer != nullptr)
			{
				pPlayer = _pPlayer;
				break;
			}
		}


		CObjBossClusterAim* pBossClusterAim = new CObjBossClusterAim;
		pBossClusterAim->Initialize();
		if (pPlayer != nullptr)
		{
			pBossClusterAim->Set_Pos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
		}
		else
		{
			pBossClusterAim->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		}
		pBossClusterAim->Set_Shoot(false);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBossClusterAim);
		m_pClusterAim = pBossClusterAim;

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bBossHideToDown = false;

				//Set_Active(false);

				CObjBossBackHeli* pBackHeli = new CObjBossBackHeli;
				pBackHeli->Initialize();
				pBackHeli->Set_Pos(WINCX >> 1, WINCY);
				pBackHeli->Set_MoveTarget(WINCX >> 1, WINCY >> 1);
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBackHeli);

				
			}, 1000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bClusterAimTrace = false;
			}, 4000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_pClusterAim->Shoot360ClusterBomblet();
				m_pClusterAim->Set_Dead();

				for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER))
				{
					auto backHeli = dynamic_cast<CObjBossBackHeli*>(pObj);
					if (backHeli != nullptr)
					{
						backHeli->Set_MoveTarget(WINCX >> 1, WINCY + 200);
					}
				}
			}, 5000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER))
				{
					auto backHeli = dynamic_cast<CObjBossBackHeli*>(pObj);
					if (backHeli != nullptr)
					{
						backHeli->Set_Dead();
					}
				}
				
			}, 8000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bBossShowToUp = true;
			}, 8000);

		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_eState = PATTERN4_CLUSTERBOMB_END;
				m_bBossShowToUp = false;
			}, 9000);
	}
	break;

	case PATTERN4_CLUSTERBOMB_ING:
	{
		if (m_bBossHideToDown)
		{
			Move(270.f, 15.f);
		}
		else if (m_bBossShowToUp)
		{
			Move(90.f, 15.f);
		}

		for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER))
		{
			CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
			if (pPlayer != nullptr)
			{
				DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
				float playerX = pPlayer->Get_Info()->fX;
				float playerY = pPlayer->Get_Info()->fY;

				if (m_bClusterAimTrace)
				{
					float aimX = m_pClusterAim->Get_Info()->fX;
					float aimY = m_pClusterAim->Get_Info()->fY;
					float aimWidth = aimX - playerX;
					float aimHeight = aimY - playerY;
					float aimRad = atan2f(aimHeight, aimWidth) + PI;
					float aimAng = aimRad * 180.f / PI;
					float aimAng2 = aimAng * -1;

					float newClusterX = aimX + cosf(aimRad * -1) * m_fClusterAimSpeed;
					float newClusterY = aimY - sinf(aimRad * -1) * m_fClusterAimSpeed;
					m_pClusterAim->Set_Pos(newClusterX, newClusterY);
				}
			}
		}
	}
	break;

	case PATTERN4_CLUSTERBOMB_END:
	{
		//m_pClusterAim->Set_Dead();
		m_eState = PLAYER_FOLLOW_START;
	}
	break;


	case BROKEN_START:
	{
		//m_fDamagedAngle
		m_bRetreat = true;
		CTimeMgr::Get_Instance()->Set_Timer(
			[&]() {
				m_bRetreat = false;
				m_eState = BROKEN_END;
			}, 1000);

		m_eState = BROKEN_ING;
		++m_iDamagedCnt;
		m_eAniStateBroken = BROKEN;
	}
	break;
	case BROKEN_ING:
	{
		if (m_bRetreat)
		{
			m_tInfo.fX += cosf(m_fRetreatAngle * PI / 180.f) * 15.f;
			m_tInfo.fY -= sinf(m_fRetreatAngle * PI / 180.f) * 15.f;
		}
	}
	break;
	case BROKEN_END:
	{
		m_eState = PLAYER_FOLLOW_START;
	}
	break;
	}

}

void CObjBossFireBird::Move(float fAngle, float fSpeed)
{
	m_tInfo.fX += cosf(fAngle * PI / 180.f) * fSpeed;
	m_tInfo.fY -= sinf(fAngle * PI / 180.f) * fSpeed;

	//»ó½Â
	if (fAngle < -180 && fAngle > -360)
	{
		if (m_eAniStateWing == NEU)
		{
			m_eAniStateWing = ANI_STATE_WING::NEU_TO_UP_START;
		}
		else if (m_eAniStateWing == UP_KEEP)
		{

		}
		else if (m_eAniStateWing == DOWN_KEEP)
		{
			m_eAniStateWing = ANI_STATE_WING::DOWN_TO_NEU_START;
		}
	}
	// ÇÏ°­
	else
	{
		if (m_eAniStateWing == NEU)
		{
			m_eAniStateWing = ANI_STATE_WING::NEU_TO_DOWN_START;
		}
		else if (m_eAniStateWing == UP_KEEP)
		{
			m_eAniStateWing = ANI_STATE_WING::UP_TO_NEU_START;
		}
		else if (m_eAniStateWing == DOWN_KEEP)
		{

		}
	}
}
