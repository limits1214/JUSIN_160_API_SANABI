#pragma once

#include "CObj.h"

class CObjLine: public CObj
{
public:
	CObjLine();
	virtual ~CObjLine();

public:
	void Set_Line_Point(LINEPOINT ptLeft, LINEPOINT ptRight)
	{
		m_tLine = {ptLeft, ptRight};
	}
	LINE Get_Line()
	{
		return m_tLine;
	}

	float Get_LineIncline()
	{
		float fWidth = m_tLine.tRight.fX - m_tLine.tLeft.fX;
		float fHeight = m_tLine.tRight.fY - m_tLine.tLeft.fY;
		float fIncline = fHeight / fWidth;
		return fIncline;
	}

	
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	void Update_Line();

protected:
	LINE m_tLine;
};

