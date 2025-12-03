#pragma once
#include "CScene.h"
#include "CUIObjText.h"
class CSceneLap2 :
    public CScene
{
public:
	CSceneLap2();
	virtual ~CSceneLap2();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	INFO info;
	RECT rect;
	DWORD dwTime;

	float deltaSum;

	CUIObjText* m_pText;
	CUIObjText* m_pText2;
	CUIObjText* m_pText3;
	float m_fG;

	float m_fAngle;

	float m_fCurrentTargetAngle;

	bool m_bStopDeltaSum;
};

