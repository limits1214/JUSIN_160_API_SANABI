#pragma once
#include "CObj.h"
class CObjTrigger :
    public CObj
{
public:
	CObjTrigger();
	virtual ~CObjTrigger();

public:
	void Set_TriggerLoopCallback(function<void()> cb)
	{
		m_TriggerLoopCallbackFunc = cb;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	function<void()> m_TriggerLoopCallbackFunc;

	//function<void()> m_TriggerEnterCallbackFunc;
	//function<void()> m_TriggerExitCallbackFunc;
};

