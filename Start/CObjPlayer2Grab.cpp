#include "pch.h"
#include "CObjPlayer2Grab.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjPlayer2.h"
#include "CCollisionMgr.h"
#include "CObjCollisionRect.h"
#include "CObjMgr.h"
#include "CObjPlayer2GrabSprite.h"

CObjPlayer2Grab::CObjPlayer2Grab()
{
	Set_DbgName(_T("CObjPlayer2GrabSprite"));
	ZeroMemory(&m_tCollisionRectInfo, sizeof(INFO));
}

CObjPlayer2Grab::~CObjPlayer2Grab()
{
	Release();
}

void CObjPlayer2Grab::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 45.f;

	m_bUseMainScroll = true;
	m_bCeiling = false;
	m_GrabSend = false;


	CObjPlayer2GrabSprite* pSprite = new CObjPlayer2GrabSprite;
	pSprite->Initialize();
	pSprite->Set_Pos(0, 0);
	pSprite->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pSprite);

	m_eGrabDir = DIR_RIGHT;

	//__super::Update_Rect();
}

int CObjPlayer2Grab::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	m_tInfo.fX += cosf(m_fRadian) * m_fSpeed;
	m_tInfo.fY += sinf(m_fRadian) * m_fSpeed;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2Grab::Late_Update()
{
}

void CObjPlayer2Grab::Render(HDC hDC)
{
	if (m_tRect.left == -10)
	{
		return;
	}
	
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjPlayer2Grab::Release()
{
}

void CObjPlayer2Grab::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	if (m_bDead)
		return;

	CObjCollisionRect* pRect = dynamic_cast<CObjCollisionRect*>(pObj);
	COLL_ETC_RECT_EX* pRectExCollEtc = static_cast<COLL_ETC_RECT_EX*>(etc);
	if (eCollID == COLL_RECT_EX && pRect != nullptr && pRectExCollEtc != nullptr)
	{
		m_fSpeed = 0.f;
		m_iCollisionOption = pRect->Get_Option();
		m_tCollisionRectInfo = *pRect->Get_Info();

		m_bCeiling = false;
		m_bCollisionRight = false;
		m_bCollisionLeft = false;

		// TODO: 들어간만큼 나오게
		COLL_ETC_RECT_EX rectExCollEtc = *pRectExCollEtc;
		float fDistance = rectExCollEtc.fDistance;
		switch (rectExCollEtc.eDir)
		{
		case DIR_UP:
		{
			m_tInfo.fY -= fDistance;
			m_eGrabDir = DIR_DOWN; 
		}
		break;
		case DIR_DOWN:
		{
			m_tInfo.fY += fDistance;
			m_bCeiling = true;
			m_eGrabDir = DIR_UP;
		}
		break;
		case DIR_LEFT:
		{
			m_tInfo.fX -= fDistance;
			m_bCollisionLeft = true;
			m_eGrabDir = DIR_RIGHT;
		}
		break;
		case DIR_RIGHT:
		{
			m_tInfo.fX += fDistance;
			m_bCollisionRight = true;
			m_eGrabDir = DIR_LEFT; 
		}
		break;
		}


		if (!m_GrabSend)
		{
			auto pPlayer = dynamic_cast<CObjPlayer2*>(m_pTarget);
			if (pPlayer != nullptr)
			{
				m_GrabSend = true;
				pPlayer->Grab(this);
			}
		}
	}
}
