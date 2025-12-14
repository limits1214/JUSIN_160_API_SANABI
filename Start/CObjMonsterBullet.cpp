#include "pch.h"
#include "CObjMonsterBullet.h"
#include "CObjMonsterBulletSprite.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CObjMonsterBulletBoomSprite.h"
#include "CObjCollisionRect.h"
#include "CObjPlayer2.h"
CObjMonsterBullet::CObjMonsterBullet()
{
}

CObjMonsterBullet::~CObjMonsterBullet()
{
	Release();
}

void CObjMonsterBullet::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 5.f;

	CObjMonsterBulletSprite* pSprite = new CObjMonsterBulletSprite;
	
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);


	m_iDeadTimer = CTimeMgr::Get_Instance()->Set_Timer([&]() {
		Set_Dead_Cascade();
		CObjMonsterBulletBoomSprite* pBoom = new CObjMonsterBulletBoomSprite;
		pBoom->Initialize();
		pBoom->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBoom);
		}, 2000);
}

int CObjMonsterBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterBullet::Late_Update()
{

}

void CObjMonsterBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterBullet::Release()
{
}

void CObjMonsterBullet::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
	CObjCollisionRect* pRect = dynamic_cast<CObjCollisionRect*>(pObj);
	if (eCollID == COLL_RECT && pRect != nullptr)
	{
		CTimeMgr::Get_Instance()->Clear_Timer(m_iDeadTimer);
		Set_Dead_Cascade();
		CObjMonsterBulletBoomSprite* pBoom = new CObjMonsterBulletBoomSprite;
		pBoom->Initialize();
		pBoom->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBoom);
		return;
	}

	CObjPlayer2* pPlayer = dynamic_cast<CObjPlayer2 * >(pObj);
	if (eCollID == COLL_RECT && pPlayer != nullptr)
	{
		pPlayer->Damage();

		CTimeMgr::Get_Instance()->Clear_Timer(m_iDeadTimer);
		Set_Dead_Cascade();
		CObjMonsterBulletBoomSprite* pBoom = new CObjMonsterBulletBoomSprite;
		pBoom->Initialize();
		pBoom->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBoom);
		return;
	}
}
