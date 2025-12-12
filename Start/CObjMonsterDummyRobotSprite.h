#pragma once
#include "CObj.h"
class CObjMonsterDummyRobotSprite :
    public CObj
{
public:
	CObjMonsterDummyRobotSprite();
	virtual ~CObjMonsterDummyRobotSprite();


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

