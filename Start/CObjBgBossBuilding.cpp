#include "pch.h"
#include "CObjBgBossBuilding.h"
#include "CBmpMgr.h"

CObjBgBossBuilding::CObjBgBossBuilding()
{
}

CObjBgBossBuilding::~CObjBgBossBuilding()
{
}

void CObjBgBossBuilding::Initialize()
{
	Set_FrameKeyId(FKI_Spr_Chap5_Chap4_Building);
	//Set_Pos((1920 / 2) , WINCY >> 1);
	//Set_CX(1920);
	//Set_CY(1280);
}

int CObjBgBossBuilding::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBgBossBuilding::Late_Update()
{
}

void CObjBgBossBuilding::Render(HDC hDC)
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

void CObjBgBossBuilding::Release()
{
}

