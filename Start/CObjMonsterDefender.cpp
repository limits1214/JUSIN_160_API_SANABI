#include "pch.h"
#include "CObjMonsterDefender.h"
#include "CObjMonsterDefenderSprite.h"
#include "CObjMgr.h"

CObjMonsterDefender::CObjMonsterDefender()
{
}

CObjMonsterDefender::~CObjMonsterDefender()
{
}

void CObjMonsterDefender::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExecuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RIGHT_SET_START;

	CObjMonsterDefenderSprite* pSprite = new CObjMonsterDefenderSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);
}

int CObjMonsterDefender::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDefender::Late_Update()
{
}

void CObjMonsterDefender::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDefender::Release()
{
}

void CObjMonsterDefender::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterDefender::Excuted(CObj* pPlayer, float fRad)
{
}
