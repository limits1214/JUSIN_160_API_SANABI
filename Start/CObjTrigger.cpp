#include "pch.h"
#include "CObjTrigger.h"
#include "CObjMgr.h"

CObjTrigger::CObjTrigger()
	:m_TriggerLoopCallbackFunc(nullptr)
{
}

CObjTrigger::~CObjTrigger()
{
	Release();
}

void CObjTrigger::Initialize()
{
	Set_UseMainScroll(true);
}

int CObjTrigger::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_pTarget != nullptr)
	{
		RECT rc;
		if (IntersectRect(&rc, m_pTarget->Get_Rect(), &m_tRect))
		{
			if (m_TriggerLoopCallbackFunc != nullptr)
			{
				m_TriggerLoopCallbackFunc();
			}
		}
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjTrigger::Late_Update()
{
}

void CObjTrigger::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjTrigger::Release()
{
}
