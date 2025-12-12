#include "pch.h"
#include "CObjMonsterTrooper.h"
#include "CObjMonsterTrooperSprite.h"
#include "CObjMgr.h"

CObjMonsterTrooper::CObjMonsterTrooper()
{
}

CObjMonsterTrooper::~CObjMonsterTrooper()
{
}

void CObjMonsterTrooper::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExecuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_PODPOPUP_START;

	CObjMonsterTrooperSprite* pSprite = new CObjMonsterTrooperSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);
}

int CObjMonsterTrooper::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterTrooper::Late_Update()
{
}

void CObjMonsterTrooper::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterTrooper::Release()
{
}

void CObjMonsterTrooper::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterTrooper::Excuted(CObj* pPlayer, float fRad)
{
}
