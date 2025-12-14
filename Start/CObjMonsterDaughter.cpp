#include "pch.h"
#include "CObjMonsterDaughter.h"
#include "CObjMonsterDaughterSprite.h"
#include "CObjMgr.h"

CObjMonsterDaughter::CObjMonsterDaughter()
{
}

CObjMonsterDaughter::~CObjMonsterDaughter()
{
}

void CObjMonsterDaughter::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExcuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RIGHT_IDLE_START;

	CObjMonsterDaughterSprite* pSprite = new CObjMonsterDaughterSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);
}

int CObjMonsterDaughter::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDaughter::Late_Update()
{
}

void CObjMonsterDaughter::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDaughter::Release()
{
}

void CObjMonsterDaughter::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterDaughter::Excuted(CObj* pPlayer, float fRad)
{
}

void CObjMonsterDaughter::Grabbed(CObj* pPlayer)
{
}
