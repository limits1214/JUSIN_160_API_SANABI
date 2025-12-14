#pragma once
class CGameStorageMgr
{
public:
	bool IsChap1Clear()
	{
		return m_bChap1Clear;
	}
	bool IsChap2Clear()
	{
		return m_bChap2Clear;
	}
	bool IsChap3Clear()
	{
		return m_bChap3Clear;
	}
	void Set_Chap1Clear(bool bClear)
	{
		m_bChap1Clear = bClear;
	}
	void Set_Chap2Clear(bool bClear)
	{
		m_bChap2Clear = bClear;
	}

public:
	void Release();
private:
	bool m_bChap1Clear;
	bool m_bChap2Clear;
	bool m_bChap3Clear;


	// SINGLETON
private:
	CGameStorageMgr();
	CGameStorageMgr& operator=(CGameStorageMgr&) = delete;
	CGameStorageMgr(const CGameStorageMgr&) = delete;
	~CGameStorageMgr();

public:
	static CGameStorageMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CGameStorageMgr;
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
	static CGameStorageMgr* m_pInstance;
};

