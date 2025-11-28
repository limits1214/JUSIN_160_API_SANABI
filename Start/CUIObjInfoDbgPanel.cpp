#include "pch.h"
#include "CUIObjInfoDbgPanel.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CObjDbgText.h"
CUIObjInfoDbgPanel::CUIObjInfoDbgPanel()
	:m_lObjSeq(0)
{
	Set_DbgName(_T("CUIObjInfoDbgPanel"));
}

CUIObjInfoDbgPanel::~CUIObjInfoDbgPanel()
{
	Release();
}

void CUIObjInfoDbgPanel::Initialize()
{
	CUIObjPanel::Initialize();

	{
		CUIObjText* pText = new CUIObjText;
		pText->Initialize();
		pText->Set_Pos(0, 0);
		pText->Set_Parent(this->m_pUIContentBox);
		//OBJID eID = Get_ParentObjIdWithDefault(OBJ_DBG_UI);
		//CObjMgr::Get_Instance()->Add_Object_TargetNext(eID, this->m_pUIContentBox, pText);
		CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pText);
	}
}

int CUIObjInfoDbgPanel::Update()
{
	int iUpdateResult = CUIObjPanel::Update();
	if (iUpdateResult != OBJ_NOEVENT)
		return iUpdateResult;

	{

		auto hiermap = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
		list<CObj*> hier = CObjMgr::Get_Instance()->Get_HierarchyList(this->m_pUIContentBox);
		CObj* parent = hier.front();
		hier.pop_front();
		//for (auto*& a : hier)
		//{
		//	a->Set_Active_Cascade(false);
		//}

		auto pText = dynamic_cast<CUIObjText*>(hier.back());
		CObj* pObj = CObjMgr::Get_Instance()->Get_Obj_By_Seq(m_lObjSeq);
		if (pObj == nullptr)
		{
			Set_Dead_Cascade();
			return OBJ_DEAD;
		}

		map<CObj*, list<pair<OBJID, CObj*>>> hierMap = CObjMgr::Get_Instance()->Get_HierarchyObjIDPairMap(pObj);
		

		TCHAR szText[1024]{};

		for (auto& pair: hierMap)
		{
			TCHAR szTemp[256]{};
			//pair.second->Get_DbgName(szTemp);
			pair.first->Get_DbgName(szTemp);
			lstrcat(szText, szTemp);
			lstrcat(szText, _T(":\n"));
			for (auto& pair : pair.second)
			{
				TCHAR szTemp2[256]{};
				pair.second->Get_DbgName(szTemp2);
				lstrcat(szText, _T("    \n"));
				lstrcat(szText, szTemp2);
			}
			lstrcat(szText, _T("\n----\n"));
			//lstrcat(szText, szTemp);
		}
		lstrcat(szText, _T("\nEND\n"));
		//for (auto& pair : hierList)
		//{
		//	TCHAR szTemp[256];
		//	pair.second->Get_DbgName(szTemp);
		//	lstrcat(szText, _T("\n"));
		//	lstrcat(szText, szTemp);
		//}

		pText->Set_Text(szText);


		CObjDbgText* pDbgText = dynamic_cast<CObjDbgText*>(pObj);
		if (false && pDbgText != nullptr)
		{
			TCHAR* pT = pDbgText->Dbg_Text();
			pText->Set_Text(szText);
			Safe_Delete(pT);
		}
		

		//auto info = this->m_pUIContentBox->Get_Info();
		//CObj* pObj = CObjMgr::Get_Instance()->Get_Obj_By_ID(m_lObjSeq);
		//CObjDbgText* pDbgText = dynamic_cast<CObjDbgText*>(pObj);
		//if (pDbgText != nullptr)
		//{
		//	TCHAR* pT = pDbgText->Dbg_Text();
		//	CUIObjText* pText = new CUIObjText;
		//	pText->Initialize();
		//	//pText->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
		//	pText->Set_Pos(0, 0);
		//	pText->Set_Text(pT);
		//	pText->Set_Parent(this->m_pUIContentBox);
		//	pText->Set_CX(info->fCX);
		//	pText->Set_CY(info->fCY);
		//	CObjMgr::Get_Instance()->Add_Object_TargetNext(OBJ_UI, parent, pText);
		//	Safe_Delete(pT);
		//}
		//else
		//{

		//}
	}



	return OBJ_NOEVENT;
}

void CUIObjInfoDbgPanel::Late_Update()
{
	CUIObjPanel::Late_Update();
}

void CUIObjInfoDbgPanel::Render(HDC hDC)
{
	CUIObjPanel::Render(hDC);
}

void CUIObjInfoDbgPanel::Release()
{
	CUIObjPanel::Release();
}
