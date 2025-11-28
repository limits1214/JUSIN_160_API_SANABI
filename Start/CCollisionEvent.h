#pragma once

#include "pch.h"
#include "CObj.h"

class CCollisionEvent
{
public:
	CCollisionEvent() = default;
	virtual ~CCollisionEvent() = default;

public:
	virtual void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) PURE;
};
