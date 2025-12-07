#pragma once
#include "CObj.h"
class CObjBossBackHeli :
    public CObj
{
public:
	CObjBossBackHeli();
	virtual ~CObjBossBackHeli();

public:
	void Set_MoveTarget(float x, float y)
	{
		m_fMoveTargetX = x;
		m_fMoveTargetY = y;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	float m_fMoveTargetX;
	float m_fMoveTargetY;
};

