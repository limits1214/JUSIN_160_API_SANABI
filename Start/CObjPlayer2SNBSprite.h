#pragma once
#include "CObj.h"
class CObjPlayer2SNBSprite :
    public CObj
{
public:
	CObjPlayer2SNBSprite();
	virtual ~CObjPlayer2SNBSprite();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;


private:
	void Motion_Change();

	void AniStateUpdate();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;
};

