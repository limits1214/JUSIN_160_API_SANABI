#pragma once
#include "CObj.h"
class CObjMovable: public CObj
{
public:
	CObjMovable();
	virtual ~CObjMovable();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	virtual void _Move(DIRECTION eDir, float fDistance);

protected:
	void ParabolaNoGravityEquation(float fVZero, float fAngle, float fDeltaSum, float* fDstX, float* fDstY);


protected:
	DWORD m_dwTime;
	DWORD m_dwDeltaSum;

	DWORD m_dwGravityDeltaSum;
	DWORD m_dwJumpDeltaSum;

	DWORD m_dwMoveLeftDeltaSum;
	DWORD m_dwMoveRightDeltaSum;



	bool m_bJump;

	float m_fJumpVZero;
	float m_fJumpAngle;
};

