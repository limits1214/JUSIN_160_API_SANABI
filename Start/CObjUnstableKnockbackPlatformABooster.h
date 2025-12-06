#pragma once
#include "CObj.h"
class CObjUnstableKnockbackPlatformABooster :
    public CObj
{
public:
	CObjUnstableKnockbackPlatformABooster();
	virtual ~CObjUnstableKnockbackPlatformABooster();

public:
	void Set_PlayerState(FRAME_STATE_ID eState)
	{
		m_eCurState = eState;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Motion_Change();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;
};

