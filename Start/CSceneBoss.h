#pragma once
#include "CScene.h"
#include "CObjBgBossBuilding.h"
#include "CObjBgBossCloud.h"
#include "CObjUnstableKnockbackPlatformA.h"

class CSceneBoss: public CScene
{
public:
	CSceneBoss();
	virtual ~CSceneBoss();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;


private:
	CObjBgBossBuilding* m_pBgBuilding1;
	CObjBgBossBuilding* m_pBgBuilding2;
	CObjBgBossCloud* m_pBgCloud[7];

	CObjUnstableKnockbackPlatformA* m_pPlatform[7];
};

