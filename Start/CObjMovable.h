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

	float m_fGravityDeltaSum;
	float m_fJumpDeltaSum;

	float m_fMoveLeftDeltaSum;
	float m_fMoveRightDeltaSum;


	bool m_bGravity;
	bool m_bJump;

	float m_fJumpVZero;
	float m_fJumpAngle;

	bool m_bGround;


	bool m_bGrab;
	float m_fPendLength;
	float m_fPendRad;
	float m_fPendDeltaSum;
	float m_fPendStartX;
	float m_fPendStartY;

};

