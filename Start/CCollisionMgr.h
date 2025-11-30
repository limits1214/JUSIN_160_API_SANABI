#pragma once

#include "CObj.h"
#include "CObjLine.h"
#include "Define.h"

typedef struct tagLineCollEtc
{
	float fX, fY;
} COLL_ETC_LINE;

typedef struct tagCollRectEx
{
	DIRECTION eDir;
	float fDistance;
} COLL_ETC_RECT_EX;

class CCollisionMgr
{
public:
	static void Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	static void Collision_Line(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Line_Equation(CObjLine* line, float inputX, float inputY, float intputXMarin, float inputYMargin, float* outputX, float* outputY);

	static void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
};

