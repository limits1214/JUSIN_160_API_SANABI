#pragma once
#include "CMyBitmap.h"
class CBmpMgr
{
public:
	HDC Find_Image(const TCHAR* pImgKey);

public:
	void Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	map<const TCHAR*, CMyBitmap*>* Get_BmpMap();

	// Bmp Á¦°Å
	void Delete_Bmp(const TCHAR* pImgKey);
	void Release();

private:
	map<const TCHAR*, CMyBitmap*>		m_mapBit;
	
// SINGLETON
private:
	CBmpMgr();
	CBmpMgr& operator=(CBmpMgr&) = delete;
	CBmpMgr(const CBmpMgr&) = delete;
	~CBmpMgr();

public:
	static CBmpMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CBmpMgr;
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
	static CBmpMgr* m_pInstance;
};

