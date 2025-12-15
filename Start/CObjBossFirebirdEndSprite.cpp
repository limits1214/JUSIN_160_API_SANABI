#include "pch.h"
#include "CObjBossFirebirdEndSprite.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CGameStorageMgr.h"

CObjBossFirebirdEndSprite::CObjBossFirebirdEndSprite()
{
}

CObjBossFirebirdEndSprite::~CObjBossFirebirdEndSprite()
{
	Release();
}

void CObjBossFirebirdEndSprite::Initialize()
{
	Set_Pos((WINCX), (WINCY));
	Set_CX(174);
	Set_CY(95);
	Set_FrameKeyId(FKI_FIREBIRD_END_SHEET);
	Set_Frame(FrameStateId_To_Frame(FSI_FIREBIRD_END, CTimeMgr::Get_Instance()->Get_Tick_Count()));
	__super::Update_Rect();
}

int CObjBossFirebirdEndSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(135.f * PI / 180.f) * 2;
	m_tInfo.fY -= sinf(135.f * PI / 180.f) * 2;

	Move_Frame();
	int end = 57;
	if (m_tFrame.iStart == end)
	{
		CGameStorageMgr::Get_Instance()->Set_BossDeadEnd(true);
		//parent->m_eAniStateGun = CObjBossFireBird::ANI_STATE_GUN::GUNSHOOTSTART_END;
	}
	

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjBossFirebirdEndSprite::Late_Update()
{
}

void CObjBossFirebirdEndSprite::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));

	//GdiTransparentBlt(hDC,				// 복사 받을 DC
	//	m_tRect.left ,	// 복사 받을 공간의 LEFT	
	//	m_tRect.top ,				// 복사 받을 공간의 TOP
	//	(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
	//	(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	0,					// 복사할 이미지의 LEFT, TOP
	//	0,
	//	(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
	//	(INT)m_tInfo.fCY,
	//	RGB(255, 255, 255));	// 제거할 색상


	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjBossFirebirdEndSprite::Release()
{
}
