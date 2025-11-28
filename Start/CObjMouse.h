#pragma once

#include "CObj.h"
#include "CObjDbgText.h"

class CObjMouse: public CObj, public CObjDbgText
{
public:
	CObjMouse();
	virtual ~CObjMouse();

public:
	POINT Get_Pt_Curr()
	{
		return m_ptCurr;
	}
	POINT Get_Pt_Prev()
	{
		return m_ptPrev;
	}

	void Mouse_PreventEvent()
	{
		m_bPreventEvent = true;
	}
	void Mouse_TargetBringToTop()
	{
		m_bTargetBringToTop = true;
	}


public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	TCHAR* Dbg_Text() override;

private:

	template<typename T, typename F>
	void PropagateMouseEvent(F func);

private:
	POINT m_ptCurr;
	POINT m_ptPrev;

	//bool m_bCatch;
	bool m_bTargetBringToTop;
	bool m_bPreventEvent;

	CObj* m_pBringToTopObj;
};

