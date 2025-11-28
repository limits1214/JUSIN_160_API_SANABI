#pragma once

#include "pch.h"
#include "CObj.h"

class CMouseKeyEvent
{
public:
	CMouseKeyEvent() = default;
	virtual ~CMouseKeyEvent() = default;

public:
	virtual void On_Mouse_Key_Down(CObj* pMouse) PURE;
	virtual void On_Mouse_Key_Up(CObj* pMouse) PURE;
	virtual void On_Mouse_Key_Pressing(CObj* pMouse) PURE;
};

class CMousePosEvent
{
public:
	CMousePosEvent() = default;
	virtual ~CMousePosEvent() = default;

public:
	virtual void On_Mouse_Pos(CObj* pMouse) PURE;
};