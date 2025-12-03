#pragma once

#include "CObj.h"
#include "CMouseEvent.h"
#include "CCollisionEvent.h"

class CObjHookGuide: public CObj, public CMousePosEvent, public CCollisionEvent, public CMouseKeyEvent
{
public:
	CObjHookGuide();
	virtual ~CObjHookGuide();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Mouse_Pos(CObj* pMouse) override;

public:
	void On_Mouse_Key_Down(CObj* pMouse) override;
	void On_Mouse_Key_Up(CObj* pMouse) override;
	void On_Mouse_Key_Pressing(CObj* pMouse) override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

private:
	LINE m_tLine;
	float m_fMaxLength;
	float m_fAngle;
	CObj* m_pGrab;
};

