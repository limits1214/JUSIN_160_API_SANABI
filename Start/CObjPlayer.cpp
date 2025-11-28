#include "pch.h"
#include "CObjPlayer.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CScrollMgr.h"


CObjPlayer::CObjPlayer()
{
}

CObjPlayer::~CObjPlayer()
{
	Release();
}

void CObjPlayer::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_SHEET.bmp", L"SNB");
	m_pFrameKey = _T("SNB");

	
	m_tFrame.dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_eCurState = IDLE;
}

int CObjPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	m_eCurState = IDLE;
	Key_Input();

	Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjPlayer::Late_Update()
{
	Offset();
	Motion_Change();
}

void CObjPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	//GdiTransparentBlt(hDC,				// 복사 받을 DC
	//	m_tRect.left + iScrollX,	// 복사 받을 공간의 LEFT	
	//	m_tRect.top + iScrollY,				// 복사 받을 공간의 TOP
	//	(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
	//	(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	m_tFrame.iStart * (int)m_tInfo.fCX,					// 복사할 이미지의 LEFT, TOP
	//	m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
	//	(INT)m_tInfo.fCY,
	//	RGB(255, 0, 255));	// 제거할 색상

	BmpRender(
		hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,(int) m_tInfo.fCY
		);



	//float angleDeg = 45.f;
	//float angle = angleDeg * 3.14159265f / 180.0f;

	//POINT pt[3];

	//float cosA = cos(angle);
	//float sinA = sin(angle);
	//float w = m_tInfo.fCX;
	//float h = m_tInfo.fCY;
	//float cx = w / 2.0f;
	//float cy = h / 2.0f;
	//float ox = m_tInfo.fX;
	//float oy = m_tInfo.fY;

	//// 1) Left-Top
	////pt[0].x = (LONG)(ox + (-cx * cosA - -cy * sinA));
	////pt[0].y = (LONG)(oy + (-cx * sinA + -cy * cosA));

	////// 2) Right-Top
	////pt[1].x = (LONG)(ox + ((w - cx) * cosA - -cy * sinA));
	////pt[1].y = (LONG)(oy + ((w - cx) * sinA + -cy * cosA));

	////// 3) Left-Bottom
	////pt[2].x = (LONG)(ox + (-cx * cosA - (h - cy) * sinA));
	////pt[2].y = (LONG)(oy + (-cx * sinA + (h - cy) * cosA));

	//int newW = w * 2;
	//int newH = h * 2;
	//int x = m_tInfo.fX;
	//int y = m_tInfo.fY;

	//pt[0] = { x, y };
	//pt[1] = { x + newW, y };
	//pt[2] = { x, y + newH };



	//HDC hdcSrc = CreateCompatibleDC(hDC);
	//HBITMAP hbmSrc = CreateCompatibleBitmap(hDC, w, h);
	//HBITMAP oldSrcBmp = (HBITMAP)SelectObject(hdcSrc, hbmSrc);

	//BitBlt(hdcSrc, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);

	//HDC hdcMask = CreateCompatibleDC(hDC);
	//HBITMAP hbmMask = CreateBitmap(w, h, 1, 1, NULL);
	//HBITMAP oldMaskBmp = (HBITMAP)SelectObject(hdcMask, hbmMask);

	//COLORREF oldBk = SetBkColor(hdcSrc, RGB(255, 0, 255));
	//BitBlt(hdcMask, 0, 0, w, h, hdcSrc, 0, 0, SRCCOPY);

	//SetBkColor(hdcSrc, oldBk);

	//BitBlt(hdcMask, 0, 0, w, h, NULL, 0, 0, DSTINVERT);

	//PlgBlt(hDC, pt, hdcSrc,
	//	0,
	//	0,
	//	w, h, hbmMask, 0, 0);

	//SelectObject(hdcSrc, oldSrcBmp);
	//SelectObject(hdcMask, oldMaskBmp);
	//DeleteObject(hbmSrc);
	//DeleteObject(hbmMask);
	//DeleteDC(hdcSrc);
	//DeleteDC(hdcMask);

}

void CObjPlayer::Release()
{
}
void CObjPlayer::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	if (eCollID == COLL_LINE)
	{
		float targetY = *static_cast<float*>(etc);
		m_tInfo.fY = targetY;
	}
}
void CObjPlayer::Key_Input()
{
	bool bPressingA = CKeyMgr::Get_Instance()->Key_Pressing('A');
	bool bPressingD = CKeyMgr::Get_Instance()->Key_Pressing('D');
	bool bKeyDownSpace = CKeyMgr::Get_Instance()->Key_Down(VK_SPACE);

	if (bPressingA)
	{
		m_tInfo.fX -= 3.f;
		m_eCurState = RUNNING;
	}

	if (bPressingD)
	{
		m_tInfo.fX += 3.f;
		m_eCurState = RUNNING;
	}

	if (bKeyDownSpace)
	{
		m_eCurState = JUMP;
	}
}

void CObjPlayer::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		case RUNNING:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 19;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = dwNow;
			break;
		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CObjPlayer::Offset()
{
	int	iOffsetminX = 100;
	int	iOffsetmaxX = 700;

	int	iOffsetminY = 100;
	int	iOffsetmaxY = 500;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 왼쪽으로 플레이어가 이동 중
	if (iOffsetminX > m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(3.f);
	}

	// 오른쪽으로 플레이어가 이동 중
	if (iOffsetmaxX < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-3.f);
	}


	if (iOffsetminY > m_tInfo.fY + iScrollY)
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(3.f);
	}

	if (iOffsetmaxY < m_tInfo.fY + iScrollY)
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-3.f);
	}

}
