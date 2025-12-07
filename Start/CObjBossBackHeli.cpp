#include "pch.h"
#include "CObjBossBackHeli.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"

CObjBossBackHeli::CObjBossBackHeli()
{
}

CObjBossBackHeli::~CObjBossBackHeli()
{
}

void CObjBossBackHeli::Initialize()
{
	//m_bUseMainScroll = true;
	m_tInfo.fCX = 153.f;
	m_tInfo.fCY = 74.f;
	Set_FrameKeyId(FKI_Spr_BackHeliMove_Loop);
	m_tFrame = FrameStateId_To_Frame(FSI_BACK_HELI_MOVE_LOOP, CTimeMgr::Get_Instance()->Get_Tick_Count());
	m_fSpeed = 5.f;
}

int CObjBossBackHeli::Update()
{

	if (m_bDead)
		return OBJ_DEAD;

	float width = m_fMoveTargetX - m_tInfo.fX;
	float height = m_fMoveTargetY - m_tInfo.fY;

	float length = sqrtf(width * width + height * height);

	if (length > m_fSpeed)
	{
		float rad = atan2f(height, width);

		m_tInfo.fX += cosf(rad) * m_fSpeed;
		m_tInfo.fY += sinf(rad) * m_fSpeed;
	}

	

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjBossBackHeli::Late_Update()
{
}

void CObjBossBackHeli::Render(HDC hDC)
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

void CObjBossBackHeli::Release()
{
}

