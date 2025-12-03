#include "pch.h"
#include "CObjGrab.h"
#include "CObjCollisionRect.h"
#include "CCollisionMgr.h"
#include "CObjPlayer.h"

CObjGrab::CObjGrab()
	:m_fAngle(0.f)
{
	ZeroMemory(&m_tCollisionRectInfo, sizeof(INFO));
}

CObjGrab::~CObjGrab()
{
	Release();
}

void CObjGrab::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 50.f;

	m_bUseMainScroll = true;
	m_bCeiling = false;
}

int CObjGrab::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// 입력받고 그릴지 아니면 그리고 입력받을지...
	__super::Update_Rect();

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed;

	return OBJ_NOEVENT;
}

void CObjGrab::Late_Update()
{
}

void CObjGrab::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjGrab::Release()
{
}

void CObjGrab::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	CObjCollisionRect* pRect = dynamic_cast<CObjCollisionRect*>(pObj);
	COLL_ETC_RECT_EX* pRectExCollEtc = static_cast<COLL_ETC_RECT_EX*>(etc);
	if (eCollID == COLL_RECT_EX && pRect != nullptr && pRectExCollEtc != nullptr)
	{
		m_fSpeed = 0.f;

		auto pPlayer = dynamic_cast<CObjPlayer*>(m_pTarget);
		if (pPlayer != nullptr)
		{
			pPlayer->Grab(this);
		}

		m_tCollisionRectInfo = *pRect->Get_Info();

		// TODO: 들어간만큼 나오게
		COLL_ETC_RECT_EX rectExCollEtc = *pRectExCollEtc;
		float fDistance = rectExCollEtc.fDistance;
		switch (rectExCollEtc.eDir)
		{
		case DIR_UP:
		{
			m_tInfo.fY -= fDistance;
		}
		break;
		case DIR_DOWN:
		{
			m_tInfo.fY += fDistance;
			m_bCeiling = true;
		}
		break;
		case DIR_LEFT:
		{
			m_tInfo.fX -= fDistance;

		}
		break;
		case DIR_RIGHT:
		{
			m_tInfo.fX += fDistance;

		}
		break;
		}
	}
}
