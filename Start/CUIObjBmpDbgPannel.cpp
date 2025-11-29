#include "pch.h"
#include "CUIObjBmpDbgPannel.h"
#include "CObjMgr.h"
#include "CUIObjRectButton.h"
#include "CUIObjText.h"
#include "CBmpMgr.h"

CUIObjBmpDbgPannel::CUIObjBmpDbgPannel()
{
	Set_DbgName(_T("CUIObjBmpDbgPannel"));
}

CUIObjBmpDbgPannel::~CUIObjBmpDbgPannel()
{
	Release();
}

void CUIObjBmpDbgPannel::Initialize()
{
	CUIObjPanel::Initialize();

}

int CUIObjBmpDbgPannel::Update()
{
	int iUpdateResult = CUIObjPanel::Update();
	if (iUpdateResult != OBJ_NOEVENT)
		return iUpdateResult;



	{
		auto bmpMap = CBmpMgr::Get_Instance()->Get_BmpMap();
		

		//list<CObj*>* oblList = CObjMgr::Get_Instance()->Get_ObjectList(m_eObjID);

		auto hiermap = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
		list<CObj*> hier = CObjMgr::Get_Instance()->Get_HierarchyList(this->m_pUIContentBox);
		CObj* parent = hier.front();
		hier.pop_front();
		for (auto*& a : hier)
		{
			a->Set_Active_Cascade(false);
		}

		auto info = this->m_pUIContentBox->Get_Info();
		auto itemHeight = 20;
		int viewItemCnt = info->fCY / itemHeight;
		int listSize = bmpMap->size();
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
				//CObjMgr::Get_Instance()->Add_Object_TargetNext(OBJ_DBG_UI, parent, a);
				CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
			}
		}

		int idx = 0;
		for (int i = startIemIdx; i < endItemIdx; ++i)
		{
			auto iter = bmpMap->begin();
			auto iter2 = std::next(iter, i);
			//auto sq = (*iter2)->Get_Seq();
			TCHAR szDbgName[256];
			//(*iter2)->Get_DbgName(szDbgName);

			auto iter3 = std::next(targetBtnList.begin(), idx);
			(*iter3)->Set_Active_Cascade(true);

			(*iter3)->Set_CX(info->fCX);
			(*iter3)->Set_CY(itemHeight);
			(*iter3)->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
			(*iter3)->Set_Parent(this->m_pUIContentBox);
			(*iter3)->Set_OnKeyDown([=]() {
				
				});


			auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
			TCHAR szTemp[256]{};
			swprintf_s(szTemp, _T("%d-%s"), i, (*iter2).first);
			dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTemp);
			dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_CX(info->fCX);
			dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_CY(itemHeight);
			++idx;
		}


	}




	return OBJ_NOEVENT;
}

void CUIObjBmpDbgPannel::Late_Update()
{
	CUIObjPanel::Late_Update();
}

void CUIObjBmpDbgPannel::Render(HDC hDC)
{
	CUIObjPanel::Render(hDC);
}

void CUIObjBmpDbgPannel::Release()
{
	CUIObjPanel::Release();
}
