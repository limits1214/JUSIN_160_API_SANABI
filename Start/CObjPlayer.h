#pragma once

#include "CObj.h"
#include "CCollisionEvent.h"
#include "CMouseEvent.h"

#include "CObjDbgText.h"

class CObjPlayer: public CObj, public CCollisionEvent, public CMousePosEvent, public CMouseKeyEvent
{
public:
	CObjPlayer();
	virtual ~CObjPlayer();

public:
	void Set_PlayerState(FRAME_STATE_ID eState)
	{
		m_eCurState = eState;
	}
	FRAME_STATE_ID Get_PlayerState()
	{
		return m_eCurState;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

public:
	void On_Mouse_Pos(CObj* pMouse) override;

public:
	void On_Mouse_Key_Down(CObj* pMouse) override;
	void On_Mouse_Key_Up(CObj* pMouse) override;
	void On_Mouse_Key_Pressing(CObj* pMouse) override;

public:
	//TCHAR* Dbg_Text() override;

public:
	void MonsterExcStart(CObj* pMonster);

public:
	void Grab(CObj* pObj);

private:
	void Key_Input();
	void Motion_Change();
	void Offset();
	void Move(DIRECTION eDir, float fDistance);

	void JumpStart(float fVZero, float fAngle);
	void JumpEnd();

	void GrabLoad();

	


private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;



private:
	void DeltaInit();
	void DeltaUpdate();

	DWORD m_dwTime;
	float m_fGravityDeltaSum;
	float m_fJumpDeltaSum;
	float m_fMoveLeftDeltaSum;
	float m_fMoveRightDeltaSum;

	bool m_bJumpJustPressed;

	bool m_bRWallClimb;
	bool m_bLWallClimb;
	bool m_bGravity;
	bool m_bJump;
	bool m_bGround;
	bool m_bGrab;
	bool m_bGrabLoad;

	bool m_bWallTop;
	bool m_bWallDown;

	float m_fJumpVZero;
	float m_fJumpAngle;
	

	float m_bSwigDash;

	bool m_bDamaged;
	DIRECTION m_eDamagedDir;
	int m_iDamagedInvicibleTime;

	bool m_bDamagedDash;
	DIRECTION m_eDamagedDashDir;
	int m_iDamagedDashableTime;


	bool m_bMonsterExcStart;
	bool m_bMonsterExc;
	


private:
	LINE m_tHookLine;
	float m_fHookMaxLength;
	float m_fHookMinLength;
	float m_fHookAngle;
	CObj* m_pGrab;
	unsigned long long seq_pGrab;

	float m_fGrabLoadX;
	float m_fGrabLoadY;
	RECT m_tGrabRect;

	bool m_bGrabCeilingMove;


	float m_fPendLength;
	float m_fPendRad;
	float m_fPendCurr;
	float m_fPendDeltaSum;
	float m_fPendStartX;
	float m_fPendStartY;

protected:
	void ParabolaNoGravityEquation(float fVZero, float fAngle, float fDeltaSum, float* fDstX, float* fDstY);
};

