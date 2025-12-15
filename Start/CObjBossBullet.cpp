#include "pch.h"
#include "CObjBossBullet.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjBossBulletSprite.h"
#include "CObjMgr.h"
#include "CObjUnstableKnockbackPlatformA.h"
#include "CObjClusterBombExplode.h"
#include "CObjClusterBombletExplode.h"
#include "CObjPlayer2.h"
#include "CSoundMgr.h"

CObjBossBullet::CObjBossBullet()
	:m_iOption(0)
{
}

CObjBossBullet::~CObjBossBullet()
{
	Release();
}

void CObjBossBullet::Initialize()
{
	m_bUseMainScroll = true;

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	CObjBossBulletSprite* pSprite = new CObjBossBulletSprite;
	pSprite->Set_Option(m_iOption);
	pSprite->Initialize();
	//bomblet
	if (m_iOption == 0)
	{
		pSprite->Set_Pos(0, 16);
	}
	// bomb
	else if (m_iOption == 1)
	{
		pSprite->Set_Pos(0, -15);
	}
	
	pSprite->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pSprite);
	
}

int CObjBossBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_iOption == 0)
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * 5.f;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * 5.f;
	}
	else if (m_iOption == 1)
	{
		m_tInfo.fY += 5.f;
	}
	
	if (
		m_tInfo.fX < ((WINCX >> 1) - 224 * 6)
		||
		m_tInfo.fX >((WINCX >> 1) + 224 * 6)
		||
		m_tInfo.fY < ((WINCY >> 1) - 224 * 4)
		||
		m_tInfo.fY >((WINCY >> 1) + 224 * 4)
		)
	{
		Set_Dead_Cascade();
	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBossBullet::Late_Update()
{

}

void CObjBossBullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjBossBullet::Release()
{
}

void CObjBossBullet::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	auto pPlatform = dynamic_cast<CObjUnstableKnockbackPlatformA*>(pObj);
	if (pPlatform != nullptr && eCollID == COLL_RECT)
	{
		if (m_iOption == 0)
		{
			CObjClusterBombletExplode* pBombletExplode = new CObjClusterBombletExplode;
			pBombletExplode->Initialize();
			pBombletExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBombletExplode);
			CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_CLUSTERBOMBLETEXPLOSION);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_ClusterBombletExplosion.wav", SOUND_SFX_CLUSTERBOMBLETEXPLOSION, 1.f);
			
		}
		else if (m_iOption == 1)
		{
			CObjClusterBombExplode* pBombExplode = new CObjClusterBombExplode;
			pBombExplode->Initialize();
			pBombExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBombExplode);
			CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BOMBING_EXPLOSION);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingBombExplosion.wav", SOUND_SFX_BOMBING_EXPLOSION, 1.f);
		}
		Set_Dead_Cascade();

		return;
	}

	CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
	if (eCollID == COLL_RECT && pPlayer != nullptr)
	{
		pPlayer->Damage();

		
		Set_Dead_Cascade();
		if (m_iOption == 0)
		{
			CObjClusterBombletExplode* pBombletExplode = new CObjClusterBombletExplode;
			pBombletExplode->Initialize();
			pBombletExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBombletExplode);
			CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_CLUSTERBOMBLETEXPLOSION);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_ClusterBombletExplosion.wav", SOUND_SFX_CLUSTERBOMBLETEXPLOSION, 1.f);
		}
		else if (m_iOption == 1)
		{
			CObjClusterBombExplode* pBombExplode = new CObjClusterBombExplode;
			pBombExplode->Initialize();
			pBombExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBombExplode);
			CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BOMBING_EXPLOSION);
			CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingBombExplosion.wav", SOUND_SFX_BOMBING_EXPLOSION, 1.f);
		}
		return;
	}
}
