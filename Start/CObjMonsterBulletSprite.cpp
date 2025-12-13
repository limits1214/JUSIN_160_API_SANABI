#include "pch.h"
#include "CObjMonsterBulletSprite.h"
#include "CObjMonsterBullet.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjMonsterBulletSprite::CObjMonsterBulletSprite()
{
}

CObjMonsterBulletSprite::~CObjMonsterBulletSprite()
{
}

void CObjMonsterBulletSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;


	m_eFrameKey = FKI_Spr_MONSTER_BULLET_SHEET;
	m_eCurState = FSI_MONSTER_BULLET;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
	//m_fAngle = 0.f;
}

int CObjMonsterBulletSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterBulletSprite::Late_Update()
{
	Motion_Change();
	CObjMonsterBullet* parent = dynamic_cast<CObjMonsterBullet*>(m_pParent);
	if (parent != nullptr)
	{
		float angle = parent->Get_Angle();

		// 사진이 기본각도가 90도라 조정해줌
		angle -= 90.f;


		float		fDistance = sqrtf((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) +
			(m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

		// 좌 상단
		m_tPoint[0].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 135.f) * PI / 180.f));
		m_tPoint[0].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 135.f) * PI / 180.f));

		// 우 상단
		m_tPoint[1].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 45.f) * PI / 180.f));
		m_tPoint[1].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 45.f) * PI / 180.f));

		// 좌 상단
		m_tPoint[2].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 225.f) * PI / 180.f));
		m_tPoint[2].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 225.f) * PI / 180.f));
	}
}

void CObjMonsterBulletSprite::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	HDC		hPlgDC = CBmpMgr::Get_Instance()->Find_Image(_T("BulletPLG"));
	HDC		hResetDC = CBmpMgr::Get_Instance()->Find_Image(_T("BulletRESET"));
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//BmpRender(
	//	hDC,
	//	m_tRect.left, m_tRect.top,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,

	//	hMemDC,
	//	m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY
	//);

	BitBlt(hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		SRCCOPY);

	PlgBlt(hPlgDC,
		m_tPoint,
		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		NULL, NULL, NULL);

	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);

	BitBlt(hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0, 0, SRCCOPY);

}

void CObjMonsterBulletSprite::Release()
{
}

void CObjMonsterBulletSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
