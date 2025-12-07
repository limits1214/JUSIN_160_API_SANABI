#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;
CTimeMgr::CTimeMgr()
	:m_iTimerCnt(0), m_iIntervalCnt(0), m_dwTime(GetTickCount())
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Update_Tick_Count()
{
	m_dwTime = GetTickCount();

	// 안쓸거 같아서 주석처리함
	Update_Timer();
	Update_Interval();
}

DWORD CTimeMgr::Get_Tick_Count()
{
	return m_dwTime;
}

int CTimeMgr::Set_Timer(function<void()> func, DWORD time)
{
	DWORD dwNowTime = Get_Tick_Count();
	int iCnt = ++m_iTimerCnt;
	m_TimerMap[iCnt] = {false, time, dwNowTime, func};
	return iCnt;
}

void CTimeMgr::Clear_Timer(int iID)
{
	m_TimerMap.erase(iID);
}

int CTimeMgr::Set_Interval(function<void()> func, DWORD time)
{
	DWORD dwNowTime = Get_Tick_Count();
	int iCnt = ++m_iIntervalCnt;
	m_IntervalMap[iCnt] = { false, time, dwNowTime, func };
	return iCnt;
}

void CTimeMgr::Clear_Interval(int iID)
{
	m_IntervalMap.erase(iID);
}

void CTimeMgr::Update_Timer()
{
	DWORD dwNowTime = Get_Tick_Count();
	for (auto iter = m_TimerMap.begin(); iter != m_TimerMap.end();)
	{
		DWORD dwTime = (*iter).second.dwTime;
		DWORD dwLastTime = (*iter).second.dwLastTime;
		if (dwLastTime + dwTime < dwNowTime)
		{
			(*iter).second.func();
			iter = m_TimerMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CTimeMgr::Update_Interval()
{
	DWORD dwNowTime = Get_Tick_Count();
	for (auto& interval : m_IntervalMap)
	{
		DWORD dwTime = interval.second.dwTime;
		DWORD dwLastTime = interval.second.dwLastTime;
		if (dwLastTime + dwTime < dwNowTime)
		{
			interval.second.func();
			interval.second.dwLastTime += dwTime;
		}
	}
}
