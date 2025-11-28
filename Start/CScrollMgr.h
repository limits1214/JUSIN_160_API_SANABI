#pragma once

#include "Define.h"


class CScrollMgr
{

public:
	float Get_ScrollX() { return m_fScrollX; }
	float Get_ScrollY() { return m_fScrollY; }

	void Set_ScrollX(float fX) { m_fScrollX += fX; }
	void Set_ScrollY(float fY) { m_fScrollY += fY; }

	void Scroll_Lock();

private:
	float		m_fScrollX;
	float		m_fScrollY;

// SINGLETON
private:
	CScrollMgr();
	CScrollMgr& operator=(CScrollMgr&) = delete;
	CScrollMgr(const CScrollMgr&) = delete;
	~CScrollMgr();

public:
	static CScrollMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CScrollMgr;
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
	static CScrollMgr* m_pInstance;
};

