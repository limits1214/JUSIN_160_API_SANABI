#include "pch.h"
#include "CObjBossBodySlap.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjPlayer2.h"
CObjBossBodySlap::CObjBossBodySlap()

{
}

CObjBossBodySlap::~CObjBossBodySlap()
{
	Release();
}

void CObjBossBodySlap::Initialize()
{
	m_bUseMainScroll = true;

	m_tInfo.fCX = 933;
	m_tInfo.fCY = 445;
	m_eFrameKey = FKI_Spr_BOSS_Firebird_Body_BodySlapLoop;
	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_BODY_SLAP, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossBodySlap::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += 20.f;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBossBodySlap::Late_Update()
{
	if (m_tInfo.fX > 2000)
	{
		Set_Dead();
	}
}

void CObjBossBodySlap::Render(HDC hDC)
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

void CObjBossBodySlap::Release()
{
}

void CObjBossBodySlap::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
	CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
	if (eCollID == COLL_RECT && pPlayer != nullptr)
	{
		pPlayer->Damage();
		return;
	}
}
