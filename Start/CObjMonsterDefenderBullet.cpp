#include "pch.h"
#include "CObjMonsterDefenderBullet.h"
#include "pch.h"
#include "CObjMonsterDefenderBulletSprite.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CObjCollisionRect.h"
#include "CObjPlayer2.h"
#include "CSoundMgr.h"
#include "CObjExplosionSprite.h"
CObjMonsterDefenderBullet::CObjMonsterDefenderBullet()
{
}

CObjMonsterDefenderBullet::~CObjMonsterDefenderBullet()
{
	Release();
}

void CObjMonsterDefenderBullet::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 2.f;
	m_fAngle = 90.f;

	CObjMonsterDefenderBulletSprite* pSprite = new CObjMonsterDefenderBulletSprite;

	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);


	m_iDeadTimer = CTimeMgr::Get_Instance()->Set_Timer([&]() {
		Set_Dead_Cascade();
		CObjExplosionSprite* pExplosionSprite = new CObjExplosionSprite;
		pExplosionSprite->Set_Option(1);
		pExplosionSprite->Initialize();
		pExplosionSprite->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pExplosionSprite);

		CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BOMBING_EXPLOSION);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingBombExplosion.wav", SOUND_SFX_BOMBING_EXPLOSION, 1.f);
		}, 10000);
}

int CObjMonsterDefenderBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_pTarget != nullptr)
	{
		CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(m_pTarget);
		if (pPlayer != nullptr)
		{
			float playerX = pPlayer->Get_Info()->fX;
			float playerY = pPlayer->Get_Info()->fY;
			float tmpWidth = playerX - m_tInfo.fX;
			float tmpHeight = playerY - m_tInfo.fY;
			float tmpRad = atan2f(tmpHeight, tmpWidth);
			float ang = tmpRad * 180.f / PI * -1;
			if (ang < 0)
				ang += 360;
			// TODO 점점 기울이게
			//if (m_fAngle > ang)
			//{
			//	--m_fAngle;
			//}
			//else
			//{
			//	++m_fAngle;
			//}

			m_fAngle = ang;
		}
	}

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDefenderBullet::Late_Update()
{

}

void CObjMonsterDefenderBullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDefenderBullet::Release()
{
}

void CObjMonsterDefenderBullet::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
	CObjCollisionRect* pRect = dynamic_cast<CObjCollisionRect*>(pObj);
	if (eCollID == COLL_RECT && pRect != nullptr)
	{
		CTimeMgr::Get_Instance()->Clear_Timer(m_iDeadTimer);
		Set_Dead_Cascade();
		CObjExplosionSprite* pExplosionSprite = new CObjExplosionSprite;
		pExplosionSprite->Set_Option(1);
		pExplosionSprite->Initialize();
		pExplosionSprite->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pExplosionSprite);

		CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BOMBING_EXPLOSION);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingBombExplosion.wav", SOUND_SFX_BOMBING_EXPLOSION, 1.f);
		return;
	}

	CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2*>(pObj);
	if (eCollID == COLL_RECT && pPlayer != nullptr)
	{
		pPlayer->Damage();

		CTimeMgr::Get_Instance()->Clear_Timer(m_iDeadTimer);
		Set_Dead_Cascade();
		CObjExplosionSprite* pExplosionSprite = new CObjExplosionSprite;
		pExplosionSprite->Set_Option(1);
		pExplosionSprite->Initialize();
		pExplosionSprite->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pExplosionSprite);

		CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_BOMBING_EXPLOSION);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_Firebird_BombingBombExplosion.wav", SOUND_SFX_BOMBING_EXPLOSION, 1.f);
		return;
	}
}
