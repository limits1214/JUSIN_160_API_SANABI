#include "pch.h"
#include "CUIObjScrollDbgPanel.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CUIObjRectButton.h"
#include "CScrollMgr.h"
#include "CKeyMgr.h"

CUIObjScrollDbgPanel::CUIObjScrollDbgPanel()
{
	Set_DbgName(_T("CUIObjScrollDbgPanel"));
}

CUIObjScrollDbgPanel::~CUIObjScrollDbgPanel()
{
	Release();
}

void CUIObjScrollDbgPanel::Initialize()
{
	CUIObjPanel::Initialize();
}

int CUIObjScrollDbgPanel::Update()
{
	int iUpdateResult = CUIObjPanel::Update();
	if (iUpdateResult != OBJ_NOEVENT)
		return iUpdateResult;

	auto hiermap = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
	list<CObj*> hier = CObjMgr::Get_Instance()->Get_HierarchyList(this->m_pUIContentBox);
	CObj* parent = hier.front();
	hier.pop_front();
	for (auto*& a : hier)
	{
		a->Set_Active_Cascade(false);
	}


	{
		auto info = this->m_pUIContentBox->Get_Info();
		auto itemHeight = 20;
		int viewItemCnt = info->fCY / itemHeight;
		int listSize = 6;
		int startIemIdx = 0;
		if (listSize > viewItemCnt)
		{
			startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
		}
		int endItemIdx = startIemIdx + viewItemCnt;
		if (endItemIdx > listSize)
		{
			endItemIdx = listSize;
		}

		list<CUIObjRectButton*> targetBtnList;

		for (auto iter = hiermap.begin(); iter != hiermap.end(); ++iter)
		{
			auto pBtn = dynamic_cast<CUIObjRectButton*>((*iter).first);
			if (pBtn != nullptr)
			{
				targetBtnList.push_back(pBtn);
			}
		}

		auto shortageCnt = viewItemCnt - targetBtnList.size();
		if (shortageCnt > 0)
		{
			list<CObj*> tempList;
			for (int i = 0; i < shortageCnt; ++i)
			{
				CUIObjRectButton* pRectBtn = new CUIObjRectButton;
				pRectBtn->Initialize();
				pRectBtn->Set_Parent(this->m_pUIContentBox);

				CUIObjText* pText = new CUIObjText;
				pText->Initialize();
				pText->Set_Parent(pRectBtn);

				tempList.push_back(pText);
				tempList.push_back(pRectBtn);

				targetBtnList.push_back(pRectBtn);
			}

			for (auto*& a : tempList)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
			}
		}


		int idx = 0;
		for (int i = startIemIdx; i < endItemIdx; ++i)
		{
			auto iter3 = std::next(targetBtnList.begin(), idx);
			(*iter3)->Set_Active_Cascade(true);

			(*iter3)->Set_CX(info->fCX);
			(*iter3)->Set_CY(itemHeight);
			(*iter3)->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
			(*iter3)->Set_Parent(this->m_pUIContentBox);

			(*iter3)->Set_OnKeyDown([=]() {
				if (i == 2)
				{
					// 위
					CScrollMgr::Get_Instance()->Set_ScrollY(TILECX * 8);
				}
				else if (i == 3)
				{
					// 아래
					CScrollMgr::Get_Instance()->Set_ScrollY(-TILECX * 8);
				}
				else if (i == 4)
				{
					// 왼쪽
					CScrollMgr::Get_Instance()->Set_ScrollX(TILECX * 8);
				}
				else if (i == 5)
				{
					// 오른쪽
					CScrollMgr::Get_Instance()->Set_ScrollX(-TILECX * 8);
				}
				});

			auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
			if (i == 0)
			{
				TCHAR szTmp[128];
				swprintf_s(szTmp, _T("%f"), CScrollMgr::Get_Instance()->Get_ScrollX());
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTmp);
			}
			else if (i == 1)
			{
				TCHAR szTmp[128];
				swprintf_s(szTmp, _T("%f"), CScrollMgr::Get_Instance()->Get_ScrollY());
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTmp);
			}
			else if (i == 2)
			{
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(_T("위"));
			}
			else if (i == 3)
			{
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(_T("아래"));
			}
			else if (i == 4)
			{
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(_T("왼쪽"));
			}
			else if (i == 5)
			{
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(_T("오른쪽"));
			}


			++idx;
		}
	}


	{
		// 위
		if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollY(TILECX );
		}

		// 왼
		if (CKeyMgr::Get_Instance()->Key_Pressing('J'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollX(TILECX );
		}

		// 아
		if (CKeyMgr::Get_Instance()->Key_Pressing('K'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollY(-TILECX );
		}

		// 오
		if (CKeyMgr::Get_Instance()->Key_Pressing('L'))
		{
			CScrollMgr::Get_Instance()->Set_ScrollX(-TILECX );
		}
	}

	return OBJ_NOEVENT;
}

void CUIObjScrollDbgPanel::Late_Update()
{
	CUIObjPanel::Late_Update();
}

void CUIObjScrollDbgPanel::Render(HDC hDC)
{
	CUIObjPanel::Render(hDC);
}

void CUIObjScrollDbgPanel::Release()
{
	CUIObjPanel::Release();
}
