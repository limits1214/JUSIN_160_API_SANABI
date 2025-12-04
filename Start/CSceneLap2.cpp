#include "pch.h"
#include "CSceneLap2.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CUIObjText.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"

CSceneLap2::CSceneLap2()
{
}

CSceneLap2::~CSceneLap2()
{
	Release();
}

void CSceneLap2::Initialize()
{
	info.fX = WINCX >> 1;
	info.fY = WINCY >>1;
	info.fCX = 10;
	info.fCY = 10;

	dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	deltaSum = 0.f;


	CUIObjText* pText = new CUIObjText;
	pText->Set_Pos(200, 200);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText);
	m_pText = pText;

	CUIObjText* pText2 = new CUIObjText;
	pText2->Set_Pos(200, 300);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText2);
	m_pText2 = pText2;

	CUIObjText* pText3 = new CUIObjText;
	pText3->Set_Pos(200, 400);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText3);
	m_pText3 = pText3;

	CUIObjText* pText4 = new CUIObjText;
	pText4->Set_Pos(200, 500);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText4);
	m_pText4 = pText4;

	m_fAngle = 45.f;
	//m_fG = 10.f;
	m_fG = 500.f;

	m_bStopDeltaSum = true;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"TILE_TEST");
}

int CSceneLap2::Update()
{
	CObjMgr::Get_Instance()->Update();

	rect.left = (LONG)((info.fX - info.fCX * 0.5f) );
	rect.top = (LONG)((info.fY - info.fCY * 0.5f) );
	rect.right = (LONG)((info.fX + info.fCX * 0.5f) );
	rect.bottom = (LONG)((info.fY + info.fCY * 0.5f) );

	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();

	DWORD delta = dwNow - dwTime;

	dwTime = dwNow;

	float deltaMs = (float)delta / 1000.f;
	if (m_bStopDeltaSum)
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing('R'))
		{
			deltaSum += (deltaMs * 4);
		}
		else
		{
			deltaSum += deltaMs;
		}
		
	}
	else
	{

	}
	

	//info.fX += cosf(deltaSum) * 1.f;
	//info.fY -= sinf(deltaSum) * 1.f;

	//float L = 100;
	//float ang =  PI / 6;
	//float g = 9.8;
	//float w = sqrtf(g / L);



	//{
	//	float L = 100.0f;        // 길이
	//	float ang_deg = 180.0f;   // 초기 각도 (도)
	//	float g = 9.8f;
	//	float ang0 = ang_deg * (3.1415926535f / 180.0f);  // 라디안 변환
	//	float w = sqrtf(g / L);  // 고유 진동수
	//	float theta = ang0 * cosf(w * deltaSum * 20); // t = 누적 시간
	//	float x = 200.0f + L * sinf(theta);
	//	float y = 200.0f + L * cosf(theta);
	//}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		
			m_fAngle += 1.f;
			if (m_fAngle < 180.f)
			{
		}
		
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		
			m_fAngle -= 1.f;
			if (m_fAngle > 0)
			{
		}
		
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		//m_fG -= 0.1f;
		
			m_fAngle -= 10;

			if (m_fAngle > -180)
			{
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		//m_fG += 0.1f;
		
			m_fAngle += 10;

			if (m_fAngle < 180)
			{
		}
	}



	// 
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			if (info.fX <= (WINCX >> 1))
			{
				// 진폭 늘리기
				if (m_fAngle <= 0)
				{
					//if (m_fAngle > -180)
						m_fAngle -= 10;
				}
				else
				{
					//if (m_fAngle < 180)
						m_fAngle += 10;
				}
			}
			else
			{
				// 진폭 줄이기
				if (m_fAngle <= 0)
				{
					//if (m_fAngle < -5)
						m_fAngle += 10;
				}
				else
				{
					//if (m_fAngle > 5)
						m_fAngle -= 10;
				}
			}
		}
		else
		{
			if (info.fX <= (WINCX >> 1))
			{
				// 진폭 늘리기
				if (m_fAngle <= 0)
				{
					if (m_fAngle > -180)
						--m_fAngle;
				}
				else
				{
					if (m_fAngle < 180)
						++m_fAngle;
				}
			}
			else
			{
				// 진폭 줄이기
				if (m_fAngle <= 0)
				{
					if (m_fAngle < -5)
						++m_fAngle;
				}
				else
				{
					if (m_fAngle > 5)
						--m_fAngle;
				}
			}
		}
		

		//if (m_fBeforeTargetAngle < m_fCurrentTargetAngle)
		//{
		//	// left to right
		//	if (info.fX <= (WINCX >> 1))
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			--m_fAngle;
		//		}
		//		else
		//		{
		//			++m_fAngle;
		//		}
		//	}
		//	else
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			++m_fAngle;
		//		}
		//		else
		//		{
		//			--m_fAngle;
		//		}
		//	}
		//}
		//else
		//{
		//	// right to left
		//	if (info.fX <= (WINCX >> 1))
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			--m_fAngle;
		//		}
		//		else
		//		{
		//			++m_fAngle;
		//		}
		//	}
		//	else
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			++m_fAngle;
		//		}
		//		else
		//		{
		//			--m_fAngle;
		//		}
		//	}
		//}
	}

	// 진폭 줄이기
	if (m_fAngle <= 0)
	{
		if (m_fAngle < -5)
			m_fAngle += 0.05;
	}
	else
	{
		if (m_fAngle > 5)
			m_fAngle -= 0.05;
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			// left to right
			if (info.fX <= (WINCX >> 1))
			{
				// 진폭 줄이기
				if (m_fAngle <= 0)
				{
					
						m_fAngle += 10;
				}
				else
				{
					
						m_fAngle -= 10;
				}
			}
			else
			{
				// 진폭 늘이기
				if (m_fAngle <= 0)
				{
					
						m_fAngle  -= 10;
				}
				else
				{
					
						m_fAngle += 10;
				}
			}
		}
		else
		{
			// left to right
			if (info.fX <= (WINCX >> 1))
			{
				// 진폭 줄이기
				if (m_fAngle <= 0)
				{
					if (m_fAngle < -5)
						++m_fAngle;
				}
				else
				{
					if (m_fAngle > 5)
						--m_fAngle;
				}
			}
			else
			{
				// 진폭 늘이기
				if (m_fAngle <= 0)
				{
					if (m_fAngle > -179)
						--m_fAngle;
				}
				else
				{
					if (m_fAngle < 179)
						++m_fAngle;
				}
			}
		}
		


		//if (m_fBeforeTargetAngle < m_fCurrentTargetAngle)
		//{
		//	// left to right
		//	if (info.fX <= (WINCX >> 1))
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			++m_fAngle;
		//		}
		//		else
		//		{
		//			--m_fAngle;
		//		}
		//	}
		//	else
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			--m_fAngle;
		//		}
		//		else
		//		{
		//			++m_fAngle;
		//		}
		//	}
		//}
		//else
		//{
		//	// right to left
		//	if (info.fX <= (WINCX >> 1))
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			++m_fAngle;
		//		}
		//		else
		//		{
		//			--m_fAngle;
		//		}
		//	}
		//	else
		//	{
		//		if (m_fAngle <= 0)
		//		{
		//			--m_fAngle;
		//		}
		//		else
		//		{
		//			++m_fAngle;
		//		}
		//	}
		//}
	}

	// 스탑 무빙
	// 속도를 
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		//m_fG = 9.8;F

		// 맞추고 싶은 속도
		float ang0 = m_fAngle * (PI / 180.0f);
		m_bStopDeltaSum = false;
		
		
		
		
	}

	if (CKeyMgr::Get_Instance()->Key_Up('S'))
	{
		//m_fG = 500;
		m_bStopDeltaSum = true;
	}




	float x = WINCX >> 1;
	float y = WINCY >> 1;

	float l = 100.f;

	float w = sqrtf(m_fG / l);
	float ang_deg = 45.0f;
	
	float ang0 = m_fAngle * (PI/ 180.0f);  // 라디안 변환

	//float a = -(w * w) * sinf(w * deltaSum + 0);
	//float v = a * deltaSum;
	//float ang = v * deltaSum;
	//deltaSum = 0;
	//float tar = ang0 * sinf(w * (deltaSum * 4) + (70.f * PI / 180.f));
	//deltaSum = 0;
	//float tar = ang0 * cosf(w * (deltaSum * 4) + (90.f * PI / 180.f));
	//float tar = ang0 * cosf(w * (deltaSum * 4) + ((90.f) - 45.f * PI / 180.f));
	// 양의 최대 파이는 0
	// 음의 최대 파이는 파이


	m_fBeforeTargetAngle = m_fCurrentTargetAngle;


	float tar = ang0 * cosf(w * (deltaSum ) + PI / 2);
	m_fCurrentTargetAngle = tar * (180.f / PI);
	
	//float tar = ang0 * cosf(w * (deltaSum * 4) + 0);

	info.fX = (WINCX >> 1) + sinf(tar) * l;
	info.fY = (WINCY >> 1) + cosf(tar) * l;

	TCHAR mText[256];
	swprintf_s(mText, _T("%f"), m_fCurrentTargetAngle);
	m_pText->Set_Text(mText);
	
	int tmp = 0;
	if (m_fAngle < 0)
	{
		tmp = 0;
	}
	else
	{
		tmp = 1;
	}


	TCHAR mText2[256];
	swprintf_s(mText2, _T("%f, %i"), m_fAngle, tmp);
	m_pText2->Set_Text(mText2);

	TCHAR mText3[256];
	swprintf_s(mText3, _T("%f"), m_fG);
	m_pText3->Set_Text(mText3);



	TCHAR mText4[256];
	if (m_fBeforeTargetAngle < m_fCurrentTargetAngle)
	{
		swprintf_s(mText4, _T("%s"), _T("left to right"));
	}
	else
	{
		swprintf_s(mText4, _T("%s"), _T("right to left"));
	}
	
	m_pText4->Set_Text(mText4);

	return 0;
}

void CSceneLap2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneLap2::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);

	

	MoveToEx(hDC, 0, (WINCY >> 1) + 0, nullptr);
	LineTo(hDC, WINCX, (WINCY >> 1) + 0);

	MoveToEx(hDC, 0, (WINCY >> 1) + 100, nullptr);
	LineTo(hDC, WINCX, (WINCY >> 1) + 100);

	MoveToEx(hDC, WINCX >> 1, 0, nullptr);
	LineTo(hDC, WINCX >> 1, (WINCY));

	

	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
}

void CSceneLap2::Release()
{
	CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
