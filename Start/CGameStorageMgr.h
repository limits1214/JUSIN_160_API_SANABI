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
	void Set_Chap3Clear(bool bClear)
	{
		m_bChap3Clear = bClear;
	}
	void Set_BossDeadEnd(bool bBossDead)
	{
		m_bBossDeadEnd = bBossDead;
	}
	bool Get_BossDeadEnd()
	{
		return m_bBossDeadEnd;
	}

public:
	void Release();
private:
	bool m_bChap1Clear;
	bool m_bChap2Clear;
	bool m_bChap3Clear;

	bool m_bBossDeadEnd;


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

