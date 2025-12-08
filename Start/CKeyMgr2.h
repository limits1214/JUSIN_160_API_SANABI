#include "Define.h"

class CKeyMgr2
{
public:
	void Update();
	bool Key_Pressing(int _iKey);
	bool Key_Down(int _iKey);
	bool Key_Up(int _iKey);
	void Release();

private:
	bool m_bKeyPressingState[VK_MAX];
	bool m_bKeyUpState[VK_MAX];
	bool m_bKeyDownState[VK_MAX];

	// SINGLETON
private:
	CKeyMgr2();
	CKeyMgr2& operator=(CKeyMgr2&) = delete;
	CKeyMgr2(const CKeyMgr2&) = delete;
	~CKeyMgr2();

public:
	static CKeyMgr2* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CKeyMgr2;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyMgr2* m_pInstance;
};

