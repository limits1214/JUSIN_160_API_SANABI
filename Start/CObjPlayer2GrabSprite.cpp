#include "pch.h"
#include "CObjPlayer2GrabSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjPlayer2Grab.h"

CObjPlayer2GrabSprite::CObjPlayer2GrabSprite()
{
	Set_DbgName(_T("CObjPlayer2GrabSprite"));
}

CObjPlayer2GrabSprite::~CObjPlayer2GrabSprite()
{
	Release();
}

void CObjPlayer2GrabSprite::Initialize()
{
	m_bSkipFirstRender = true;
	Set_UseMainScroll(true);
	m_tInfo.fCX = 46;
	m_tInfo.fCY = 44;

	m_eFrameKey = FKI_Spr_SNB_GRAB_SHEET;
	m_eCurState = FSI_GRAB_TOP;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());

	//__super::Update_Rect();
}

int CObjPlayer2GrabSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	CObjPlayer2Grab* parent = dynamic_cast<CObjPlayer2Grab*>(m_pParent);
	if (parent != nullptr)
	{
		switch (parent->Get_GrabDir())
		{
		case DIR_LEFT:
			m_eCurState = FSI_GRAB_LEFT;
			break;
		case DIR_UP:
			m_eCurState = FSI_GRAB_TOP;
			break;
		case DIR_RIGHT:
			m_eCurState = FSI_GRAB_RIGHT;
			break;
		case DIR_DOWN:
			m_eCurState = FSI_GRAB_BOTTOM;
			break;
		}
	}

	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	
	bool bMove = true;
	int end = FrameStateId_To_Frame(m_eCurState, dwNow).iEnd;
	if (m_tFrame.iStart == end)
	{
		bMove = false;
	}

	if (bMove)
	{
		Move_Frame();
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2GrabSprite::Late_Update()
{
	Motion_Change();
}

void CObjPlayer2GrabSprite::Render(HDC hDC)
{
	// юс╫ц
	if (m_tRect.left == -23)
		return;

	if (m_tRect.left == 76)
		return;
	if (m_tRect.left == 0)
		return;

	if (m_bSkipFirstRender)
	{
		m_bSkipFirstRender = false;
		return;
	}


	cout << "mtrectleft" << m_tRect.left << endl;
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

void CObjPlayer2GrabSprite::Release()
{
}

void CObjPlayer2GrabSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}

void CObjPlayer2GrabSprite::AniStateUpdate()
{
	//Move_Frame();

}
