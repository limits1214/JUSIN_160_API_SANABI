#include "pch.h"
#include "CObjPlayerSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjPlayer.h"


CObjPlayerSprite::CObjPlayerSprite()
{
	Set_DbgName(_T("CObjBossFireBird"));
}

CObjPlayerSprite::~CObjPlayerSprite()
{
	Release();
}

void CObjPlayerSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 91;
	m_tInfo.fCY = 64;
	m_tInfo.fCX = 112.f;
m_tInfo.fCY = 104.f;

	m_eFrameKey = FKI_Spr_SNB_SHEET_2;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_Sheet2.bmp", FrameKeyId_To_Text2(m_eFrameKey));
	m_tFrame.dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_eCurState = FSI_SNB_R_IDLE;
}

int CObjPlayerSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();
	auto parent = dynamic_cast<CObjPlayer*>(m_pParent);
	if (parent != nullptr)
	{
		auto state = parent->Get_PlayerState();
		if (state == FSI_SNB_R_RUNNING)
		{
			m_eCurState = FSI_SNB_R_RUNNING;
		}
		else if (state == FSI_SNB_R_IDLE)
		{
			m_eCurState = FSI_SNB_R_IDLE;
		}
		else if (state == FSI_SNB_R_RUNSTART)
		{
			m_eCurState = FSI_SNB_R_RUNSTART;
		}
		else if (state == FSI_SNB_R_RUNSTOP)
		{
			m_eCurState = FSI_SNB_R_RUNSTOP;
		}
		else if (state == FSI_SNB_R_JUMPING)
		{
			m_eCurState = FSI_SNB_R_JUMPING;
		}
		else if (state == FSI_SNB_R_FALLSTART)
		{
			m_eCurState = FSI_SNB_R_FALLSTART;
		}
		else if (state == FSI_SNB_R_FALLING)
		{
			m_eCurState = FSI_SNB_R_FALLING;
		}
		else if (state == FSI_SNB_R_WALLCLIMBUP)
		{
			m_eCurState = FSI_SNB_R_WALLCLIMBUP;
		}
		else if (state == FSI_SNB_R_WALLCLIMBDOWN)
		{
			m_eCurState = FSI_SNB_R_WALLCLIMBDOWN;
		}
		else if (state == FSI_SNB_R_SWING)
		{
			m_eCurState = FSI_SNB_R_SWING;
		}
		else if (state == FSI_SNB_R_DAMAGED)
		{
			m_eCurState = FSI_SNB_R_DAMAGED;
		}
		else if (state == FSI_SNB_R_DAMAGEDDASH)
		{
			m_eCurState = FSI_SNB_R_DAMAGEDDASH;
		}
	}

	return OBJ_NOEVENT;
}

void CObjPlayerSprite::Late_Update()
{
	Motion_Change();
}

void CObjPlayerSprite::Render(HDC hDC)
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

void CObjPlayerSprite::Release()
{
}
void CObjPlayerSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}