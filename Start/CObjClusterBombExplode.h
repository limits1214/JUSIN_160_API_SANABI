#pragma once
#include "CObj.h"
class CObjClusterBombExplode :
    public CObj
{
public:
	CObjClusterBombExplode();
	virtual ~CObjClusterBombExplode();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

