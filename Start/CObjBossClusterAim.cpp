#include "pch.h"
#include "CObjBossClusterAim.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjBossShootExplode.h"
#include "CObjMgr.h"
CObjBossClusterAim::CObjBossClusterAim()
{
}

CObjBossClusterAim::~CObjBossClusterAim()
{
}

void CObjBossClusterAim::Initialize()
{
	m_bUseMainScroll = true;
	m_tInfo.fCX = 224.f;
	m_tInfo.fCY = 122.f;
	Set_FrameKeyId(FKI_Spr_BOSS_Cluster_Aim_Sheet);
	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_CLUSTER_AIM, CTimeMgr::Get_Instance()->Get_Tick_Count());

	m_dwShootTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
}

int CObjBossClusterAim::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	//m_tInfo.fX += 1.f;

	//m_tInfo.fX += cosf(CTimeMgr::Get_Instance()->Get_Tick_Count()) * 30;
	//m_tInfo.fY += sinf(CTimeMgr::Get_Instance()->Get_Tick_Count()) * 30;
	//m_tInfo.fX += 1.f;
	//m_tInfo.fY += 1.f;

	Move_Frame();



	CTimeMgr::Delay(&m_dwShootTime, 200,
		[&]() {
			CObjBossShootExplode* pShootExplode = new CObjBossShootExplode;
			pShootExplode->Initialize();
			pShootExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pShootExplode);
		}
	);
	



	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBossClusterAim::Late_Update()
{
}

void CObjBossClusterAim::Render(HDC hDC)
{
	//STR_FKI_Spr_BOSS_Cluster_Aim_Sheet
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

void CObjBossClusterAim::Release()
{
}
