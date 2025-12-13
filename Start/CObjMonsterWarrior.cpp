#include "pch.h"
#include "CObjMonsterWarrior.h"
#include "CObjMonsterWarriorSprite.h"
#include "CObjMgr.h"

CObjMonsterWarrior::CObjMonsterWarrior()
{
}

CObjMonsterWarrior::~CObjMonsterWarrior()
{
}

void CObjMonsterWarrior::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExecuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RIGHT_SPAWN_START;

	CObjMonsterWarriorSprite* pSprite = new CObjMonsterWarriorSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);
}

int CObjMonsterWarrior::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterWarrior::Late_Update()
{
}

void CObjMonsterWarrior::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterWarrior::Release()
{
}

void CObjMonsterWarrior::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterWarrior::Excuted(CObj* pPlayer, float fRad)
{
}

void CObjMonsterWarrior::Grabbed(CObj* pPlayer)
{
}
