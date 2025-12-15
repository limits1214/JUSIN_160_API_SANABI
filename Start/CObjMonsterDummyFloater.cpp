#include "pch.h"
#include "CObjMonsterDummyFloater.h"
#include "CObjMonsterDummyFloaterSprite.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CObjExplosionSprite.h"

CObjMonsterDummyFloater::CObjMonsterDummyFloater()
{
}

CObjMonsterDummyFloater::~CObjMonsterDummyFloater()
{
}

void CObjMonsterDummyFloater::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExcuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RESPAWN_START;

	CObjMonsterDummyFloaterSprite* pSprite = new CObjMonsterDummyFloaterSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);

	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_fLemnisDeltaSum = 0;
	m_bOriginSet = false;

	m_bGrabbed = false;
}

int CObjMonsterDummyFloater::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bOriginSet)
	{
		m_bOriginSet = true;
		m_fOriginX = m_tInfo.fX;
		m_fOriginY = m_tInfo.fY;
	}



	DeltaUpdate();


	float lemnisX = 0;
	float lemnisY = 0;

	float a = 40;
	float t = m_fLemnisDeltaSum;
	lemnisX = a * cosf(t) / (1.0f + sinf(t) * sinf(t));
	lemnisY = a * sinf(t) * cosf(t) / (1.0f + sinf(t) * sinf(t));


	m_fOriginX;
	m_fOriginY ;


	if (!m_bGrabbed)
	{
		m_tInfo.fX = m_fOriginX + lemnisX;
		m_tInfo.fY = m_fOriginY + lemnisY;
	}
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDummyFloater::Late_Update()
{
}

void CObjMonsterDummyFloater::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDummyFloater::Release()
{
}

void CObjMonsterDummyFloater::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterDummyFloater::Excuted(CObj* pPlayer, float fRad)
{
	m_bExcuted = true;
	Set_Dead_Cascade();
	CObjExplosionSprite* pExplosionSprite = new CObjExplosionSprite;
	pExplosionSprite->Set_Option(0);
	pExplosionSprite->Initialize();
	pExplosionSprite->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pExplosionSprite);
}

void CObjMonsterDummyFloater::Grabbed(CObj* pPlayer)
{
	m_eAniState = AST_EXCSTART_START;
	m_bGrabbed = true;
}


void CObjMonsterDummyFloater::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;
	m_dwTime = dwNowTime;

	m_fLemnisDeltaSum += dwDelta;
}