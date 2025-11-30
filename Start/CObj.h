#pragma once

#include "Define.h"
//#include "CObjMgr.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	void Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	void Set_CX(float fCX)
	{
		m_tInfo.fCX = fCX;
	}
	void Set_CY(float fCY)
	{
		m_tInfo.fCY = fCY;
	}
	void Set_Dead();
	void Set_Dead_Cascade();

	void Set_FrameKeyId(FRAME_KEY_ID eFrameKey)
	{
		m_eFrameKey = eFrameKey;
	}

	FRAME_KEY_ID Get_FrameKeyId()
	{
		return m_eFrameKey;
	}


	void		Set_PosX(float fX) { m_tInfo.fX += fX; }
	void		Set_PosY(float fY) { m_tInfo.fY += fY; }

	const RECT* Get_Rect() const { return &m_tRect; }
	const INFO* Get_Info() const { return &m_tInfo; }
	CObj* Get_Parent() { return m_pParent; }

	void Set_Parent(CObj* pObj);

	unsigned long long Get_Seq()
	{
		return m_lSeq;
	}
	bool Get_Active()
	{
		return m_bActive;
	}
	bool Get_Dead()
	{
		return m_bDead;
	}

	void Set_Active(bool bActive)
	{
		m_bActive = bActive;
	}
	void Set_Active_Cascade(bool bActive);
	bool Get_Visible()
	{
		return m_bVisible;
	}

	// TODO: set visible cascade
	void Set_Visible(bool bVisible)
	{
		m_bVisible = bVisible;
	}

	RENDER_ORDERID Get_RDO()
	{
		return m_eRdo;
	}
	void Set_RDO(RENDER_ORDERID eRdo)
	{
		m_eRdo = eRdo;
		m_eRdo2 = eRdo;
	}
	void Set_RDOTempChange(RENDER_ORDERID eRdo)
	{
		m_eRdo = eRdo;
	}
	void Set_RDOTempRestore()
	{
		m_eRdo = m_eRdo2;
	}

	void Set_DbgName(const TCHAR* pName)
	{
		lstrcpy(m_szDbgName, pName);
	}
	void Get_DbgName(TCHAR* pName)
	{
		lstrcpy(pName, m_szDbgName);
	}

	CObj* Get_SuperParent();

	void Set_Frame(FRAME tFrame)
	{
		m_tFrame = tFrame;
	}
	FRAME Get_Frame()
	{
		return m_tFrame;
	}

	void Apply_Scroll(int iScrollX, int iScrollY)
	{
		m_tRect.left += iScrollX;
		m_tRect.right += iScrollX;
		m_tRect.top += iScrollY;
		m_tRect.bottom += iScrollY;
	}

	void Set_UseMainScroll(bool bUseMainScroll) { m_bUseMainScroll = bUseMainScroll; }
	bool Get_UseMainScroll() { return m_bUseMainScroll; }

	// TODO: REMOVE
private:
	OBJID Get_ParentObjIdWithDefault(OBJID eDefualtObjID);


protected:
	void Update_Rect();
	void Move_Frame();
	void Calculate_Parent_Pos(float* pfX, float* pfY);
	

protected:
	unsigned long long m_lSeq;
	INFO m_tInfo;
	RECT m_tRect;

	bool m_bDead;

	FRAME		m_tFrame;

	FRAME_KEY_ID m_eFrameKey;

	CObj* m_pParent;

	bool m_bVisible;
	bool m_bActive;

	RENDER_ORDERID m_eRdo;
	RENDER_ORDERID m_eRdo2;

	TCHAR m_szDbgName[256];

	bool m_bUseMainScroll;

private:
	static unsigned long long seqGenerator;
};

