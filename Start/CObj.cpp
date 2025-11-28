#include "pch.h"
#include "CObj.h"
#include "CTimeMgr.h"
#include "CObjMgr.h"

unsigned long long CObj::seqGenerator = 0;


void CObj::Set_Dead()
{
	m_bDead = true;
}

//TODO ¿Á±Õ¡¶∞≈
void CObj::Set_Dead_Cascade()
{
	//map<CObj*, list<CObj*>> hier = CObjMgr::Get_Instance()->Make_Hierarchy();
	////set<CObj*> tSet;

	//list<CObj*> targetList;

	//list<CObj*> tempList;
	//tempList.push_back(this);

	//while (!tempList.empty())
	//{
	//	CObj* node = tempList.front();
	//	tempList.pop_front();
	//	///
	//	targetList.push_back(node);
	//	///
	//	for (auto child : hier[node])
	//	{
	//		tempList.push_back(child);
	//	}
	//}

	list<CObj*> targetList = CObjMgr::Get_Instance()->Get_HierarchyList(this);

	for (auto*& pObj : targetList)
	{
		pObj->Set_Dead();
	}

	/////////////////////////////////////
	//map<CObj*, list<CObj*>> h = CObjMgr::Get_Instance()->Make_Hierarchy();
	//int dbg = 0;

	//if (!h[this].empty())
	//{
	//	for (auto*& child : h[this])
	//	{
	//		child->Set_Dead_Cascade();
	//	}
	//}

	//m_bDead = true;
}

void CObj::Set_Active_Cascade(bool bActive)
{
	list<CObj*> targetList = CObjMgr::Get_Instance()->Get_HierarchyList(this);

	for (auto*& pObj : targetList)
	{
		pObj->Set_Active(bActive);
	}
}

CObj* CObj::Get_SuperParent()
{
	CObj* pBefore = this;
	CObj* pParent = m_pParent;
	while (pParent != nullptr)
	{
		pBefore = pParent;
		pParent = pParent->Get_Parent();
	}
	return this;
}

OBJID CObj::Get_ParentObjIdWithDefault(OBJID eDefualtObjID)
{
	CObj* pBefore = this;
	CObj* pParent = m_pParent;
	while (pParent != nullptr)
	{
		pBefore = pParent;
		pParent = pParent->Get_Parent();
	}
	OBJID eID = CObjMgr::Get_Instance()->Get_ObjID_By_Obj(pBefore);

	if (eID == OBJ_END)
		return eDefualtObjID;
	else
		return eID;
}

void CObj::Update_Rect()
{
	float fParentX = 0, fParentY = 0;
	Calculate_Parent_Pos(&fParentX, &fParentY);
	float fHalfWidth = m_tInfo.fCX * 0.5f;
	float fHalfHeight = m_tInfo.fCY * 0.5f;
	m_tRect.left = (LONG)((m_tInfo.fX - fHalfWidth) + fParentX);
	m_tRect.top = (LONG)((m_tInfo.fY - fHalfHeight) + fParentY);
	m_tRect.right = (LONG)((m_tInfo.fX + fHalfWidth) + fParentX);
	m_tRect.bottom = (LONG)((m_tInfo.fY + fHalfHeight) + fParentY);
}

void CObj::Move_Frame()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();

	if (m_tFrame.dwSpeed + m_tFrame.dwTime < dwNow)
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime += m_tFrame.dwSpeed;

		if (m_tFrame.iStart > m_tFrame.iEnd)
		{
			m_tFrame.iStart = 0;
		}
	}
}

void  CObj::Set_Parent(CObj* pObj)
{
	m_pParent = pObj;
	CObjMgr::Get_Instance()->RefreshHierarchyView();
}
void CObj::Calculate_Parent_Pos(float* pfX, float* pfY)
{
	CObj* pParent = m_pParent;
	while (pParent != nullptr)
	{
		//if (pParent->Get_Dead())
		//{
		//	continue;
		//}
		//if (!pParent->Get_Active())
		//{
		//	continue;
		//}

		*pfX += pParent->Get_Info()->fX;
		*pfY += pParent->Get_Info()->fY;

		pParent = pParent->Get_Parent();
	}
}

CObj::CObj()
	: m_bDead(false), m_pParent(nullptr), m_bActive(true), m_bVisible(true)
	, m_eRdo(RDO_0), m_eRdo2(RDO_0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(m_szDbgName, sizeof(m_szDbgName));

	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_tFrame.dwTime = dwNow;

	m_lSeq = ++CObj::seqGenerator;
}

CObj::~CObj()
{
	//m_pParent = nullptr;
}
