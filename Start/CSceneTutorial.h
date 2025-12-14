#pragma once

#include "CScene.h"
#include "CObjBgTutoCloud.h"

class CSceneTutorial: public CScene
{
public:
	CSceneTutorial();
	virtual ~CSceneTutorial();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	CObjBgTutoCloud* m_pCloud1;
	CObjBgTutoCloud* m_pCloud2;
	bool m_bTriggerEnter;

	bool m_bTutoClear;
};

