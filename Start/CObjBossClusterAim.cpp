#include "pch.h"
#include "CObjBossClusterAim.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjBossShootExplode.h"
#include "CObjMgr.h"
#include "CObjClusterBombExplode.h"
#include "CObjBossBullet.h"
#include "CSoundMgr.h"

CObjBossClusterAim::CObjBossClusterAim()
{
}

CObjBossClusterAim::~CObjBossClusterAim()
{
}

void CObjBossClusterAim::Shoot360ClusterBomblet()
{
	float targetX = m_tInfo.fX;
	float targetY = m_tInfo.fY;
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
	//SFX_Chap4_Firebird_ClusterShoot.wav
	CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_CLUSTERSHOOT);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_ClusterBombExplosion.wav", SOUND_SFX_CLUSTERSHOOT, 1.f);

}

void CObjBossClusterAim::Initialize()
{
	m_bShoot = false;
	m_bUseMainScroll = true;
	m_tInfo.fCX = 224.f;
	m_tInfo.fCY = 122.f;
	Set_FrameKeyId(FKI_Spr_BOSS_Cluster_Aim_Sheet);
	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_CLUSTER_AIM, CTimeMgr::Get_Instance()->Get_Tick_Count());

	m_dwShootTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

//SFX_Chap4_Firebird_ClusterWarning.wav

	CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_CLUSTERAIM_WARNING);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_ClusterWarning.wav", SOUND_SFX_CLUSTERAIM_WARNING, 1.f);
}

int CObjBossClusterAim::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();

	if (m_bShoot)
	{
		CTimeMgr::Delay(&m_dwShootTime, 150,
			[&]() {
				CObjBossShootExplode* pShootExplode = new CObjBossShootExplode;
				pShootExplode->Initialize();
				pShootExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
				CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pShootExplode);
				//gun_machinegun_auto_heavy_shot_01.wav
				CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_MACHINEGUN_SHOOT);
				CSoundMgr::Get_Instance()->PlaySound(L"gun_machinegun_auto_heavy_shot_01.wav", SOUND_SFX_MACHINEGUN_SHOOT, 1.f);
			}
		);
	}
	
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
