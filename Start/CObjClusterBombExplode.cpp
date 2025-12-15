#include "pch.h"
#include "CObjClusterBombExplode.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
CObjClusterBombExplode::CObjClusterBombExplode()
{
}

CObjClusterBombExplode::~CObjClusterBombExplode()
{
}

void CObjClusterBombExplode::Initialize()
{
	m_bUseMainScroll = true;
	m_tInfo.fCX = 126;
	m_tInfo.fCY = 122.f;
	Set_FrameKeyId(FKI_Spr_BOSS_ClusterBombExplode_Sheet);
	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_CLUSTER_BOMB_EXPLODE, CTimeMgr::Get_Instance()->Get_Tick_Count());

}

int CObjClusterBombExplode::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	Move_Frame();
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	int end = FrameStateId_To_Frame(FSI_BOSS_CLUSTER_BOMB_EXPLODE, dwNow).iEnd;
	if (m_tFrame.iStart == end)
	{
		Set_Dead();
	}

	return OBJ_NOEVENT;
}

void CObjClusterBombExplode::Late_Update()
{
}

void CObjClusterBombExplode::Render(HDC hDC)
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

void CObjClusterBombExplode::Release()
{
}

