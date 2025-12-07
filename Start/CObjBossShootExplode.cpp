#include "pch.h"
#include "CObjBossShootExplode.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
CObjBossShootExplode::CObjBossShootExplode()
{
}

CObjBossShootExplode::~CObjBossShootExplode()
{
}

void CObjBossShootExplode::Initialize()
{
	m_bUseMainScroll = true;
	m_tInfo.fCX = 173;
	m_tInfo.fCY = 124.f;
	Set_FrameKeyId(FKI_Spr_BOSS_ShootExplode_Sheet);
	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_SHOT_EXPLODE, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossShootExplode::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	Move_Frame();


	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	int end = FrameStateId_To_Frame(FSI_BOSS_SHOT_EXPLODE, dwNow).iEnd;
	if (m_tFrame.iStart == end)
	{
		Set_Dead();
	}

	return OBJ_NOEVENT;
}

void CObjBossShootExplode::Late_Update()
{
}

void CObjBossShootExplode::Render(HDC hDC)
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

void CObjBossShootExplode::Release()
{
}

void CObjBossShootExplode::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}
