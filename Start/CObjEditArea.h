#pragma once

#include "CObj.h"
#include "CMouseEvent.h"

class CObjEditArea : public CObj, public CMousePosEvent, public CMouseKeyEvent
{
public:
	CObjEditArea();
	virtual ~CObjEditArea();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Mouse_Key_Down(CObj* pMouse) override;
	void On_Mouse_Key_Up(CObj* pMouse) override;
	void On_Mouse_Key_Pressing(CObj* pMouse) override;

public:
	void On_Mouse_Pos(CObj* pMouse) override;
};

