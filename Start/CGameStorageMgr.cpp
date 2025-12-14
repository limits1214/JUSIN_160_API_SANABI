#include "pch.h"
#include "CGameStorageMgr.h"
CGameStorageMgr* CGameStorageMgr::m_pInstance = nullptr;

CGameStorageMgr::CGameStorageMgr()
	:m_bChap1Clear(false), m_bChap2Clear(false), m_bChap3Clear(false)
{

}

CGameStorageMgr::~CGameStorageMgr()
{
	Release();
}

void CGameStorageMgr::Release()
{

}