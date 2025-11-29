#pragma once
#include "CObj.h"
class CObjTile: public CObj
{
public:
	CObjTile();
	virtual ~CObjTile();

public:
	void Set_FrameKey(const TCHAR* pFrameKey)
	{
		lstrcpy(m_szFrameKey, pFrameKey);
	}
	void Set_Frame(FRAME tFrame)
	{
		m_tFrame = tFrame;
	}
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	TCHAR m_szFrameKey[256];
};

