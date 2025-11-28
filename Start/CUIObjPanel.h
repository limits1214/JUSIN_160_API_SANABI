#pragma once
#include "CObj.h"
#include "CMouseEvent.h"
class CUIObjPanel: public CObj, public CMouseKeyEvent
{
public:
	CUIObjPanel();
	virtual ~CUIObjPanel();

public:
	void Set_Header_Text(const TCHAR* pText);

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

protected:
	int m_iHeaderHeight;

	RECT m_tHeaderRect;
	RECT m_tCloseRect;
	RECT m_tScrollRect;
	//RECT m_tContentRect;
	CObj* m_pUIContentBox;

	bool m_bMouseTrack;
	bool m_bMouseScrollTrack;


	int m_iYScrollWidth;
	int m_iYScrollHeight;
	int m_iYScrollLength;
	float m_fYScrollPercent;
};

