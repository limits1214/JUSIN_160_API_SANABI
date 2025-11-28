#pragma once
#include "CObj.h"
#include "CMouseEvent.h"
class CUIObjRectButton: public CObj, public CMouseKeyEvent, public CMousePosEvent
{
public:
	CUIObjRectButton();
	virtual ~CUIObjRectButton();
public:
	void Set_OnKeyDown(function<void()> keydownFunc)
	{
		m_OnKeydownFunc = keydownFunc;
	}

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

private:

	function<void()> m_OnKeydownFunc;
	function<void()> m_OnMouseIn;
	function<void()> m_OnMouseOut;
	function<void()> m_OnMouseClick;

	COLORREF m_colDefault;
	COLORREF m_colHover;

	COLORREF m_colCur;
	
};

