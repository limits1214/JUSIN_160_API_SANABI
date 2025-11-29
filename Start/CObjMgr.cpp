#include "pch.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}

CObjMgr::~CObjMgr()
{
	
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);

	RefreshHierarchyView();
}

void CObjMgr::Add_Object_TargetNext(OBJID eID, CObj* pTarget, CObj* pObj)
{
	bool bAdded = false;
	for (auto iter = m_ObjList[eID].begin(); iter != m_ObjList[eID].end(); ++iter)
	{
		if ((*iter) == pTarget)
		{
			auto next = ++iter;
			if (next != m_ObjList[eID].end())
			{
				m_ObjList[eID].insert(next, pObj);
			}
			else
			{
				m_ObjList[eID].push_back(pObj);
			}
			bAdded = true;
			break;
		}
	}

	if (!bAdded)
	{
		m_ObjList[eID].push_back(pObj);
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}

void CObjMgr::Dead_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		pObj->Set_Dead_Cascade();
}

void CObjMgr::Dead_ID(list<OBJID> eIdList)
{
	for (auto& id : eIdList)
	{
		Dead_ID(id);
	}
}

void CObjMgr::Dead_ID_Except(list<OBJID> eIdList)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		bool bSkip = false;
		for (auto& id : eIdList)
		{
			if (i == id)
			{
				bSkip = true;
				break;
			}
		}
		if (bSkip)
			continue;

		Dead_ID(static_cast<OBJID>(i));
	}
}


list<CObj*>* CObjMgr::Get_ObjectList()
{
	return m_ObjList;
}

list<CObj*>* CObjMgr::Get_ObjectList(OBJID eID)
{
	return &m_ObjList[eID];
}

CObj* CObjMgr::Get_Obj_By_Seq(long lID)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto*& pObj : m_ObjList[i])
		{
			if (pObj->Get_Seq() == lID)
				return pObj;
		}
	}
	return nullptr;
}

OBJID CObjMgr::Get_ObjID_By_Obj(CObj* _pObj)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto*& pObj : m_ObjList[i])
		{
			if (pObj == _pObj)
				return static_cast<OBJID>(i);
		}
	}
	return OBJ_END;
}

list<CObj*> CObjMgr::Make_NoParentList()
{
	list<CObj*> noParentList;

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto*& pObj : m_ObjList[i])
		{
			CObj* pParent = pObj->Get_Parent();
			if (pParent != nullptr)
			{
				
			}
			else
			{
				noParentList.push_back(pObj);
			}
		}
	}

	return noParentList;
}

map<CObj*, list<pair<OBJID, CObj*>>> CObjMgr::Get_HierarchyView()
{
	return m_HierarchyViewMap;
}

void CObjMgr::RefreshHierarchyView()
{
	m_HierarchyViewMap = Make_HierarchyObjIDPair();
}

map<CObj*, list<CObj*>> CObjMgr::Make_Hierarchy()
{
	map<CObj*, list<CObj*>> hierachy;

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto*& pObj : m_ObjList[i])
		{
			CObj* pParent = pObj->Get_Parent();
			if (pParent != nullptr)
			{
				hierachy[pParent].push_back(pObj);
			}
			else
			{
				// 단일 개체이거나 최상위
			}
		}
	}
	return hierachy;
}

map<CObj*, list<pair<OBJID, CObj*>>> CObjMgr::Make_HierarchyObjIDPair()
{
	map<CObj*, list<pair<OBJID, CObj*>>> hierachy;

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto*& pObj : m_ObjList[i])
		{
			CObj* pParent = pObj->Get_Parent();
			if (pParent != nullptr)
			{
				hierachy[pParent].push_back({static_cast<OBJID>(i), pObj});
			}
			else
			{
				// 단일 개체이거나 최상위
			}
		}
	}
	return hierachy;
}

list<CObj*> CObjMgr::Get_HierarchyList(CObj* pObj)
{
	map<CObj*, list<pair<OBJID, CObj*>>> hier = m_HierarchyViewMap;
	OBJID objID = Get_ObjID_By_Obj(pObj);
	list<CObj*> targetList;

	list<pair<OBJID, CObj*>> tempList;
	tempList.push_back({objID, pObj});

	while (!tempList.empty())
	{
		pair<OBJID, CObj*> node = tempList.front();
		tempList.pop_front();
		///
		targetList.push_back(node.second);
		///
		for (auto child : hier[node.second])
		{
			tempList.push_back(child);
		}
	}
	return targetList;
}

map<CObj*, list<CObj*>> CObjMgr::Get_HierarchyMap(CObj* _pObj)
{
	OBJID objID = Get_ObjID_By_Obj(_pObj);
	map<CObj*, list<pair<OBJID, CObj*>>> hierMap = m_HierarchyViewMap;

	map<CObj*, list< CObj*>> targetMap;

	list<pair<OBJID, CObj*>> tempList;
	tempList.push_back({ objID, _pObj });

	while (!tempList.empty())
	{
		pair<OBJID, CObj*> node = tempList.front();
		tempList.pop_front();
		///

		list<CObj*> tmplist;
		for(auto& a: hierMap[node.second])
		{
			tmplist.push_back(a.second);
		}

		targetMap[node.second] = tmplist;

		///
		for (auto child : hierMap[node.second])
		{
			tempList.push_back(child);
		}
	}

	return targetMap;
}

list<pair<OBJID, CObj*>> CObjMgr::Get_HierarchyObjIDPairList(CObj* pObj)
{
	map<CObj*, list<pair<OBJID, CObj*>>> hier = m_HierarchyViewMap;

	list<pair<OBJID, CObj*>> targetList;

	list<pair<OBJID, CObj*>> tempList;
	OBJID objID = Get_ObjID_By_Obj(pObj);
	// TODO: 만약 OBJ_END가리턴된다면? 처리
	tempList.push_back({ objID, pObj });

	while (!tempList.empty())
	{
		pair<OBJID, CObj*> node = tempList.front();
		tempList.pop_front();
		//
		targetList.push_back(node);
		//
		for (auto child : hier[node.second])
		{
			tempList.push_back(child);
		}
	}
	return targetList;
}

map<CObj*, list<pair<OBJID, CObj*>>> CObjMgr::Get_HierarchyObjIDPairMap(CObj* pObj)
{
	OBJID objID = Get_ObjID_By_Obj(pObj);
	map<CObj*, list<pair<OBJID, CObj*>>> hierMap = m_HierarchyViewMap;
	map<CObj*, list<pair<OBJID, CObj*>>> targetMap;

	list<pair<OBJID, CObj*>> tempList;
	tempList.push_back({objID, pObj });

	while (!tempList.empty())
	{
		pair<OBJID, CObj*> node = tempList.front();
		tempList.pop_front();
		///
		targetMap[node.second] = hierMap[node.second];
		///
		for (auto child : hierMap[node.second])
		{
			tempList.push_back(child);
		}
	}

	return targetMap;
}


void CObjMgr::Make_Render_Order(list<CObj*>* pRDOList)
{
	/*
	1. 계층 정렬 계층끼리 계층이 깊어질수록 나중에 렌더가 나중에되고, 동일 계층에서는 왼쪽에서 오른쪽으로 렌더리스트에 쌓인다(즉 오른쪽이 먼저 보인다)
	2. 계층의 최상위 부모의 렌더오더를 기준으로 렌더오더 정렬을 진행한다.
	*/
	list<CObj*> noParentList = Make_NoParentList();

	for (auto& pObj : noParentList)
	{
		RENDER_ORDERID rdo = pObj->Get_RDO();
		list<CObj*> hierList = Get_HierarchyList(pObj);
		for (auto*& pObj : hierList)
		{
			pRDOList[rdo].push_back(pObj);
		}
	}
}


void CObjMgr::Update()
{

	list<CObj*> deadList;

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			if (!(*iter)->Get_Active())
			{
				// 음... 다른방법 없을까?
				if ((*iter)->Get_Dead())
				{
					deadList.push_back(*iter);
					iter = m_ObjList[i].erase(iter);
				}
				else
				{
					++iter;
				}
				continue;
			}

			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				deadList.push_back(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	bool bDeadListEmpty = deadList.empty();

	for (auto*& pObj : deadList)
	{
		Safe_Delete<CObj*>(pObj);
	}

	if (!bDeadListEmpty)
	{
		RefreshHierarchyView();
	}
	
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto*& pObj : m_ObjList[i])
		{
			if (!pObj->Get_Active())
				continue;
			pObj->Late_Update();
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	list< CObj*> renderOrderList[RDO_END];
	Make_Render_Order(renderOrderList);

	for (int i = 0; i < RDO_END; ++i)
	{
		for (auto& pObj: renderOrderList[i])
		{
			if (!pObj->Get_Active())
				continue;
			if (!pObj->Get_Visible())
				continue;

			if (pObj->Get_UseMainScroll())
			{
				int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
				int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
				pObj->Apply_Scroll(iScrollX, iScrollY);
			}

			// culling
			if (
				pObj->Get_Rect()->left > WINCX
				||
				pObj->Get_Rect()->top > WINCY
				||
				pObj->Get_Rect()->right < 0
				||
				pObj->Get_Rect()->bottom < 0 
				)
			{
				continue;

				// TODO: 컬링이 되더라도 컬링에서 강제로 제외시키는거 만들까?
			}

			pObj->Render(hDC);
		}
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}