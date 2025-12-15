#pragma once
#include "CObj.h"
#include "CMouseEvent.h"
#include "CCollisionEvent.h"
#include "CObjMonster.h"
class CObjMonsterFloatingBomb :
    public CObjMonster,public CCollisionEvent
{
public:
	CObjMonsterFloatingBomb();
	virtual ~CObjMonsterFloatingBomb();

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
	void Explode();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;


private:
	int m_iAngle;
	bool m_bExploded;
};

