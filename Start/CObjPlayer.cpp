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

	auto a = CBmpMgr::Get_Instance();

	m_eFrameKey = FKI_SNB;
	//TCHAR szFrameKey[256]{};
	//FrameKeyId_To_Text(m_eFrameKey, szFrameKey);
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_SHEET.bmp", szFrameKey);
	
	//TCHAR szFrameKey[256]{};
	;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_SHEET.bmp", FrameKeyId_To_Text2(m_eFrameKey));
	
	m_tFrame.dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_eCurState = IDLE;

	m_bUseMainScroll = true;
}

int CObjPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	// 입력받고 그릴지 아니면 그리고 입력받을지...
	__super::Update_Rect();


	m_eCurState = IDLE;
	Key_Input();

	Move_Frame();

	

	return OBJ_NOEVENT;
}

void CObjPlayer::Late_Update()
{
	Offset();
	Motion_Change();
}

void CObjPlayer::Render(HDC hDC)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
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
		m_tRect.left , m_tRect.top,
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
	//TCHAR szFrameKey[256]{};
	//FrameKeyId_To_Text(m_eFrameKey, szFrameKey);
	//CBmpMgr::Get_Instance()->Delete_Bmp(szFrameKey);
}
void CObjPlayer::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	if (eCollID == COLL_LINE)
	{
		float targetY = *static_cast<float*>(etc);

		if (
			// under margin
			(targetY + (m_tInfo.fCY * 0.5f) > m_tInfo.fY)
			&&
			// top margin
			(targetY - (m_tInfo.fCY * 0.5f) < m_tInfo.fY)
			)
		{
			
			m_tInfo.fY = targetY - (m_tInfo.fCY * 0.5f);

			//if (
			//	// under margin
			//	(targetY + (m_tInfo.fCY * 0) > m_tInfo.fY)
			//	&&
			//	// top margin
			//	(targetY - (m_tInfo.fCY * 0.5) < m_tInfo.fY)
			//	)
			//{
			//	
			//}
		}
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


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{

		m_tInfo.fY -= 5;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += 5;
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
	return;
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
