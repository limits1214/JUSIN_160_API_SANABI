#include "pch.h"
#include "CObjMonsterDefenderBulletSprite.h"
#include "pch.h"
#include "CObjMonsterDefenderBullet.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjMonsterDefenderBulletSprite::CObjMonsterDefenderBulletSprite()
{
}

CObjMonsterDefenderBulletSprite::~CObjMonsterDefenderBulletSprite()
{
}

void CObjMonsterDefenderBulletSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 100;
	m_tInfo.fCY = 100;


	m_eFrameKey = FKI_Spr_DEFENDER_BULLET_SHEET;
	m_eCurState = FSI_DEFENDER_BULLET;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
	//m_fAngle = 0.f;
}

int CObjMonsterDefenderBulletSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterDefenderBulletSprite::Late_Update()
{
	Motion_Change();
	CObjMonsterDefenderBullet* parent = dynamic_cast<CObjMonsterDefenderBullet*>(m_pParent);
	if (parent != nullptr)
	{
		float angle = parent->Get_Angle();

		angle -= 90.f;


		float		fDistance = sqrtf((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) +
			(m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

		// ÁÂ »ó´Ü
		m_tPoint[0].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 135.f) * PI / 180.f));
		m_tPoint[0].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 135.f) * PI / 180.f));

		// ¿ì »ó´Ü
		m_tPoint[1].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 45.f) * PI / 180.f));
		m_tPoint[1].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 45.f) * PI / 180.f));

		// ÁÂ »ó´Ü
		m_tPoint[2].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 225.f) * PI / 180.f));
		m_tPoint[2].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 225.f) * PI / 180.f));
	}
}

void CObjMonsterDefenderBulletSprite::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	HDC		hPlgDC = CBmpMgr::Get_Instance()->Find_Image(_T("DefenderBulletPLG"));
	HDC		hResetDC = CBmpMgr::Get_Instance()->Find_Image(_T("DefenderBulletRESET"));
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

void CObjMonsterDefenderBulletSprite::Release()
{
}

void CObjMonsterDefenderBulletSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
