#include "pch.h"
#include "CObjBg.h"
#include "CBmpMgr.h"
CObjBg::CObjBg()
{
}

CObjBg::~CObjBg()
{
}

void CObjBg::Initialize()
{
  /*  m_tInfo.fCX = 832;
    m_tInfo.fCX = 448;*/

    //m_eFrameKey = FKI_Spr_BG_Mat_Chap5_Heli_Sky;
}

int CObjBg::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	//Move_Frame();


	return OBJ_NOEVENT;
}

void CObjBg::Late_Update()
{
}

void CObjBg::Render(HDC hDC)
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

void CObjBg::Release()
{
}
