#include "pch.h"
#include "CObjBgTutoMountain.h"
#include "CBmpMgr.h"

CObjBgTutoMountain::CObjBgTutoMountain()
{
}

CObjBgTutoMountain::~CObjBgTutoMountain()
{
}

void CObjBgTutoMountain::Initialize()
{
	Set_FrameKeyId(FKI_Spr_BG_TUTO_MOUNTAIN);
	//Set_Pos((1920 / 2) , WINCY >> 1);
	Set_CX(1426);
	Set_CY(528);
}

int CObjBgTutoMountain::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBgTutoMountain::Late_Update()
{
}

void CObjBgTutoMountain::Render(HDC hDC)
{
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

void CObjBgTutoMountain::Release()
{
}

