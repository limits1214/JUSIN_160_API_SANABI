#include "pch.h"
#include "CCollisionMgr.h"
#include "CObjLine.h"
#include "CCollisionEvent.h"
void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{

	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		CCollisionEvent* evDst = dynamic_cast<CCollisionEvent*>(Dst);
		if (evDst == nullptr) continue;
		for (auto& Src : _Src)
		{
			CCollisionEvent* evSrc = dynamic_cast<CCollisionEvent*>(Src);
			if (evSrc == nullptr) continue;
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				evDst->On_Collision(Src, COLL_RECT, &rc);
				evSrc->On_Collision(Dst, COLL_RECT, &rc);
			}
		}
	}

}

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
				float inputX = Dst->Get_Info()->fX;
				float inputY = Dst->Get_Info()->fY;
				float outpuyX = 0;
				float outputY = 0;
				if (Line_Equation(pLine, inputX, inputY, 0, 0, &outpuyX, &outputY))
				{
					COLL_ETC_LINE etc{ outpuyX, outputY };
					pDst->On_Collision(Src, COLL_LINE, &etc);
				}
			}
		}
	}
}


bool CCollisionMgr::Line_Equation(CObjLine* pLine, float inputX, float inputY, float intputXMarin, float inputYMargin, float* outputX, float* outputY)
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
	
	// check 기울기 세로 nan
	if (((int)(line.tRight.fX - line.tLeft.fX)) == 0)
	{
		if (line.tLeft.fY > line.tRight.fY)
		{
			swap(line.tLeft.fY, line.tRight.fY);
		}

		//  세로 길이 범위 체크
		if (
			inputY >= line.tLeft.fY - inputYMargin
			&&
			inputY <= line.tRight.fY + inputYMargin
			)
		{
			*outputX = line.tLeft.fX; // 세로는 같으니 레프트나 라이트 아무거나
			*outputY = NAN;
			return true;
		}
		else
		{
			return false;
		}
	}

	// check 가로
	if (
		inputX >= line.tLeft.fX - intputXMarin
		&&
		inputX <= line.tRight.fX + intputXMarin
		)
	{
		//if (inputX < line.tLeft.fX)
		//{
		//	inputX = line.tLeft.fX;
		//}
		//else if (inputX > line.tRight.fX)
		//{
		//	inputX = line.tRight.fX;
		//}

		//*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
		float fLineGi = ((line.tRight.fY - line.tLeft.fY) / (line.tRight.fX - line.tLeft.fX));
		float targetY = fLineGi * (inputX - line.tLeft.fX) + line.tLeft.fY;

		

		*outputX = inputX;
		*outputY = targetY;
		return true;
	}
	else
	{
		return false;
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{

	float	fWidth(0.f), fHeight(0.f);

	for (auto& pDst : _Dst)
	{
		CCollisionEvent* evDst = dynamic_cast<CCollisionEvent*>(pDst);
		if (evDst == nullptr)
		{
			continue;
		}
		for (auto& Src : _Src)
		{
			if (Check_Rect(pDst, Src, &fWidth, &fHeight))
			{
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (pDst->Get_Info()->fY < Src->Get_Info()->fY)
					{

						//Dst->Set_PosY(-fHeight);
						COLL_ETC_RECT_EX info{ DIR_UP, fHeight };
						evDst->On_Collision(Src, COLL_RECT_EX, &info);
					}
					// 하 충돌
					else
					{
						//Dst->Set_PosY(fHeight);
						COLL_ETC_RECT_EX info{ DIR_DOWN, fHeight };
						evDst->On_Collision(Src, COLL_RECT_EX, &info);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (pDst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						//Dst->Set_PosX(-fWidth);
						COLL_ETC_RECT_EX info{ DIR_LEFT, fWidth };
						evDst->On_Collision(Src, COLL_RECT_EX, &info);
					}
					// 우 충돌
					else
					{
						//Dst->Set_PosX(fWidth);
						COLL_ETC_RECT_EX info{ DIR_RIGHT, fWidth };
						evDst->On_Collision(Src, COLL_RECT_EX, &info);
					}
				}
			}
		}
	}


	//float	fWidth(0.f), fHeight(0.f);

	//for (auto& Dst : _Dst)
	//{
	//	for (auto& Src : _Src)
	//	{
	//		if (Check_Rect(Dst, Src, &fWidth, &fHeight))
	//		{
	//			// 상 하 충돌
	//			if (fWidth > fHeight)
	//			{
	//				// 상 충돌
	//				if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
	//				{
	//					Dst->Set_PosY(-fHeight);
	//				}
	//				// 하 충돌
	//				else
	//				{
	//					Dst->Set_PosY(fHeight);
	//				}
	//			}

	//			// 좌 우 충돌
	//			else
	//			{
	//				// 좌 충돌
	//				if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
	//				{
	//					Dst->Set_PosX(-fWidth);
	//				}
	//				// 우 충돌
	//				else
	//				{
	//					Dst->Set_PosX(fWidth);
	//				}
	//			}
	//		}
	//	}
	//}
}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fRadiusX = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->fCY + pSrc->Get_Info()->fCY) * 0.5f;

	if (fRadiusX >= fWidth && fRadiusY >= fHeight)
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
