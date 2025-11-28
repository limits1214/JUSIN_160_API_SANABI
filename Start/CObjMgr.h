#pragma once
#include "CObj.h"

class CObjMgr
{
public:
	void Add_Object(OBJID eID, CObj* pObj);

	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	// 객체리스트 제거
	void Dead_ID(OBJID eID);
	void Dead_ID(list<OBJID> eIdList);
	void Dead_ID_Except(list<OBJID> eIdList);

	// 객체 리스트포인터 가져오기
	list<CObj*>* Get_ObjectList();
	list<CObj*>* Get_ObjectList(OBJID eID);

	// 시퀀스 아이디로 단일Obj 조회
	CObj* Get_Obj_By_Seq(long lSeq);
	// 해당 오브젝트가 현재 어떤 OBJID소속인지 조회
	OBJID Get_ObjID_By_Obj(CObj* pObj);

	// 부모 없는 애들, 즉 최상위 계층인 애들
	list<CObj*> Make_NoParentList();

	// 계층 뷰 리턴
	map<CObj*, list<pair<OBJID, CObj*>>> Get_HierarchyView();
	void RefreshHierarchyView();

	// 전체 ObjList들의 계층을 만들어낸다.
	map<CObj*, list<CObj*>> Make_Hierarchy();
	map<CObj*, list<pair<OBJID, CObj*>>> Make_HierarchyObjIDPair();

	// 주어진 Obj이하 계층을 반환한다.
	list<CObj*> Get_HierarchyList(CObj* pObj);
	map<CObj*, list<CObj*>> Get_HierarchyMap(CObj* pObj);

	list<pair<OBJID, CObj*>> Get_HierarchyObjIDPairList(CObj* pObj);
	map<CObj*, list<pair<OBJID, CObj*>>> Get_HierarchyObjIDPairMap(CObj* pObj);

	void Make_Render_Order(list<CObj*>* pRDOList);

// FOR REMOVE
private:
	// 업데이트 리스트는 건드리지 않는거로 하자
	void Add_Object_TargetNext(OBJID eID, CObj* pTarget, CObj* pObj);
	// 객체 제거처리는 Dead로 통일
	void Delete_ID(OBJID eID);

private:
	list<CObj*> m_ObjList[OBJ_END];
	map<CObj*, list<pair<OBJID, CObj*>>> m_HierarchyViewMap;

// SINGLETON
private:
	CObjMgr();
	CObjMgr& operator=(CObjMgr&) = delete;
	CObjMgr(const CObjMgr&) = delete;
	~CObjMgr();

public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr* m_pInstance;
};

