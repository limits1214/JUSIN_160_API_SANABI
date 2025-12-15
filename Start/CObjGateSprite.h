#pragma once
#include "CObj.h"
class CObjGateSprite :
    public CObj
{
public:
	CObjGateSprite();
	virtual ~CObjGateSprite();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void GateOpen();
	void GateClose();


private:
	void Motion_Change();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

private:
	bool m_bOpening;
	bool m_bClosing;
	bool m_bIdle;
};

