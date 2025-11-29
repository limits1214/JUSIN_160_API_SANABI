#pragma once
#include "CObj.h"
class CObjSprite: public CObj
{
public:
	CObjSprite();
	virtual ~CObjSprite();

public:


	void Set_MoveFrame(bool bMoveFrame)
	{
		m_bMoveFrame = bMoveFrame;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	bool m_bMoveFrame;
};

