#include "pch.h"
#include "CObjBgTutoCloud.h"
#include "CBmpMgr.h"

CObjBgTutoCloud::CObjBgTutoCloud()
{
}

CObjBgTutoCloud::~CObjBgTutoCloud()
{
}

void CObjBgTutoCloud::Initialize()
{
	Set_FrameKeyId(FKI_Spr_BG_TUTO_CLOUD);
	//Set_Pos((1920 / 2) , WINCY >> 1);
	Set_CX(1171);
	Set_CY(369);
}

int CObjBgTutoCloud::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBgTutoCloud::Late_Update()
{
}

void CObjBgTutoCloud::Render(HDC hDC)
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

void CObjBgTutoCloud::Release()
{
}

