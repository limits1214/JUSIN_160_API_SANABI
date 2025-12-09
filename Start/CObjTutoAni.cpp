#include "pch.h"
#include "CObjTutoAni.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"

CObjTutoAni::CObjTutoAni()
	:m_iOption(0)
{
}

CObjTutoAni::~CObjTutoAni()
{
	Release();
}

void CObjTutoAni::Initialize()
{
	m_tInfo.fCX = 156;
	m_tInfo.fCY = 157;
	m_eFrameKey = FKI_Spr_TUTO_ANI_SHEET;
	FRAME_STATE_ID fsi = FSI_TUTO_ANI_JUMP;
	if (m_iOption == 0)
	{
		 fsi = FSI_TUTO_ANI_CEILING_STICK;
	}
	else if (m_iOption == 1)
	{
		 fsi = FSI_TUTO_ANI_JUMP;
	}
	else if (m_iOption == 2)
	{
		 fsi = FSI_TUTO_ANI_WALLJUMP;
	}
	else if (m_iOption == 3)
	{
		 fsi = FSI_TUTO_ANI_WALLUPDOWN;
	}
	else if (m_iOption == 4)
	{
		 fsi = FSI_TUTO_ANI_WINDING;
	}
	else if (m_iOption == 5)
	{
		 fsi = FSI_TUTO_ANI_SWINGDASH;
	}
	else if (m_iOption == 6)
	{
		 fsi = FSI_TUTO_ANI_WINDINGNEW;
	}
	m_tFrame = FrameStateId_To_Frame(fsi, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjTutoAni::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjTutoAni::Late_Update()
{
}

void CObjTutoAni::Render(HDC hDC)
{
	//m_tFrame.iMotion = m_iOption;
	//m_tFrame = FrameStateId_To_Frame(FSI_TUTO_ANI_JUMP, CTimeMgr::Get_Instance()->Get_Tick_Count());
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

void CObjTutoAni::Release()
{
}
