#pragma once
#include "CObj.h"
class CObjBgBossCloud : public CObj
{
public:
	CObjBgBossCloud();
	virtual ~CObjBgBossCloud();

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

private:
	int m_iOption;
};

