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
#include "CObjPlayer.h"
#include "CObjBossBodySlapAlert.h"
#include "CObjBossBullet.h"
#include "CObjClusterBombExplode.h"

CObjBossFireBird::CObjBossFireBird()
{
    Set_DbgName(_T("CObjBossFireBird"));
}

CObjBossFireBird::~CObjBossFireBird()
{
    Release();
}

void CObjBossFireBird::Initialize()
{
    Set_UseMainScroll(true);
    m_tInfo.fCX = 300;
    m_tInfo.fCY = 300;

	m_fSpeed = 3.f;

	m_fAngle = 0.f;

	m_eAniStateBomber = ANI_STATE_BOMBER::IDLE;
	m_eAniStateGun = ANI_STATE_GUN::GUN_IDLE;
	m_eAniStateBroken = ANI_STATE_BROKEN::NORMAL;
	m_eAniStateWing = ANI_STATE_WING::NEU;

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

	Test_Key_Input();

	Move_Frame();

    __super::Update_Rect();

	//m_tInfo.fX += 0.1;
	
    return OBJ_NOEVENT;
}

void CObjBossFireBird::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBird::Render(HDC hDC)
{
	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	//BmpRender(
	//	hDC,
	//	m_tRect.left, m_tRect.top,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,

	//	hMemDC,
	//	m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY
	//);
	// Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CObjBossFireBird::Release()
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
			CObjPlayer* pPlayer = dynamic_cast<CObjPlayer*>(pObj);
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
