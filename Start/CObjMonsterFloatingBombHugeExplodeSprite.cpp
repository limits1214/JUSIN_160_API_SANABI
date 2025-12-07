#include "pch.h"
#include "CObjMonsterFloatingBombHugeExplodeSprite.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
CObjMonsterFloatingBombHugeExplodeSprite::CObjMonsterFloatingBombHugeExplodeSprite()
{
	Set_DbgName(_T("CObjMonsterFloatingBombHugeExplodeSprite"));
}

CObjMonsterFloatingBombHugeExplodeSprite::~CObjMonsterFloatingBombHugeExplodeSprite()
{
	Release();
}

void CObjMonsterFloatingBombHugeExplodeSprite::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 512;
	m_tInfo.fCY = 512;
	m_eFrameKey = FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512;
	m_eCurState = FSI_MOB_FLTBOMB_EXPLODEHUGE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjMonsterFloatingBombHugeExplodeSprite::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	int end = FrameStateId_To_Frame(FSI_BOSS_CLUSTER_BOMBLET_EXPLODE, dwNow).iEnd;
	if (m_tFrame.iStart == end)
	{
		Set_Dead();
	}

	Move_Frame();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterFloatingBombHugeExplodeSprite::Late_Update()
{
	Motion_Change();
}

void CObjMonsterFloatingBombHugeExplodeSprite::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);
}

void CObjMonsterFloatingBombHugeExplodeSprite::Release()
{
}
void CObjMonsterFloatingBombHugeExplodeSprite::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}
