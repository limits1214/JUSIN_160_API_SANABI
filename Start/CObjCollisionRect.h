#pragma once
#include "CObjRect.h"
#include "CCollisionEvent.h"
class CObjCollisionRect: public CObjRect, public CCollisionEvent
{
public:
	CObjCollisionRect();
	virtual ~CObjCollisionRect();

public:
	int Get_Option() { return m_iOption; }
	void Set_Option(int iOption) { m_iOption = iOption; }

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;


public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iOption;
};

