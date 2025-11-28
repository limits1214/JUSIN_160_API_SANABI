#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
CPlayer::CPlayer()
{
	Set_DbgName(_T("Player"));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 100.f, WINCY >> 1, 60.f, 60.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_SHEET.bmp", L"SNB");

	m_pFrameKey = _T("SNB");
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.iMotion = 4;
	m_tFrame.dwSpeed = 200;
	
	m_eCurState = IDLE;
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();
	__super::Update_Rect();
	__super::Move_Frame();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	//Motion_Change();
}

void DrawRotated(HDC destDC, HDC srcDC, int x, int y, int w, int h, float angleDeg)
{
	float angle = angleDeg * 3.14159265f / 180.0f;

	// 중심 기준 회전 계산을 위해 중심점 구함
	float cx = w / 2.0f;
	float cy = h / 2.0f;

	// 회전 후 3점 좌표
	POINT pt[3];

	float cosA = cos(angle);
	float sinA = sin(angle);

	// 목적지 좌표 (회전 중심 x,y)
	float ox = x;
	float oy = y;

	// 1) Left-Top
	pt[0].x = (LONG)(ox + (-cx * cosA - -cy * sinA));
	pt[0].y = (LONG)(oy + (-cx * sinA + -cy * cosA));

	// 2) Right-Top
	pt[1].x = (LONG)(ox + ((w - cx) * cosA - -cy * sinA));
	pt[1].y = (LONG)(oy + ((w - cx) * sinA + -cy * cosA));

	// 3) Left-Bottom
	pt[2].x = (LONG)(ox + (-cx * cosA - (h - cy) * sinA));
	pt[2].y = (LONG)(oy + (-cx * sinA + (h - cy) * cosA));

	// 1. 원본을 받을 비트맵 + DC
	HDC hdcSrc = CreateCompatibleDC(destDC);
	HBITMAP hbmSrc = CreateCompatibleBitmap(destDC, w, h);
	HBITMAP oldSrcBmp = (HBITMAP)SelectObject(hdcSrc, hbmSrc);

	// srcDC의 (0,0,w,h)을 hdcSrc로 복사
	BitBlt(hdcSrc, 0, 0, w, h, srcDC, 0, 0, SRCCOPY);

	// 2. 마스크 DC/비트맵 만들기
	HDC hdcMask = CreateCompatibleDC(destDC);
	HBITMAP hbmMask = CreateBitmap(w, h, 1, 1, NULL);
	HBITMAP oldMaskBmp = (HBITMAP)SelectObject(hdcMask, hbmMask);

	COLORREF oldBk = SetBkColor(hdcSrc, RGB(255, 0, 255));
	BitBlt(hdcMask, 0, 0, w, h, hdcSrc, 0, 0, SRCCOPY);

	SetBkColor(hdcSrc, oldBk);

	// 2-2. 마스크 반전: 배경(마젠타)=0, 캐릭터=1이 되도록
	BitBlt(hdcMask, 0, 0, w, h, NULL, 0, 0, DSTINVERT);

	// 3. PlgBlt
	PlgBlt(destDC, pt, hdcSrc, 0, 0, w, h, hbmMask, 0, 0);

	// 4. 정리
	SelectObject(hdcSrc, oldSrcBmp);
	SelectObject(hdcMask, oldMaskBmp);
	DeleteObject(hbmSrc);
	DeleteObject(hbmMask);
	DeleteDC(hdcSrc);
	DeleteDC(hdcMask);
}
void CPlayer::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//GdiTransparentBlt(hDC,				// 복사 받을 DC
	//	m_tRect.left ,	// 복사 받을 공간의 LEFT	
	//	m_tRect.top ,				// 복사 받을 공간의 TOP
	//	(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
	//	(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	0,					// 복사할 이미지의 LEFT, TOP
	//	0,
	//	(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
	//	(INT)m_tInfo.fCY,
	//	RGB(0, 0, 0));	// 제거할 색상

	//HDC tempDC = CreateCompatibleDC(hDC);
	//HBITMAP tempBmp = CreateCompatibleBitmap(hDC, 60, 60);
	//SelectObject(tempDC, tempBmp);

	//BitBlt(tempDC,
	//0,
	//0,
	//m_tInfo.fCX,
	//m_tInfo.fCY,
	//hMemDC,
	//0,
	//0,
	//SRCCOPY);

	DrawRotated(hDC, hMemDC, 300, 200, 60, 60, 45.0f);

	//GdiTransparentBlt(tempDC,				// 복사 받을 DC
	//	m_tRect.left ,	// 복사 받을 공간의 LEFT	
	//	m_tRect.top,				// 복사 받을 공간의 TOP
	//	(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
	//	(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	0,					// 복사할 이미지의 LEFT, TOP
	//	0,
	//	(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
	//	(INT)m_tInfo.fCY,
	//	RGB(255, 0, 255));	// 제거할 색상

	


	//BitBlt(hDC,
	//	0,
	//	0,
	//	m_tInfo.fCX,
	//	m_tInfo.fCY,
	//	tempDC,
	//	0,
	//	0,
	//	SRCCOPY);
}


void CPlayer::Release()
{
	CBmpMgr::Get_Instance()->Delete_Bmp(L"Player_DOWN");
	CBmpMgr::Get_Instance()->Delete_Bmp(L"Player_UP");
	CBmpMgr::Get_Instance()->Delete_Bmp(L"Player_LEFT");
	CBmpMgr::Get_Instance()->Delete_Bmp(L"Player_RIGHT");
	CBmpMgr::Get_Instance()->Delete_Bmp(L"SNB");
}

void CPlayer::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= 5.f;
		//m_pFrameKey = _T("Player_LEFT");
		m_eCurState = WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += 5.f;
		//m_pFrameKey = _T("Player_RIGHT");
		m_eCurState = WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= 5.f;
		//m_pFrameKey = _T("Player_UP");
		m_eCurState = WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += 5.f;
		//m_pFrameKey = _T("Player_DOWN");
		m_eCurState = WALK;
	}
	else
		m_eCurState = IDLE;
}

void CPlayer::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		case HIT:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = dwNow;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
