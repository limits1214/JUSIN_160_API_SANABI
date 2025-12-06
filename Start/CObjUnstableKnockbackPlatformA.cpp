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
	//CObjCollisionRect::Initialize();
	Set_Option(ERI_CLIMABLE);

	Set_UseMainScroll(true);
	m_tInfo.fCX = 264;
	m_tInfo.fCY = 112;

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
}

int CObjUnstableKnockbackPlatformA::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	

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

void CObjUnstableKnockbackPlatformA::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
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