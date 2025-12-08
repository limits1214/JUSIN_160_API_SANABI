#pragma once
#include "CObj.h"
#include "CCollisionEvent.h"
#include "CMouseEvent.h"
#include "CObjPlayer2Grab.h"

class CObjPlayer2 :
    public CObj, public CCollisionEvent, public CMousePosEvent, public CMouseKeyEvent
{
public:
	CObjPlayer2();
	virtual ~CObjPlayer2();

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
	void Grab(CObjPlayer2Grab* pObj);

private:
	void DeltaUpdate();
	void Key_Input();
	void Apply_Gravity();
	void Apply_Jump();
	void Apply_Pend();
	void Move(float fAngle, float fLength);
	void Offset();

	void GrabLoad();
private:
	DWORD m_dwTime;

	bool m_bGravity;
	float m_fGravityDeltaSum;
	
	bool m_bJump;
	float m_fJumpDeltaSum;
	float m_fJumpVelocity;
	float m_fJumpAngle;

	INFO m_tBeforeInfo;

	bool m_bFall;
	bool m_bGround;

	bool m_bLeftWallClimb;
	bool m_bRightWallClimb;
	bool m_bWallTop;
	bool m_bWallDown;

	bool m_bGrabShoot;
	bool m_bGrabbing;
	bool m_bGrabRelease;
	bool m_bGrabLoad;

	bool m_bExc;
	bool m_bCeilStick;
	DIRECTION m_eLastLRDir;
	

	LINE m_tHookLine;
	float m_fHookMaxLength;
	float m_fHookMinLength;
	float m_fHookAngle;
	CObjPlayer2Grab* m_pGrab;


	float m_fPendLength;
	float m_fPendRad;
	float m_fPendCurr;
	float m_fPendDeltaSum;
	float m_fPendStartX;
	float m_fPendStartY;

public:
	enum STATE
	{
		IDLE,
		MOVE,
		JUMP,
		WALL,
		CEILING_STICK,
		
		GRAP
	};
	STATE m_eState;


	enum ANI_STATE_SNB
	{
		AST_RIGHT_SNB_IDLE_START,
		AST_RIGHT_SNB_IDLE_ING,
		AST_RIGHT_SNB_IDLE_END,
		AST_LEFT_SNB_IDLE_START,
		AST_LEFT_SNB_IDLE_ING,
		AST_LEFT_SNB_IDLE_END,

		AST_RIGHT_SNB_RUNSTART_START,
		AST_RIGHT_SNB_RUNSTART_ING,
		AST_RIGHT_SNB_RUNSTART_END,
		AST_LEFT_SNB_RUNSTART_START,
		AST_LEFT_SNB_RUNSTART_ING,
		AST_LEFT_SNB_RUNSTART_END,

		AST_RIGHT_SNB_RUNNING_START,
		AST_RIGHT_SNB_RUNNING_ING,
		AST_RIGHT_SNB_RUNNING_END,
		AST_LEFT_SNB_RUNNING_START,
		AST_LEFT_SNB_RUNNING_ING,
		AST_LEFT_SNB_RUNNING_END,

		AST_RIGHT_SNB_RUNSTOP_START,
		AST_RIGHT_SNB_RUNSTOP_ING,
		AST_RIGHT_SNB_RUNSTOP_END,
		AST_LEFT_SNB_RUNSTOP_START,
		AST_LEFT_SNB_RUNSTOP_ING,
		AST_LEFT_SNB_RUNSTOP_END,

		AST_RIGHT_SNB_JUMPING_START,
		AST_RIGHT_SNB_JUMPING_ING,
		AST_RIGHT_SNB_JUMPING_END,
		AST_LEFT_SNB_JUMPING_START,
		AST_LEFT_SNB_JUMPING_ING,
		AST_LEFT_SNB_JUMPING_END,

		AST_RIGHT_SNB_FALLSTART_START,
		AST_RIGHT_SNB_FALLSTART_ING,
		AST_RIGHT_SNB_FALLSTART_END,
		AST_LEFT_SNB_FALLSTART_START,
		AST_LEFT_SNB_FALLSTART_ING,
		AST_LEFT_SNB_FALLSTART_END,

		AST_RIGHT_SNB_FALLING_START,
		AST_RIGHT_SNB_FALLING_ING,
		AST_RIGHT_SNB_FALLING_END,
		AST_LEFT_SNB_FALLING_START,
		AST_LEFT_SNB_FALLING_ING,
		AST_LEFT_SNB_FALLING_END,

		AST_RIGHT_SNB_LANDING_START,
		AST_RIGHT_SNB_LANDING_ING,
		AST_RIGHT_SNB_LANDING_END,
		AST_LEFT_SNB_LANDING_START,
		AST_LEFT_SNB_LANDING_ING,
		AST_LEFT_SNB_LANDING_END,

		AST_RIGHT_SNB_LAND2RUN_START,
		AST_RIGHT_SNB_LAND2RUN_ING,
		AST_RIGHT_SNB_LAND2RUN_END,
		AST_LEFT_SNB_LAND2RUN_START,
		AST_LEFT_SNB_LAND2RUN_ING,
		AST_LEFT_SNB_LAND2RUN_END,

		AST_RIGHT_SNB_WALL_SLIDE_START_START,
		AST_RIGHT_SNB_WALL_SLIDE_START_ING,
		AST_RIGHT_SNB_WALL_SLIDE_START_END,
		AST_LEFT_SNB_WALL_SLIDE_START_START,
		AST_LEFT_SNB_WALL_SLIDE_START_ING,
		AST_LEFT_SNB_WALL_SLIDE_START_END,


		AST_RIGHT_SNB_WALL_SLIDING_START,
		AST_RIGHT_SNB_WALL_SLIDING_ING,
		AST_RIGHT_SNB_WALL_SLIDING_END,
		AST_LEFT_SNB_WALL_SLIDING_START,
		AST_LEFT_SNB_WALL_SLIDING_ING,
		AST_LEFT_SNB_WALL_SLIDING_END,

		AST_RIGHT_SNB_WALL_CLIMBUP_START,
		AST_RIGHT_SNB_WALL_CLIMBUP_ING,
		AST_RIGHT_SNB_WALL_CLIMBUP_END,
		AST_LEFT_SNB_WALL_CLIMBUP_START,
		AST_LEFT_SNB_WALL_CLIMBUP_ING,
		AST_LEFT_SNB_WALL_CLIMBUP_END,

		AST_RIGHT_SNB_WALL_CLIMBDOWN_START,
		AST_RIGHT_SNB_WALL_CLIMBDOWN_ING,
		AST_RIGHT_SNB_WALL_CLIMBDOWN_END,
		AST_LEFT_SNB_WALL_CLIMBDOWN_START,
		AST_LEFT_SNB_WALL_CLIMBDOWN_ING,
		AST_LEFT_SNB_WALL_CLIMBDOWN_END,
	};
	ANI_STATE_SNB m_eAniStateSNB;

	enum ANI_STATE_SNBARM
	{
		AST_RIGHT_SNBARM_IDLE
	};
	ANI_STATE_SNBARM m_eAniStateSNBARM;
};

