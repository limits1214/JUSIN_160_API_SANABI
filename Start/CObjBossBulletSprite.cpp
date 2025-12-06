#include "pch.h"
#include "CObjBossBulletSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjBossBulletSprite::CObjBossBulletSprite()
	:m_iOption(0)
{
}

CObjBossBulletSprite::~CObjBossBulletSprite()
{
	Release();
}

void CObjBossBulletSprite::Initialize()
{
	m_bUseMainScroll = true;

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 58;
	m_eFrameKey = FKI_Spr_BOSS_Bullet_Sheet;

	m_tFrame = FrameStateId_To_Frame(FSI_BOSS_BULLET_BOMB, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossBulletSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBossBulletSprite::Late_Update()
{
}

void CObjBossBulletSprite::Render(HDC hDC)
{
	m_tFrame.iMotion = m_iOption;
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjBossBulletSprite::Release()
{
}
