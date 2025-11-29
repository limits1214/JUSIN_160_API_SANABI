#include "pch.h"
#include "CUIObjText.h"

#include "CScrollMgr.h"
CUIObjText::CUIObjText()
	:m_pText(nullptr), m_bAlignBottom(false), m_bAlignTop(false), m_bAlignLeft(false), m_bAlignRight(false)
	
{
	Set_DbgName(_T("CUIObjText"));
}

CUIObjText::~CUIObjText()
{
	Release();
}

void CUIObjText::Initialize()
{
}

int CUIObjText::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (!m_bActive)
		return OBJ_NOEVENT;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CUIObjText::Late_Update()
{
	if (!m_bActive)
		return;
}

void CUIObjText::Render(HDC hDC)
{
	if (!m_bActive)
		return;
	if (!m_bVisible)
		return;


	RECT rc{};
	DrawText(hDC, m_pText, lstrlen(m_pText), &rc, DT_CALCRECT);

	LONG rcWidthHalf = LONG((rc.right - rc.left) * 0.5f);
	LONG rcHeightHalf = LONG((rc.bottom - rc.top) * 0.5f);

	LONG rectWidthHalf = LONG((m_tRect.right - m_tRect.left) * 0.5f);
	LONG rectHeightHalf = LONG((m_tRect.bottom - m_tRect.top) * 0.5f);

	// 가운데
	{
		rc.left = m_tRect.left + rectWidthHalf - rcWidthHalf;
		rc.right = rc.left + rcWidthHalf * 2;
		rc.top = m_tRect.top + rectHeightHalf - rcHeightHalf;
		rc.bottom = rc.top + rcHeightHalf * 2;
	}

	// 왼쪽
	if (m_bAlignLeft)
	{
		rc.left = m_tRect.left ;
		rc.right = rc.left + rcWidthHalf * 2;
	}

	// 오른쪽
	if (m_bAlignRight)
	{
		rc.left = m_tRect.right - rcWidthHalf * 2;
		rc.right = rc.left + rcWidthHalf * 2;
	}

	// 위
	if (m_bAlignTop)
	{
		rc.top = m_tRect.top ;
		rc.bottom = rc.top + rcHeightHalf * 2;
	}

	// 아래
	if (m_bAlignBottom)
	{
		rc.top = m_tRect.bottom - rcHeightHalf* 2;
		rc.bottom = rc.top + rcHeightHalf * 2;
	}

	DrawText(hDC, m_pText, lstrlen(m_pText), &rc, DT_CENTER);

	// Text는 출력하려면 그 크기를 CalRect로 계산하고 그거를 출력중인데
	// m_tRect를 사용하지 않아서 컬링이 이상하게 될수 있다.
	// 컬링은 m_tRect를 보고 하고 있어서 컬링을 제대로 하려면 반드시 CX, CY값을 잘 넘겨주자
}

void CUIObjText::Release()
{
	Safe_Delete(m_pText);
}

TCHAR* CUIObjText::Dbg_Text()
{
	TCHAR szText[256]{};
	
	const INFO* info = this->Get_Info();

	swprintf_s(szText, _T("INFO\nfX: %f\nfY: %f\nfCX: %f\nfCY: %f\n\n"), info->fX, info->fY, info->fCX, info->fCY);

	TCHAR* pText = new TCHAR[lstrlen(szText) + 1];
	lstrcpy(pText, szText);

	return pText;
}
