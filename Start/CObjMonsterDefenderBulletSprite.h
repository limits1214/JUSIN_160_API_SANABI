#pragma once
#include "CObj.h"
class CObjMonsterDefenderBulletSprite :
    public CObj
{
public:
	CObjMonsterDefenderBulletSprite();
	virtual ~CObjMonsterDefenderBulletSprite();

public:

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

private:
	POINT           m_tPoint[3];
};

