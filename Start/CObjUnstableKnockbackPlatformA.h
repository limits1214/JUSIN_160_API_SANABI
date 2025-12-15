#pragma once
#include "CObj.h"
#include "CObjCollisionRect.h"
#include "CCollisionEvent.h"
class CObjUnstableKnockbackPlatformA: public CObjCollisionRect
{
public:
	CObjUnstableKnockbackPlatformA();
	virtual ~CObjUnstableKnockbackPlatformA();

public:
	void Set_Combackpos(float X, float Y)
	{
		m_fComebackX = X;
		m_fComebackY = Y;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

private:
	void Motion_Change();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

	float m_fComebackX;
	float m_fComebackY;
	bool m_bComback;


	bool m_bDestroyed;

public:
	enum ANI_STATE
	{
		IDLE_START,
		IDLE_ING,
		IDLE_END,

		DAMAGED_START,
		DAMAGED_ING,
		DAMAGED_END,

		IDLE_WARING_START,
		IDLE_WARING_ING,
		IDLE_WARING_END,

		DAMAGED_WARNING_START,
		DAMAGED_WARNING_ING,
		DAMAGED_WARNING_END,

		IDLE_DOUBLEWARNING_START,
		IDLE_DOUBLEWARNING_ING,
		IDLE_DOUBLEWARNING_END,

		DESTROY_START,
		DESTROY_ING,
		DESTROY_END
	};

	ANI_STATE m_eAniState;
};

