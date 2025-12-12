#pragma once
#include "CObjMonster.h"
#include "CCollisionEvent.h"
class CObjMonsterDummyRobot :
	public CObjMonster, public CCollisionEvent
{
public:
	CObjMonsterDummyRobot();
	virtual ~CObjMonsterDummyRobot();

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

private:
	void Motion_Change();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

private:
	bool m_bExecuted;
	float m_fExcutedRad;

public:
	enum ANI_STATE
	{
		AST_LEFT_IDLE_START,
		AST_LEFT_IDLE_ING,
		AST_LEFT_IDLE_END,

		AST_RIGHT_IDLE_START,
		AST_RIGHT_IDLE_ING,
		AST_RIGHT_IDLE_END,

		AST_LEFT_RUNNING_START,
		AST_LEFT_RUNNING_ING,
		AST_LEFT_RUNNING_END,

		AST_RIGHT_RUNNING_START,
		AST_RIGHT_RUNNING_ING,
		AST_RIGHT_RUNNING_END,

		AST_RESPAWN_START,
		AST_RESPAWN_ING,
		AST_RESPAWN_END,

		AST_EXCSTART_START,
		AST_EXCSTART_ING,
		AST_EXCSTART_END,

		AST_EXCHOLDBACK_START,
		AST_EXCHOLDBACK_ING,
		AST_EXCHOLDBACK_END,

		AST_DEAD_START,
		AST_DEAD_ING,
		AST_DEAD_END,
	};
	ANI_STATE m_eAniState;
};

