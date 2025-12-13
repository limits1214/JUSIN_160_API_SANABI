#pragma once
#include "CObj.h"
class CObjExplosionSprite :
    public CObj
{
public:
	CObjExplosionSprite();
	virtual ~CObjExplosionSprite();

public:
	void Set_Option(int iOption)
	{
		m_iOption = iOption;
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

private:
	int m_iOption;
};

