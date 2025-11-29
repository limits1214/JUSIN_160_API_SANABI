#include "pch.h"
#include "CUIObjDbgPanel.h"
#include "CUIObjListDbgPanel.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CUIObjRectButton.h"

CUIObjDbgPanel::CUIObjDbgPanel()
{
	Set_DbgName(_T("CUIObjDbgPanel"));
}

CUIObjDbgPanel::~CUIObjDbgPanel()
{
	Release();
}

void CUIObjDbgPanel::Initialize()
{
	CUIObjPanel::Initialize();

	{
		list<CObj*> hier = CObjMgr::Get_Instance()->Get_HierarchyList(this->m_pUIContentBox);
		CObj* parent = hier.front();

		//list<CObj*> tempList;
		list<CObj*>* oblList = CObjMgr::Get_Instance()->Get_ObjectList();

		auto info = this->m_pUIContentBox->Get_Info();
		auto itemHeight = 20;

		int viewItemCnt = info->fCY / itemHeight;
		//int viewItemCnt = 1;

		//OBJ_END
		int listSize = OBJ_END;
		int startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
		int endItemIdx = startIemIdx + viewItemCnt;
		if (endItemIdx > listSize)
		{
			endItemIdx = listSize;
		}

		int idx = 0;
		for (int i = 0; i < OBJ_END; ++i)
		{


			CUIObjRectButton* pRectBtn = new CUIObjRectButton;
			pRectBtn->Set_DbgName(_T("O_D_P_BTN"));
			pRectBtn->Initialize();
			pRectBtn->Set_CX(info->fCX);
			pRectBtn->Set_CY(itemHeight);
			pRectBtn->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
			pRectBtn->Set_Parent(this->m_pUIContentBox);
			CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pRectBtn);
			//pRectBtn->Set_OnKeyDown([=]() {
			//	CUIObjListDbgPanel* pDbgPanel = new CUIObjListDbgPanel;
			//	OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
			//	CObjMgr::Get_Instance()->Add_Object(eID, pDbgPanel);
			//	pDbgPanel->Initialize();
			//	pDbgPanel->Set_CX(WINCX >> 2);
			//	pDbgPanel->Set_CY(WINCY >> 2);
			//	pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
			//	pDbgPanel->Set_Header_Text(_T("DBG_PANEL2"));
			//	pDbgPanel->Set_ObjID(static_cast<OBJID>(i));
			//	});



		

			TCHAR szTemp[256]{};
			swprintf_s(szTemp, _T("%d-%s: %d"), i, ObjID_To_Text(static_cast<OBJID>(i)), oblList[i].size());
			CUIObjText* pText = new CUIObjText;

			pText->Initialize();
			//pText->Set_Pos(0, + (itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
			pText->Set_Pos(0, 0);
			pText->Set_Text(szTemp);
			pText->Set_Parent(pRectBtn);
			pText->Set_CX(info->fCX);
			pText->Set_CY(itemHeight);
			//pText->Set_Aligh(true, false, false, false);
			CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pText);

			//tempList.push_back(pText);
			//tempList.push_back(pRectBtn);

			++idx;
		}

		//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
		//for (auto*& a : tempList)
		//{
		//	//CObjMgr::Get_Instance()->Add_Object_TargetNext(eID, parent, a);
		//	CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
		//}
	}
}

int CUIObjDbgPanel::Update()
{
	int iUpdateResult = CUIObjPanel::Update();
	if (iUpdateResult != OBJ_NOEVENT)
		return iUpdateResult;

	{
		list<CObj*> hier = CObjMgr::Get_Instance()->Get_HierarchyList(this->m_pUIContentBox);
		auto hiermap = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
		CObj* parent = hier.front();
		hier.pop_front();
		for (auto*& a : hier)
		{
			a->Set_Active_Cascade(false);
		}	

		//OBJ_END
		auto info = this->m_pUIContentBox->Get_Info();
		auto itemHeight = 20;
		int viewItemCnt = info->fCY / itemHeight;
		int listSize = OBJ_END;
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

		int idx = 0;
		for (int i = startIemIdx; i < endItemIdx; ++i)
		{
			

			auto iter2 = std::next(targetBtnList.begin(), idx);
			(*iter2)->Set_Active_Cascade(true);

			(*iter2)->Set_CX(info->fCX );
			(*iter2)->Set_CY(itemHeight);
			(*iter2)->Set_Pos(0, + (itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
			//(*iter2)->Set_Parent(this->m_pUIContentBox);
			(*iter2)->Set_OnKeyDown([=]() {
				CUIObjListDbgPanel* pDbgPanel = new CUIObjListDbgPanel;
				
				;
				//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
				CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
				pDbgPanel->Initialize();
				pDbgPanel->Set_CX(WINCX >> 2);
				pDbgPanel->Set_CY(WINCY >> 2);
				pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
				pDbgPanel->Set_Header_Text(ObjID_To_Text(static_cast<OBJID>(i)));
				pDbgPanel->Set_ObjID(static_cast<OBJID>(i));
			});

			list<CObj*>* oblList = CObjMgr::Get_Instance()->Get_ObjectList();
			
			TCHAR szTemp[256]{};
			swprintf_s(szTemp, _T("%d-%s: %d"), i, ObjID_To_Text(static_cast<OBJID>(i)), oblList[i].size());
			//TODO: nullcheck
			dynamic_cast<CUIObjText*>(hiermap[*iter2].front())->Set_Text(szTemp);

			++idx;
		}


		

		
//	for (int i = startIemIdx; i < endItemIdx; ++i)
//	{
//		CUIObjRectButton* pRectBtn = new CUIObjRectButton;
//		
//		pRectBtn->Initialize();
//		pRectBtn->Set_CX(info->fCX );
//		pRectBtn->Set_CY(itemHeight);
//		pRectBtn->Set_Pos(0, + (itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
//		pRectBtn->Set_Parent(this->m_pUIContentBox);
//		pRectBtn->Set_OnKeyDown([=]() {
//			CUIObjListDbgPanel* pDbgPanel = new CUIObjListDbgPanel;
//			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pDbgPanel);
//			pDbgPanel->Initialize();
//			pDbgPanel->Set_CX(WINCX >> 2);
//			pDbgPanel->Set_CY(WINCY >> 2);
//			pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
//			pDbgPanel->Set_Header_Text(_T("DBG_PANEL2"));
//			pDbgPanel->Set_ObjID(static_cast<OBJID>(i));
//			});




//		TCHAR* objText = ObjID_To_Text(static_cast<OBJID>(i));

//		TCHAR szTemp[256];
//		swprintf_s(szTemp, _T("%d-%s: %d"), i, objText, oblList[i].size());
//		CUIObjText* pText = new CUIObjText;
//		
//		pText->Initialize();
//		//pText->Set_Pos(0, + (itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
//		pText->Set_Pos(0, 0);
//		pText->Set_Text(szTemp);
//		pText->Set_Parent(pRectBtn);
//		pText->Set_CX(info->fCX);
//		pText->Set_CY(itemHeight);
//		//pText->Set_Aligh(true, false, false, false);

//		tempList.push_back(pText);
//		tempList.push_back(pRectBtn);

//		Safe_Delete(objText);

//		++idx;
//	}

//	for (auto*& a : tempList)
//	{
//		CObjMgr::Get_Instance()->Add_Object_TargetNext(OBJ_UI, parent, a);
//	}

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
	//	list<CObj*>* oblList = CObjMgr::Get_Instance()->Get_ObjectList();

	//	auto info = this->m_pUIContentBox->Get_Info();
	//	auto itemHeight = 20;

	//	int viewItemCnt = info->fCY / itemHeight;
	//	//int viewItemCnt = 1;

	//	//OBJ_END
	//	int listSize = OBJ_END;
	//	int startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
	//	int endItemIdx = startIemIdx + viewItemCnt;
	//	if (endItemIdx > listSize)
	//	{
	//		endItemIdx = listSize;
	//	}

	//	int idx = 0;
	//	for (int i = startIemIdx; i < endItemIdx; ++i)
	//	{


	//		CUIObjRectButton* pRectBtn = new CUIObjRectButton;
	//		
	//		pRectBtn->Initialize();
	//		pRectBtn->Set_CX(info->fCX );
	//		pRectBtn->Set_CY(itemHeight);
	//		pRectBtn->Set_Pos(0, + (itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
	//		pRectBtn->Set_Parent(this->m_pUIContentBox);
	//		pRectBtn->Set_OnKeyDown([=]() {
	//			CUIObjListDbgPanel* pDbgPanel = new CUIObjListDbgPanel;
	//			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pDbgPanel);
	//			pDbgPanel->Initialize();
	//			pDbgPanel->Set_CX(WINCX >> 2);
	//			pDbgPanel->Set_CY(WINCY >> 2);
	//			pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
	//			pDbgPanel->Set_Header_Text(_T("DBG_PANEL2"));
	//			pDbgPanel->Set_ObjID(static_cast<OBJID>(i));
	//			});




	//		TCHAR* objText = ObjID_To_Text(static_cast<OBJID>(i));

	//		TCHAR szTemp[256];
	//		swprintf_s(szTemp, _T("%d-%s: %d"), i, objText, oblList[i].size());
	//		CUIObjText* pText = new CUIObjText;
	//		
	//		pText->Initialize();
	//		//pText->Set_Pos(0, + (itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
	//		pText->Set_Pos(0, 0);
	//		pText->Set_Text(szTemp);
	//		pText->Set_Parent(pRectBtn);
	//		pText->Set_CX(info->fCX);
	//		pText->Set_CY(itemHeight);
	//		//pText->Set_Aligh(true, false, false, false);

	//		tempList.push_back(pText);
	//		tempList.push_back(pRectBtn);

	//		Safe_Delete(objText);

	//		++idx;
	//	}

	//	for (auto*& a : tempList)
	//	{
	//		CObjMgr::Get_Instance()->Add_Object_TargetNext(OBJ_UI, parent, a);
	//	}
	//}

	


	return OBJ_NOEVENT;
}

void CUIObjDbgPanel::Late_Update()
{
	CUIObjPanel::Late_Update();
}

void CUIObjDbgPanel::Render(HDC hDC)
{
	CUIObjPanel::Render(hDC);

	//auto a = this->m_pUIContentBox->Get_Rect();
	//Rectangle(hDC, a->left + 5, a->top + 5, a->right - 5, a->bottom - 5);
}

void CUIObjDbgPanel::Release()
{
	CUIObjPanel::Release();
}
