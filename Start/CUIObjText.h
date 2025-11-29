#pragma once
#include "CObj.h"
#include "CObjDbgText.h"
class CUIObjText: public CObj, public CObjDbgText
{
public:
	CUIObjText();
	virtual ~CUIObjText();

public:
	void Set_Text(const TCHAR* pText)
	{
		if (m_pText != nullptr)
		{
			Safe_Delete(m_pText);
		}
		auto len = lstrlen(pText);
		m_pText = new TCHAR[len+1];
		lstrcpy(m_pText, pText);
	}

	void Set_Aligh(bool bAlignLeft, bool bAlighRight, bool bAlighTop, bool bAlignBottom)
	{
		m_bAlignLeft = bAlignLeft;
		m_bAlignRight = bAlighRight;
		m_bAlignTop = bAlighTop;
		m_bAlignBottom = bAlignBottom;
	}

	void Set_ApplyScroll(bool bApplyScroll) { m_bApplyScroll = bApplyScroll; }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	TCHAR* Dbg_Text() override;

private:
	TCHAR* m_pText;

	bool m_bAlignLeft, m_bAlignRight, m_bAlignTop, m_bAlignBottom;

	bool m_bApplyScroll;
};

