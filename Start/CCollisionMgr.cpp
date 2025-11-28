#include "pch.h"
#include "CCollisionMgr.h"
#include "CObjLine.h"
#include "CCollisionEvent.h"
void CCollisionMgr::Collision_Line(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto*& Dst : _Dst)
	{
		for (auto*& Src : _Src)
		{
			CCollisionEvent* pDst = dynamic_cast<CCollisionEvent*>(Dst);
			CObjLine* pLine = dynamic_cast<CObjLine*>(Src);
			if (pLine != nullptr && pDst != nullptr)
			{
				LINE line{};
				const RECT* lineRect = pLine->Get_Rect();
				float fIncline = pLine->Get_LineIncline();
				if (fIncline < 0)
				{
					line.tLeft.fX = (float)lineRect->left;
					line.tLeft.fY = (float)lineRect->bottom;
					line.tRight.fX = (float)lineRect->right;
					line.tRight.fY = (float)lineRect->top;
				}
				else
				{
					line.tLeft.fX = (float)lineRect->left;
					line.tLeft.fY = (float)lineRect->top;
					line.tRight.fX = (float)lineRect->right;
					line.tRight.fY = (float)lineRect->bottom;
				}

				float targetX = Dst->Get_Info()->fX;
				if(
					targetX >= line.tLeft.fX
					&&
					targetX <= line.tRight.fX
				)
				{
					//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
					float fLineGi = ((line.tRight.fY - line.tLeft.fY) / (line.tRight.fX - line.tLeft.fX));
					float targetY = fLineGi * (targetX - line.tLeft.fX) + line.tLeft.fY;
					pDst->On_Collision(Src, COLL_LINE, &targetY);
				}
			}
		}
	}
}
