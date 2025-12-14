#pragma once
#include "CObjMonster.h"
#include "CCollisionEvent.h"
class CObjMonsterDefender :
    public CObjMonster, public CCollisionEvent
{
public:
	CObjMonsterDefender();
	virtual ~CObjMonsterDefender();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

public:
	void Excuted(CObj* pPlayer, float fRad) override;
	void Grabbed(CObj* pPlayer) override;

private:
	void DeltaUpdate();
	void Apply_Gravity();
	void Move(float fAngle, float fLength);

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

private:
	float m_fExcutedRad;

private:
	DWORD m_dwTime;

	bool m_bGravity;
	float m_fGravityDeltaSum;

	DWORD m_dwShootInterval;
	DWORD m_dwFireRateInterval;

	bool m_bFire;
	int m_iFireCnt;

	bool m_bPlayerFound;
	DIRECTION m_eMoveDir;

public:
	enum ANI_STATE
	{
		AST_RIGHT_IDLE_START,
		AST_RIGHT_IDLE_ING,
		AST_RIGHT_IDLE_END,

		AST_RIGHT_SET_START,
		AST_RIGHT_SET_ING,
		AST_RIGHT_SET_END,

		AST_RIGHT_DEAD_START,
		AST_RIGHT_DEAD_ING,
		AST_RIGHT_DEAD_END,

		AST_RIGHT_EXCHOLDBACK_START,
		AST_RIGHT_EXCHOLDBACK_ING,
		AST_RIGHT_EXCHOLDBACK_END,

		AST_RIGHT_STUNNED_START,
		AST_RIGHT_STUNNED_ING,
		AST_RIGHT_STUNNED_END,

		AST_RIGHT_TURNSTART_START,
		AST_RIGHT_TURNSTART_ING,
		AST_RIGHT_TURNSTART_END,

		AST_RIGHT_TURNEND_START,
		AST_RIGHT_TURNEND_ING,
		AST_RIGHT_TURNEND_END,

		AST_LEFT_IDLE_START,
		AST_LEFT_IDLE_ING,
		AST_LEFT_IDLE_END,

		AST_LEFT_SET_START,
		AST_LEFT_SET_ING,
		AST_LEFT_SET_END,

		AST_LEFT_DEAD_START,
		AST_LEFT_DEAD_ING,
		AST_LEFT_DEAD_END,

		AST_LEFT_EXCHOLDBACK_START,
		AST_LEFT_EXCHOLDBACK_ING,
		AST_LEFT_EXCHOLDBACK_END,

		AST_LEFT_STUNNED_START,
		AST_LEFT_STUNNED_ING,
		AST_LEFT_STUNNED_END,

		AST_LEFT_TURNSTART_START,
		AST_LEFT_TURNSTART_ING,
		AST_LEFT_TURNSTART_END,

		AST_LEFT_TURNEND_START,
		AST_LEFT_TURNEND_ING,
		AST_LEFT_TURNEND_END,
	};
	ANI_STATE m_eAniState;
};

