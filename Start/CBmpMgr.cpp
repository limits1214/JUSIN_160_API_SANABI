#include "pch.h"
#include "CBmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{

}

CBmpMgr::~CBmpMgr()
{
	Release();
}

HDC CBmpMgr::Find_Image(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CMyBitmap* pBmp = new CMyBitmap;
		pBmp->Load_Bmp(pFilePath);

		//TCHAR szTemp[256]{};
		//lstrcpy(szTemp, pImgKey);

		m_mapBit.insert({ pImgKey, pBmp });
	}
}

map<const TCHAR*, CMyBitmap*>* CBmpMgr::Get_BmpMap()
{
	return &m_mapBit;
}

void CBmpMgr::Delete_Bmp(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));
	tagDeleteMap()(*iter);
	m_mapBit.erase(iter);
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), tagDeleteMap());
	m_mapBit.clear();
}