#pragma once

#include "CObj.h"
#include "CObjLine.h"
class CCollisionMgr
{
public:
	static void Collision_Line(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Line_Equation(CObjLine* line, float inputX, float intputXMarin, float* outputY);
};

