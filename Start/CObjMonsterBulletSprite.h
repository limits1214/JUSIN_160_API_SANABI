#pragma once
#include "CObj.h"
class CObjMonsterBulletSprite :
    public CObj
{
public:
	CObjMonsterBulletSprite();
	virtual ~CObjMonsterBulletSprite();

public:
	void Set_Option(int iOption)
	{
		m_iOption = iOption;
	}
	//void Set_Angle(float fAngle)
	//{
	//	m_fAngle = fAngle;
	//}

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
	int m_iOption;

	//float m_fAngle;
};

