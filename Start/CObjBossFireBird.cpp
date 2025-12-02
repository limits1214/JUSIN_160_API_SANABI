#include "pch.h"
#include "CObjBossFireBird.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"
#include "CObjBossFireBirdWing.h"
#include "CObjBossFireBirdGun.h"

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
    m_tInfo.fCX = 688;
    m_tInfo.fCY = 352;

	m_eFrameKey = FKI_Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8;
	m_eCurState = FSI_BOSS_FIREBIRD_BODY_NORMAL_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());


	CObjBossFireBirdWing* pWing = new CObjBossFireBirdWing;
	pWing->Initialize();
	pWing->Set_Pos(0, 0);
	pWing->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pWing);

	CObjBossFireBirdGun* pGun = new CObjBossFireBirdGun;
	pGun->Initialize();
	pGun->Set_Pos(0, 0);
	pGun->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pGun);
}

int CObjBossFireBird::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    __super::Update_Rect();
	Move_Frame();

	m_tInfo.fX += 0.1;
	
    return OBJ_NOEVENT;
}

void CObjBossFireBird::Late_Update()
{
	Motion_Change();
}

void CObjBossFireBird::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
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