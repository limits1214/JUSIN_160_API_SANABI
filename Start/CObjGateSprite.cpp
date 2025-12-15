#include "pch.h"
#include "CObjGateSprite.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTimeMgr.h"
#include "CSoundMgr.h"
CObjGateSprite::CObjGateSprite()
{
	Set_DbgName(_T("CObjGateSprite"));
}

CObjGateSprite::~CObjGateSprite()
{
	Release();
}

void CObjGateSprite::Initialize()
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;
	m_eFrameKey = FKI_GATE_SHEET;
	m_eCurState = FSI_GATE_IDLE;
	//m_tFrame = FrameStateId_To_Frame(FSI_GATE_CLOSE, CTimeMgr::Get_Instance()->Get_Tick_Count());
	m_bOpening = false;
	m_bClosing = false;
	m_bIdle = true;
}

int CObjGateSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	int end = 19;
	if (m_bClosing)
	{
		if (m_tFrame.iStart == end)
		{
			m_bClosing = false;
			m_bIdle = true;
			m_eCurState = FSI_GATE_IDLE;
		}
	}
	else if (m_bOpening)
	{
		if (m_tFrame.iStart == end)
		{
			m_bOpening = false;
			m_bIdle = true;
			m_eCurState = FSI_END;
		}
	}
	Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjGateSprite::Late_Update()
{
	Motion_Change();
}

void CObjGateSprite::Render(HDC hDC)
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

void CObjGateSprite::Release()
{
}

void CObjGateSprite::GateOpen()
{
	if (!m_bOpening)
	{
		cout << "GATEOPEN" << endl;
		m_bOpening = true;
		m_bIdle = false;
		m_eCurState = FSI_GATE_OPEN;
		//CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_GATE_OPEN);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_BattleGate_Open.wav", SOUND_SFX_GATE_OPEN, 1.f);
	}
}

void CObjGateSprite::GateClose()
{
	if (!m_bClosing)
	{
		m_bClosing = true;
		m_bIdle = false;
		m_eCurState = FSI_GATE_CLOSE;
		//CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_GATE_CLOSE);
		CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap4_BattleGate_Close.wav", SOUND_SFX_GATE_CLOSE, 1.f);
	}
}

void CObjGateSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		if (m_eCurState == FSI_END)
		{
			m_eFrameKey = FKI_END;
			return;
		}
		else {
			m_eFrameKey = FKI_GATE_SHEET;
		}
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}