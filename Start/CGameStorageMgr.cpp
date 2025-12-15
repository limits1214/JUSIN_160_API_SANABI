#include "pch.h"
#include "CGameStorageMgr.h"
CGameStorageMgr* CGameStorageMgr::m_pInstance = nullptr;

CGameStorageMgr::CGameStorageMgr()
	:m_bChap1Clear(true), m_bChap2Clear(true), m_bChap3Clear(false), m_bBossDeadEnd(false)
{

}

CGameStorageMgr::~CGameStorageMgr()
{
	Release();
}

void CGameStorageMgr::Release()
{

}