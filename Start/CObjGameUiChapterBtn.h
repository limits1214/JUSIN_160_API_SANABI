#pragma once
#include "CObj.h"
#include "CMouseEvent.h"
class CObjGameUiChapterBtn: public CObj, public CMouseKeyEvent, public CMousePosEvent
{
public:
	CObjGameUiChapterBtn();
	virtual ~CObjGameUiChapterBtn();
public:
	void Set_Option(int iOption)
	{
		m_iOption = iOption;
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
	int m_iOption;

	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;
};

