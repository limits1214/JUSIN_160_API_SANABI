#include "pch.h"
#include "CObjMonsterDummyFloater.h"
#include "CObjMonsterDummyFloaterSprite.h"
#include "CObjMgr.h"

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

	m_bExecuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RESPAWN_START;

	CObjMonsterDummyFloaterSprite* pSprite = new CObjMonsterDummyFloaterSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);
}

int CObjMonsterDummyFloater::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDummyFloater::Late_Update()
{
}

void CObjMonsterDummyFloater::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDummyFloater::Release()
{
}

void CObjMonsterDummyFloater::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterDummyFloater::Excuted(CObj* pPlayer, float fRad)
{
}
