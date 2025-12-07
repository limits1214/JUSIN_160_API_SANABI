#include "pch.h"
#include "CObjMonsterFloatingBomb.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterFloatingBombSprite.h"
#include "CObjMgr.h"
#include "CObjMouse.h"
#include "CScrollMgr.h"
#include "CObjPlayer.h"
#include "CObjMonsterFloatingBombHugeExplodeSprite.h"
#include "CObjBossFireBird.h"


CObjMonsterFloatingBomb::CObjMonsterFloatingBomb()
{
	Set_DbgName(_T("CObjMonsterFloatingBomb"));
}

CObjMonsterFloatingBomb::~CObjMonsterFloatingBomb()
{
	Release();
}

void CObjMonsterFloatingBomb::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	CObjMonsterFloatingBombSprite* pPltSprite = new CObjMonsterFloatingBombSprite;
	pPltSprite->Initialize();
	pPltSprite->Set_Parent(this);
	pPltSprite->Set_Pos(12, 5);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pPltSprite);

	m_bExecuted = false;
}

int CObjMonsterFloatingBomb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bExecuted)
	{
		m_tInfo.fX += cosf(m_fExcutedRad) * 3;
		m_tInfo.fY += sinf(m_fExcutedRad) * 3;
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjMonsterFloatingBomb::Late_Update()
{
	
}

void CObjMonsterFloatingBomb::Render(HDC hDC)
{
	
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterFloatingBomb::Release()
{
}

void CObjMonsterFloatingBomb::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
	CObjBossFireBird* pBoss = dynamic_cast<CObjBossFireBird*>(pObj);
	if (eCollID == COLL_RECT && pBoss != nullptr)
	{
		if (m_bExecuted)
		{
			Explode();
			pBoss->m_eAniStateBroken = CObjBossFireBird::BROKEN;
		}
	}
}

void CObjMonsterFloatingBomb::Excuted(CObj* pPlayer, float fRad)
{
	m_bExecuted = true;
	m_fExcutedRad = fRad + PI;
}

void CObjMonsterFloatingBomb::Explode()
{
	Set_Dead_Cascade();

	CObjMonsterFloatingBombHugeExplodeSprite* pFloatingBombExplode = new CObjMonsterFloatingBombHugeExplodeSprite;
	pFloatingBombExplode->Initialize();
	pFloatingBombExplode->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBombExplode);
}

void CObjMonsterFloatingBomb::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		if (pMouse->Get_Last_Key() == VK_RBUTTON)
		{
			POINT ptCurr = pMouse->Get_Pt_Curr();
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			ptCurr.x -= iScrollX;
			ptCurr.y -= iScrollY;
			if (PtInRect(&m_tRect, ptCurr))
			{
				list<CObj*>* playerList = CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER);

				CObjPlayer* pPlayer = nullptr;
				for (auto*& pObj : *playerList)
				{
					CObjPlayer* _pPlayer = dynamic_cast<CObjPlayer*>(pObj);
					if (_pPlayer != nullptr)
					{
						pPlayer = _pPlayer;
						break;
					}
				}

				if (pPlayer != nullptr)
				{

					float fWidth = pPlayer->Get_Info()->fX - m_tInfo.fX;
					float fHeight = pPlayer->Get_Info()->fY - m_tInfo.fY;
					float fLength = sqrtf(fWidth * fWidth + fHeight * fHeight);

					if (fLength < 400)
					{
						pPlayer->MonsterExcStart(this);
					}
				}

				pMouse->Mouse_PreventEvent();
			}
		}
		
	}
}

void CObjMonsterFloatingBomb::On_Mouse_Key_Up(CObj* pMouse)
{
}

void CObjMonsterFloatingBomb::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CObjMonsterFloatingBomb::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}