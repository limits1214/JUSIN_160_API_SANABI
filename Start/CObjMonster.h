#pragma once
#include "pch.h"
#include "CObj.h"

class CObjMonster : public CObj
{
public:
	CObjMonster() = default;
	virtual ~CObjMonster() = default;
public:
	virtual void Excuted(CObj* pPlayer, float fRad) PURE;
	virtual void Grabbed(CObj* pPlayer) PURE;

protected:
	bool m_bAirMonster;
};