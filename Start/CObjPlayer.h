#pragma once

#include "CObj.h"
#include "CCollisionEvent.h"

class CObjPlayer: public CObj, public CCollisionEvent
{
public:
	enum STATE{IDLE, RUNNING, JUMP, ST_END};

public:
	CObjPlayer();
	virtual ~CObjPlayer();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

private:
	void Key_Input();
	void Motion_Change();
	void	Offset();

private:
	STATE				m_ePreState;
	STATE				m_eCurState;
};

