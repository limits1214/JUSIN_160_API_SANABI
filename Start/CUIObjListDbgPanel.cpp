#include "pch.h"
#include "CUIObjListDbgPanel.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CUIObjRectButton.h"
#include "CUIObjInfoDbgPanel.h"

CUIObjListDbgPanel::CUIObjListDbgPanel()
	:m_eObjID(OBJ_END)
{
	Set_DbgName(_T("CUIObjListDbgPanel"));
}

CUIObjListDbgPanel::~CUIObjListDbgPanel()
{
	Release();
}

void CUIObjListDbgPanel::Initialize()
{
	CUIObjPanel::Initialize();
}

int CUIObjListDbgPanel::Update()
{
	int iUpdateResult = CUIObjPanel::Update();
	if (iUpdateResult != OBJ_NOEVENT)
		return iUpdateResult;



	{
		list<CObj*>* oblList = CObjMgr::Get_Instance()->Get_ObjectList(m_eObjID);

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
		int listSize = oblList->size();
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

			//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
			for (auto*& a : tempList)
			{
				//CObjMgr::Get_Instance()->Add_Object_TargetNext(eID, parent, a);
				CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
			}
		}

		int idx = 0;
		for (int i = startIemIdx; i < endItemIdx; ++i)
		{
			auto iter = oblList->begin();
			auto iter2 = std::next(iter, i);
			auto sq = (*iter2)->Get_Seq();
			TCHAR szDbgName[256];
			(*iter2)->Get_DbgName(szDbgName);

			auto iter3 = std::next(targetBtnList.begin(), idx);
			(*iter3)->Set_Active_Cascade(true);

			(*iter3)->Set_CX(info->fCX);
			(*iter3)->Set_CY(itemHeight);
			(*iter3)->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
			(*iter3)->Set_Parent(this->m_pUIContentBox);
			(*iter3)->Set_OnKeyDown([=]() {
				CUIObjInfoDbgPanel* pDbgPanel = new CUIObjInfoDbgPanel;
				TCHAR szObjText[256]{};
				ObjID_To_Text(static_cast<OBJID>(m_eObjID), szObjText);

				TCHAR szText[256]{};
				swprintf_s(szText, _T("%s-%d-%s"), szObjText, sq, szDbgName);
				//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
				CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
				pDbgPanel->Initialize();
				pDbgPanel->Set_CX(WINCX >> 2);
				pDbgPanel->Set_CY(WINCY >> 2);
				pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
				pDbgPanel->Set_Header_Text(szText);
				pDbgPanel->Set_ObjSeq(sq);
				});



			//CObjMgr::Get_Instance()->RefreshHierarchyView();
			auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
			TCHAR szTemp[256]{};
			swprintf_s(szTemp, _T("%d-%d-%s"), i, sq, szDbgName);
			dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTemp);

			++idx;
		}


	}














	//{
	//	list<CObj*> hier = CObjMgr::Get_Instance()->Get_Hierarchy(this->m_pUIContentBox);
	//	CObj* parent = hier.front();
	//	hier.pop_front();
	//	for (auto*& a : hier)
	//	{
	//		a->Set_Dead();
	//	}

	//	list<CObj*> tempList;
	//	list<CObj*>* oblList = CObjMgr::Get_Instance()->Get_ObjectList(m_eObjID);

	//	auto info = this->m_pUIContentBox->Get_Info();
	//	auto itemHeight = 20;

	//	int viewItemCnt = info->fCY / itemHeight;

	//	
	//	int listSize = oblList->size();;
	//	int startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
	//	int endItemIdx = startIemIdx + viewItemCnt;
	//	if (endItemIdx > listSize)
	//	{
	//		endItemIdx = listSize;
	//	}

	//	int idx = 0;
	//	for (int i = startIemIdx; i < endItemIdx; ++i)
	//	{

	//		auto iter = oblList->begin();
	//		auto iter2 = std::next(iter, i);

	//		auto sq = (*iter2)->Get_Seq();

	//		CUIObjRectButton* pRectBtn = new CUIObjRectButton;

	//		pRectBtn->Initialize();
	//		pRectBtn->Set_CX(info->fCX);
	//		pRectBtn->Set_CY(itemHeight);
	//		pRectBtn->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
	//		pRectBtn->Set_Parent(this->m_pUIContentBox);
	//		pRectBtn->Set_OnKeyDown([=]() {
	//			CUIObjInfoDbgPanel* pDbgPanel = new CUIObjInfoDbgPanel;
	//			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pDbgPanel);
	//			pDbgPanel->Initialize();
	//			pDbgPanel->Set_CX(WINCX >> 2);
	//			pDbgPanel->Set_CY(WINCY >> 2);
	//			pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
	//			pDbgPanel->Set_Header_Text(_T("DBG_PANEL3"));
	//			pDbgPanel->Set_ObjSeq(sq);
	//			});



	//		TCHAR szTemp[256];
	//		swprintf_s(szTemp, _T("%d-%d"), i, sq );

	//		CUIObjText* pText = new CUIObjText;
	//		
	//		pText->Initialize();
	//		//pText->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
	//		pText->Set_Pos(0, 0);
	//		pText->Set_Text(szTemp);
	//		pText->Set_Parent(pRectBtn);
	//		pText->Set_CX(info->fCX);
	//		pText->Set_CY(itemHeight);
	//		//pText->Set_Aligh(true, false, false, false);

	//		tempList.push_back(pText);
	//		tempList.push_back(pRectBtn);

	//		++idx;
	//	}

	//	for (auto*& a : tempList)
	//	{
	//		CObjMgr::Get_Instance()->Add_Object_TargetNext(OBJ_UI, parent, a);
	//	}
	//}



	return OBJ_NOEVENT;
}

void CUIObjListDbgPanel::Late_Update()
{
	CUIObjPanel::Late_Update();
}

void CUIObjListDbgPanel::Render(HDC hDC)
{
	CUIObjPanel::Render(hDC);
}

void CUIObjListDbgPanel::Release()
{
	CUIObjPanel::Release();
}
