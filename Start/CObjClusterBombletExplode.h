#pragma once
#include "CObj.h"
class CObjClusterBombletExplode :
    public CObj
{
public:
	CObjClusterBombletExplode();
	virtual ~CObjClusterBombletExplode();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

