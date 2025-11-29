#include "pch.h"
#include "CObjTile.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

CObjTile::CObjTile()
{
}

CObjTile::~CObjTile()
{
}

void CObjTile::Initialize()
{
	Set_CX(TILECX);
	Set_CY(TILECY);
}

int CObjTile::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjTile::Late_Update()
{
}

void CObjTile::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_szFrameKey);

	BmpRender(
		hDC,
		m_tRect.left + iScrollX + (TILECX >> 1), m_tRect.top + iScrollY + (TILECX >> 1),
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjTile::Release()
{
}
