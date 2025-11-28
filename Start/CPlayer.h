#pragma once
#include "CObj.h"
class CPlayer: public CObj
{
public:
	enum STATE {IDLE, WALK, ATTACK, HIT, DEAD, ST_END};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Key_Input();
	void	Motion_Change();

	STATE m_ePreState;
	STATE m_eCurState;
};

