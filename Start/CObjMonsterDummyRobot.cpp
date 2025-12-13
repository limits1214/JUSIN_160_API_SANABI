#include "pch.h"
#include "CObjMonsterDummyRobot.h"
#include "CObjMonsterDummyRobotSprite.h"
#include "CObjMgr.h"

CObjMonsterDummyRobot::CObjMonsterDummyRobot()
{
}

CObjMonsterDummyRobot::~CObjMonsterDummyRobot()
{
}

void CObjMonsterDummyRobot::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_bExecuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RESPAWN_START;

	CObjMonsterDummyRobotSprite* pSprite = new CObjMonsterDummyRobotSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);
}

int CObjMonsterDummyRobot::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDummyRobot::Late_Update()
{
}

void CObjMonsterDummyRobot::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterDummyRobot::Release()
{
}

void CObjMonsterDummyRobot::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterDummyRobot::Excuted(CObj* pPlayer, float fRad)
{
}

void CObjMonsterDummyRobot::Grabbed(CObj* pPlayer)
{
}
