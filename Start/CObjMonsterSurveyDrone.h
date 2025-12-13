#pragma once
#include "CObjMonster.h"
#include "CCollisionEvent.h"
class CObjMonsterSurveyDrone :
    public CObjMonster, public CCollisionEvent
{
public:
	CObjMonsterSurveyDrone();
	virtual ~CObjMonsterSurveyDrone();

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

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

private:
	bool m_bExecuted;
	float m_fExcutedRad;
	bool m_bGrabbed;

private:
	DWORD m_dwTime;
	float m_fLemnisDeltaSum;

	bool m_bOriginSet;
	float m_fOriginX;
	float m_fOriginY;

	bool m_bTracing;
	bool m_bHovering;
	DWORD m_dwPhotoTime;
	


public:
	enum ANI_STATE
	{
		AST_RIGHT_IDLE_START,
		AST_RIGHT_IDLE_ING,
		AST_RIGHT_IDLE_END,

		AST_RIGHT_RESPAWN_START,
		AST_RIGHT_RESPAWN_ING,
		AST_RIGHT_RESPAWN_END,


		AST_RIGHT_PHOTO_START,
		AST_RIGHT_PHOTO_ING,
		AST_RIGHT_PHOTO_END,

		AST_RIGHT_DESTROY_START,
		AST_RIGHT_DESTROY_ING,
		AST_RIGHT_DESTROY_END,

		AST_RIGHT_EXCHOLDSTART_START,
		AST_RIGHT_EXCHOLDSTART_ING,
		AST_RIGHT_EXCHOLDSTART_END,

		AST_RIGHT_EXCHOLDBACK_START,
		AST_RIGHT_EXCHOLDBACK_ING,
		AST_RIGHT_EXCHOLDBACK_END,

		AST_LEFT_IDLE_START,
		AST_LEFT_IDLE_ING,
		AST_LEFT_IDLE_END,


		AST_LEFT_RESPAWN_START,
		AST_LEFT_RESPAWN_ING,
		AST_LEFT_RESPAWN_END,


		AST_LEFT_PHOTO_START,
		AST_LEFT_PHOTO_ING,
		AST_LEFT_PHOTO_END,

		AST_LEFT_DESTROY_START,
		AST_LEFT_DESTROY_ING,
		AST_LEFT_DESTROY_END,

		AST_LEFT_EXCHOLDSTART_START,
		AST_LEFT_EXCHOLDSTART_ING,
		AST_LEFT_EXCHOLDSTART_END,

		AST_LEFT_EXCHOLDBACK_START,
		AST_LEFT_EXCHOLDBACK_ING,
		AST_LEFT_EXCHOLDBACK_END,
	};
	ANI_STATE m_eAniState;
};

