#pragma once
#include "CObj.h"
class CObjBossBodySlapAlert: public CObj
{
public:
	CObjBossBodySlapAlert();
	virtual ~CObjBossBodySlapAlert();

public:
	void Set_DelayTime(DWORD dwDelay)
	{
		m_dwDelay = dwDelay;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	DWORD m_dwDelayTime;
	DWORD m_dwDelay;

	bool m_bDelayEnd;
};

