#include "pch.h"
#include "CKeyMgr2.h"

CKeyMgr2* CKeyMgr2::m_pInstance = nullptr;

CKeyMgr2::CKeyMgr2()
{
	ZeroMemory(m_bKeyPressingState, sizeof(m_bKeyPressingState));
	ZeroMemory(m_bKeyUpState, sizeof(m_bKeyUpState));
	ZeroMemory(m_bKeyDownState, sizeof(m_bKeyDownState));
}

CKeyMgr2::~CKeyMgr2()
{
	Release();
}

void CKeyMgr2::Update()
{
	//for (int i = 0; i < VK_MAX; ++i)
	//{
	//	if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
	//		m_bKeyState[i] = !m_bKeyState[i];

	//	if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))
	//		m_bKeyState[i] = !m_bKeyState[i];
	//}
	ZeroMemory(m_bKeyUpState, sizeof(m_bKeyUpState));
	ZeroMemory(m_bKeyDownState, sizeof(m_bKeyDownState));

	for (int i = 0; i < VK_MAX; ++i)
	{
		bool nowPressed = GetAsyncKeyState(i) & 0x8000;
		//이전에 누르고 있었고
		if (m_bKeyPressingState[i])
		{	
			// 현재 누르고 있으면
			if (nowPressed)
			{
				
			}
			// 현재 안눌렀으면
			else
			{
				m_bKeyUpState[i] = true;
			}
		}
		// 이전에 안누르고 있엇고
		else
		{
			// 현재 누르고 있으면
			if (nowPressed)
			{
				m_bKeyDownState[i] = true;
			}
			// 현재 안눌렀으면
			else
			{

			}
		}
		m_bKeyPressingState[i] = nowPressed;
	}

}

bool CKeyMgr2::Key_Pressing(int _iKey)
{
	return m_bKeyPressingState[_iKey];
}

// 이전에는 누른 적이 없고, 현재 눌렀을 경우
bool CKeyMgr2::Key_Down(int _iKey)
{
	return m_bKeyDownState[_iKey];
}

// 이전에는 누른 적이 있고, 현재 누르지 않은 경우
bool CKeyMgr2::Key_Up(int _iKey)
{
	return m_bKeyUpState[_iKey];
}

void CKeyMgr2::Release()
{
}
