#pragma once
#include "CObj.h"

#include "CMouseEvent.h"

class CObjThings: public CObj, public CMouseKeyEvent
{
public:
	CObjThings();
	virtual ~CObjThings();

public:
	void Set_Thgins(THINGS_ID eThings) { m_eThings = eThings; }
	THINGS_ID Get_Thgins() { return m_eThings; }

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
	void ChangeReal();

private:
	THINGS_ID m_eThings;
	bool m_bMouseTrack;
};

