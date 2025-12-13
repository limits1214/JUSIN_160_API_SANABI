#pragma once
#include "CObjMonster.h"
#include "CCollisionEvent.h"
class CObjMonsterDummyFloater :
    public CObjMonster, public CCollisionEvent
{
public:
	CObjMonsterDummyFloater();
	virtual ~CObjMonsterDummyFloater();

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
		AST_IDLE_START,
		AST_IDLE_ING,
		AST_IDLE_END,

		AST_RESPAWN_START,
		AST_RESPAWN_ING,
		AST_RESPAWN_END,

		AST_EXCSTART_START,
		AST_EXCSTART_ING,
		AST_EXCSTART_END,

		AST_EXCHOLDBACK_START,
		AST_EXCHOLDBACK_ING,
		AST_EXCHOLDBACK_END,
	};
	ANI_STATE m_eAniState;
};

