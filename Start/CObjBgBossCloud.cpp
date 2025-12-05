#include "pch.h"
#include "CObjBgBossCloud.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjBgBossCloud::CObjBgBossCloud()
    :m_iOption(0)
{
}

CObjBgBossCloud::~CObjBgBossCloud()
{
    Release();
}

void CObjBgBossCloud::Initialize()
{
	m_tInfo.fCX = 144;
	m_tInfo.fCY = 44;
    m_eFrameKey = FKI_Spr_Chap5_Heli_Cloud_Sheet;
	
    m_tFrame = FrameStateId_To_Frame(FSI_BOSS_BG_CLOUD_0, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBgBossCloud::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CObjBgBossCloud::Late_Update()
{
}

void CObjBgBossCloud::Render(HDC hDC)
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

void CObjBgBossCloud::Release()
{
}
