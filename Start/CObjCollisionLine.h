#pragma once
#include "CObjLine.h"

class CObjCollisionLine: public CObjLine
{
public:
	CObjCollisionLine();
	virtual ~CObjCollisionLine();

public:
	int Get_Option() {return m_iOption;}
	void Set_Option(int iOption) { m_iOption = iOption; }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iOption;
	
};

