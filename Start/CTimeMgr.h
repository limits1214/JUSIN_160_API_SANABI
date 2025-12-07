#pragma once
#include "Define.h"
class CTimeMgr
{
public:
	// 메인게임 업데이트시 한번만 해준다.
	void Update_Tick_Count();

	// 각 게임 업데이트시점에 필요하면 여기서 시간을 조회한다.
	DWORD Get_Tick_Count();

// 아래 Set_Timer, Set_Interval은 브라우저를 모방해서 만든건데
// 그냥 안쓸거같아서 접근제한자를 private으로 변경했다.
// 딜레이가 필요하다면 아래 스태틱 템플릿함수인 Delay를 사용하자
public:
	int Set_Timer(function<void()> func, DWORD time);
	void Clear_Timer(int iID);

	int Set_Interval(function<void()> func, DWORD time);
	void Clear_Interval(int iID);

private:
	void Update_Timer();
	void Update_Interval();

private:
	DWORD m_dwTime;
	unordered_map<int, TIMERINFO> m_TimerMap;
	unordered_map<int, TIMERINFO> m_IntervalMap;
	int m_iTimerCnt;
	int m_iIntervalCnt;

public:
	// 딜레이 주는 함수
	// TODO: 현재는 딜레이 초기화시 딜레이를 더해주는게 아니라
	//			바로 현재시간을 넣어주기때문에 시간오차가 존재하는데
	//			이부분은 정확한 타임이 필요하면 수정이 필요할듯
	template<typename F>
	static void Delay(DWORD* dwRefTime, DWORD dwDelay, F func)
	{
		DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
		if (*dwRefTime + dwDelay < dwNow)
		{
			func();

			//TODO: 뭐로
			//*dwRefTime += dwDelay;
			*dwRefTime = dwNow;
		}
	}

	template<typename F>
	static void DelayOne(DWORD* dwRefTime, DWORD dwDelay, F func)
	{
		DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
		if (*dwRefTime + dwDelay < dwNow)
		{
			func();
		}
	}
	
// SINGLETON
private:
	CTimeMgr();
	CTimeMgr& operator=(CTimeMgr&) = delete;
	CTimeMgr(const CTimeMgr&) = delete;
	~CTimeMgr();

public:
	static CTimeMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CTimeMgr;
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
	static CTimeMgr* m_pInstance;


};

