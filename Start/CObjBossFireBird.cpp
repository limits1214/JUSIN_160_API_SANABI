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

	m_eAniStateBomber = ANI_STATE_BOMBER::IDLE;
	m_eAniStateGun = ANI_STATE_GUN::GUN_IDLE;

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
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	// Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
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
	//»ó½Â
	if (CKeyMgr::Get_Instance()->Key_Pressing('T'))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	// ÁÂÃø
	if (CKeyMgr::Get_Instance()->Key_Pressing('F'))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	// ÇÏ°­
	if (CKeyMgr::Get_Instance()->Key_Pressing('G'))
	{
		m_tInfo.fY += m_fSpeed;
	}

	// ¿ìÃø
	if (CKeyMgr::Get_Instance()->Key_Pressing('H'))
	{
		m_tInfo.fX += m_fSpeed;
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
}
