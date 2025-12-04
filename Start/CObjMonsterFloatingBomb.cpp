#include "pch.h"
#include "CObjMonsterFloatingBomb.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjMonsterFloatingBombSprite.h"
#include "CObjMgr.h"

CObjMonsterFloatingBomb::CObjMonsterFloatingBomb()
{
	Set_DbgName(_T("CObjMonsterFloatingBomb"));
}

CObjMonsterFloatingBomb::~CObjMonsterFloatingBomb()
{
	Release();
}

void CObjMonsterFloatingBomb::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;
	//m_eFrameKey = FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150;
	//m_eCurState = FSI_MOB_FLTBOMB_IDLE;
	//m_eCurState = FSI_MOB_FLTBOMB_EXCHOLDED_NEU;
	//m_eCurState = FSI_MOB_FLTBOMB_IDLE;
	//m_eCurState = FSI_MOB_FLTBOMB_IDLE;
	//m_eCurState = FSI_MOB_FLTBOMB_IDLE;


	//m_tInfo.fCX = 512;
	//m_tInfo.fCY = 512;
	//m_eFrameKey = FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512;
	//m_eCurState = FSI_MOB_FLTBOMB_EXPLODEHUGE;
	//m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());

	CObjMonsterFloatingBombSprite* pPltSprite = new CObjMonsterFloatingBombSprite;
	pPltSprite->Initialize();
	pPltSprite->Set_Parent(this);
	pPltSprite->Set_Pos(12, 5);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pPltSprite);
}

int CObjMonsterFloatingBomb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	//Move_Frame();
	
	return OBJ_NOEVENT;
}

void CObjMonsterFloatingBomb::Late_Update()
{
	//Motion_Change();
}

void CObjMonsterFloatingBomb::Render(HDC hDC)
{
	
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterFloatingBomb::Release()
{
}
void CObjMonsterFloatingBomb::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}