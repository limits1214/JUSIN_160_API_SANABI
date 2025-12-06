#include "pch.h"
#include "CObjBossFirebirdBody.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CObjBossFireBird.h"

CObjBossFirebirdBody::CObjBossFirebirdBody()
{
	Set_DbgName(_T("CObjBossFirebirdBody"));
}

CObjBossFirebirdBody::~CObjBossFirebirdBody()
{
	Release();
}

void CObjBossFirebirdBody::Initialize()
{
	Set_UseMainScroll(true);

	m_tInfo.fCX = 684;
	m_tInfo.fCY = 684;
	//m_tInfo.fCY = 352;

	m_eFrameKey = FKI_Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8;
	m_eCurState = FSI_BOSS_FIREBIRD_BODY_NORMAL_IDLE;
	m_tFrame = FrameStateId_To_Frame(m_eCurState, CTimeMgr::Get_Instance()->Get_Tick_Count());
}

int CObjBossFirebirdBody::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	Move_Frame();

	return OBJ_NOEVENT;
}

void CObjBossFirebirdBody::Late_Update()
{
	Motion_Change();
	CObjBossFireBird* parent = dynamic_cast<CObjBossFireBird*>(m_pParent);
	if (parent != nullptr)
	{
		float angle = parent->Get_Angle();
		float		fDistance = sqrtf((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) +
			(m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

		// ÁÂ »ó´Ü

		m_tPoint[0].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 135.f) * PI / 180.f));
		m_tPoint[0].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 135.f) * PI / 180.f));

		// ¿ì »ó´Ü

		m_tPoint[1].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 45.f) * PI / 180.f));
		m_tPoint[1].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 45.f) * PI / 180.f));

		// ÁÂ »ó´Ü

		m_tPoint[2].x = long((m_tInfo.fCX / 2.f) + fDistance * cosf((angle + 225.f) * PI / 180.f));
		m_tPoint[2].y = long((m_tInfo.fCY / 2.f) - fDistance * sinf((angle + 225.f) * PI / 180.f));
	}
}

void CObjBossFirebirdBody::Render(HDC hDC)
{
	HDC		hPlgDC = CBmpMgr::Get_Instance()->Find_Image(_T("PLG"));
	HDC		hResetDC = CBmpMgr::Get_Instance()->Find_Image(_T("RESET"));
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	HDC		hBodyMaksDC = CBmpMgr::Get_Instance()->Find_Image(_T("BODY_MASK"));

	HBITMAP maskbmp = (HBITMAP) GetCurrentObject(hBodyMaksDC, OBJ_BITMAP);

	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);

	//PlgBlt(hDC,
	//	m_tPoint,
	//	hMemDC,
	//	m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX,
	//	(int)m_tInfo.fCY,
	//	//NULL, NULL, NULL
	//	maskbmp,
	//	m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY
	//);
	//BmpRender(
	//	hDC,
	//	m_tRect.left, m_tRect.top,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,

	//	hPlgDC,
	//	0, 0,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY
	//);
	//BitBlt(hDC,
	//	m_tRect.left, m_tRect.top,
	//	(int)m_tInfo.fCX,
	//	(int)m_tInfo.fCY,
	//	hPlgDC,
	//	0, 0, SRCCOPY);
	//BitBlt(hPlgDC,
	//	0, 0,
	//	(int)m_tInfo.fCX,
	//	(int)m_tInfo.fCY,
	//	hResetDC,
	//	0, 0, SRCCOPY);
/*



	BitBlt(hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		SRCCOPY);

	PlgBlt(hPlgDC,
		m_tPoint,
		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		NULL, NULL, NULL);


	BmpRender(
		hDC,
		m_tRect.left, m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hPlgDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY
	);

	BitBlt(hPlgDC,
		0, 0,
		1920,
		1080,
		hResetDC,
		0,
		0,
		SRCCOPY);


*/

	//BmpPlgRender(
	//	hDC,
	//	m_tRect.left, m_tRect.top,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,

	//	hMemDC,
	//	m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//	m_tPoint,
	//	hPlgDC,
	//	hResetDC
	//);
}

void CObjBossFirebirdBody::Release()
{
}

void CObjBossFirebirdBody::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}