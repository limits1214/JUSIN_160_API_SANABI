#include "pch.h"
#include "CObjPlayer.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CScrollMgr.h"
#include "CObjLine.h"
#include "CCollisionMgr.h"
#include "CObjRect.h"
#include "CObjCollisionRect.h"
#include "CObjPlayerArm.h"
#include "CObjMgr.h"
#include "CObjHookGuide.h"
#include "CObjMouse.h"
#include "CObjGrab.h"
#include "CObjPlayerSprite.h"
#include "CObjMonsterFloatingBomb.h"
#include "CObjUnstableKnockbackPlatformA.h"


CObjPlayer::CObjPlayer() :m_fHookMaxLength(0.f), m_pGrab(nullptr)
{
	Set_DbgName(_T("CObjPlayer"));
	ZeroMemory(&m_tHookLine, sizeof(LINE));
}

CObjPlayer::~CObjPlayer()
{
	Release();
}

void CObjPlayer::Initialize()
{
	DeltaInit();
	m_bJumpJustPressed = false;
	//CObjMovable::Initialize();
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 40.f;
	m_bRWallClimb = false;
	m_bLWallClimb = false;

	m_bWallTop = false;
	m_bWallDown = false;

	m_fHookMaxLength = 400.f;
	m_fHookMinLength = 200.f;

	//m_tInfo.fCX = 112.f;
	//m_tInfo.fCY = 104.f;

	m_bGrab = false;
	m_bGrabLoad = false;
	m_bGrabCeilingMove = false;

	m_fSpeed = 4.f;

	auto a = CBmpMgr::Get_Instance();

	m_bSwigDash = false;
	m_bDamaged = false;
	m_iDamagedInvicibleTime = 0;

	m_bMonsterExcStart = false;
	m_bMonsterExc = false;

	//m_eFrameKey = FKI_SNB;
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_SHEET.bmp", FrameKeyId_To_Text2(m_eFrameKey));
	
	//m_eFrameKey = FKI_Spr_SNB_SHEET_2;
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_Sheet2.bmp", FrameKeyId_To_Text2(m_eFrameKey));
	//m_tFrame.dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	//m_eCurState = FSI_SNB_R_IDLE;

	m_bUseMainScroll = true;

	CObjPlayerSprite* pPSprite = new CObjPlayerSprite;
	pPSprite->Initialize();
	pPSprite->Set_Parent(this);
	pPSprite->Set_Pos(10, -6);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPSprite);

	CObjPlayerArm* pArm = new CObjPlayerArm;
	pArm->Initialize();
	pArm->Set_Parent(this);
	pArm->Set_Pos(10, -6);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pArm);


}

int CObjPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	DeltaUpdate();

	Key_Input();


	Move_Frame();

	
	if (m_iDamagedInvicibleTime >= 0)
	{
		--m_iDamagedInvicibleTime;
	}
	if (m_bDamaged)
	{
		m_bDamaged = false;
		m_iDamagedInvicibleTime = 100;
	

		if (false && m_eDamagedDir == DIR_LEFT)
		{

		}
		else if (false && m_eDamagedDir == DIR_RIGHT)
		{

		}
		else
		{
			m_bDamagedDash = true;
			m_iDamagedDashableTime = 50;
			JumpStart(30.f, 135.f);

			// todo: hp 0, death
		}
		m_eCurState = FSI_SNB_R_DAMAGED;
	}

	if (m_bDamagedDash)
	{
		--m_iDamagedDashableTime;
		if (m_iDamagedDashableTime > 0)
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
			{
				if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
				{
					JumpStart(40.f, 180.f);
					m_bDamagedDash = false;
				}
				else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
				{
					JumpStart(40.f, 0.f);
					m_bDamagedDash = false;
				}
				else
				{
					JumpStart(40.f, 90.f);
					m_bDamagedDash = false;
				}
				m_eCurState = FSI_SNB_R_DAMAGEDDASH;
				
			}
		}

		if (m_iDamagedDashableTime < 0)
		{
			m_bDamagedDash = false;
		}
	}

	if (m_eCurState == FSI_SNB_R_RUNSTART ) /*&& m_tFrame.iStart == 1*/
	{
		m_eCurState = FSI_SNB_R_RUNNING;
	}
	else if (m_eCurState == FSI_SNB_R_RUNSTOP ) /*&& m_tFrame.iStart == 5*/
	{
		m_eCurState = FSI_SNB_R_IDLE;
	}
	else if (m_eCurState == FSI_SNB_R_FALLSTART )/* && m_tFrame.iStart == 2*/
	{
		m_eCurState = FSI_SNB_R_FALLING;
	}
	if (m_bGrabCeilingMove)
	{
		//m_bGravity = false;
		//m_bJump = false;
		//m_bGrab = false;
	}

	if (m_bMonsterExcStart)
	{
		if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pTarget))
		{
			if (m_pTarget != nullptr)
			{
				CObjMonsterFloatingBomb* pMonster = dynamic_cast<CObjMonsterFloatingBomb*>(m_pTarget);
				if (pMonster != nullptr)
				{
					m_tInfo.fX = m_pTarget->Get_Info()->fX;
					m_tInfo.fY = m_pTarget->Get_Info()->fY;

					m_bGravity = false;
					m_fGravityDeltaSum = 0;
					m_bJump = false;
					m_fJumpDeltaSum = 0;

					m_bMonsterExc = true;
				}
			}
		}
	}

	
	// 최소길이 보다 길어지면 제거 
	if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
	{
		if (m_pGrab != nullptr)
		{
			CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
			if (pGrab != nullptr)
			{
				int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
				int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

				float grabX = pGrab->Get_Info()->fX;
				float grabY = pGrab->Get_Info()->fY ;
				float width = grabX - m_tInfo.fX;
				float height = grabY - m_tInfo.fY;
				

				if (sqrtf(width * width + height * height) > m_fHookMaxLength)
				{
					m_pGrab->Set_Dead();
					m_pGrab = nullptr;
					m_bGrab = false;
				}
			}
		}
	}
	

	// 그랩 땡기기 
	if (m_bGrabLoad)
	{
		GrabLoad();
	}


	// 진자 운동
	if (!m_bGrabLoad && !m_bGrabCeilingMove && m_bGrab)
	{
		auto pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
		if (pGrab != nullptr)
		{
			m_eCurState = FSI_SNB_R_SWING;
			if (m_bSwigDash)
			{
				m_fPendRad -= 0.01;

		 		if (m_fPendRad < - 70.f * PI / 180.f)
				{
					m_bSwigDash = false;
				}

			}
			m_fGravityDeltaSum = 0;
			m_fJumpDeltaSum = 0;

			float w = sqrtf(/*GRAVITY*/ 500 / m_fPendLength);
			float l = m_fPendLength;

			auto ang0 = m_fPendRad;

			auto dbgAng = ang0 * 180.f / PI;

			cout << "dbgAng0: " << dbgAng << endl;

			float tar = ang0 * cosf(w * (m_fPendDeltaSum ) + 0.f);

			cout << "dbgTar: " << (tar * 180.f / PI) << endl;

			m_fPendCurr = tar;

			m_tInfo.fX = m_fPendStartX + sinf(tar) * l;
			m_tInfo.fY = m_fPendStartY + cosf(tar) * l ;
		}
	}

	if (m_bWallTop)
	{
		m_bWallTop = false;
		JumpStart(27.f, 90.f);
		m_bJumpJustPressed = false;
	}

	if (m_bWallDown)
	{
		m_bWallDown = false;
		JumpStart(10.f, 270.f);
		m_bJumpJustPressed = false;
	}


	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CObjPlayer::Late_Update()
{
	Offset();
	Motion_Change();


	//__super::Update_Rect();
}

void CObjPlayer::Render(HDC hDC)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BmpRender(
		hDC,
		m_tRect.left , m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,(int) m_tInfo.fCY
		);


	if (m_bGrab)
	{
		// 임시
		if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
		{
			if (m_pGrab != nullptr)
			{
				CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
				if (pGrab != nullptr)
				{
					int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
					int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

					float grabX = pGrab->Get_Info()->fX + iScrollX;
					float grabY = pGrab->Get_Info()->fY + iScrollY;

					MoveToEx(hDC, grabX, grabY, nullptr);
					LineTo(hDC, m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY);
				}
			}
		}
	}
	else
	{
		MoveToEx(hDC, m_tHookLine.tLeft.fX, m_tHookLine.tLeft.fY, nullptr);
		LineTo(hDC, m_tHookLine.tRight.fX, m_tHookLine.tRight.fY);
	}


}

void CObjPlayer::Release()
{

}

// late_update
void CObjPlayer::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
	CObjLine* pLine = dynamic_cast<CObjLine*>(pObj);
	COLL_ETC_LINE* pLineCollEtc = static_cast<COLL_ETC_LINE*>(etc);
	if (eCollID == COLL_LINE && pLine != nullptr && pLineCollEtc != nullptr)
	{
		COLL_ETC_LINE lineCollEtc = *pLineCollEtc;
		
		if (isnan(lineCollEtc.fY))
		{
			if (
				true
				&&
				// left margin
				(lineCollEtc.fX - (m_tInfo.fCX * 0.5f) < m_tInfo.fX)
				&&
				// right margin
				(lineCollEtc.fX + (m_tInfo.fCX * 0.5f) > m_tInfo.fX)
				)
			{
				// 왼쪽 접근
				if (lineCollEtc.fX - (m_tInfo.fCX * 0.5f) < m_tInfo.fX && m_tInfo.fX < lineCollEtc.fX)
				{
					//m_tInfo.fX = lineCollEtc.fX - (m_tInfo.fCX * 0.5f);
				}
				// 오른쪽 접근
				else if (lineCollEtc.fX + (m_tInfo.fCX * 0.5f) > m_tInfo.fX && m_tInfo.fX > lineCollEtc.fX)
				{
					//m_tInfo.fX = lineCollEtc.fX + (m_tInfo.fCX * 0.5f);
				}
			}
		}
		else
		{
			if (
				// under margin
				(lineCollEtc.fY + (m_tInfo.fCY * 0.5f) > m_tInfo.fY)
				&&
				// top margin
				(lineCollEtc.fY - (m_tInfo.fCY * 0.5f) < m_tInfo.fY)
				)
			{
				if (lineCollEtc.fY + (m_tInfo.fCY * 0.5f) > m_tInfo.fY && m_tInfo.fY > lineCollEtc.fY)
				{
					// 아래에서 접근
					//m_tInfo.fY = lineCollEtc.fY + (m_tInfo.fCY * 0.5f);
				}
				else if (lineCollEtc.fY - (m_tInfo.fCY * 0.5f) < m_tInfo.fY && m_tInfo.fY < lineCollEtc.fY)
				{
					// 위에서 접근
					//m_tInfo.fY = lineCollEtc.fY - (m_tInfo.fCY * 0.5f);
				}
			}
		}
	}

	CObjCollisionRect* pRect = dynamic_cast<CObjCollisionRect*>(pObj);
	COLL_ETC_RECT_EX* pRectExCollEtc = static_cast<COLL_ETC_RECT_EX*>(etc);

	if (
		eCollID == COLL_RECT_EX && pRect != nullptr && pRectExCollEtc != nullptr
	)
	{
		COLL_ETC_RECT_EX rectExCollEtc = *pRectExCollEtc;
		float fDistance = rectExCollEtc.fDistance;
		int iRectOpt = pRect->Get_Option();
		if (iRectOpt == ERI_CLIMABLE || iRectOpt == ERI_NO_CLIMABLE)
		{
			switch (rectExCollEtc.eDir)
			{
			case DIR_UP:
			{
				// 바닥에 닿은 순간

				//if (!m_bGrab)
				Move(DIR_UP, -fDistance);
				/*	if (m_bJumpJustPressed)
					{
						m_bJumpJustPressed = false;
						return;
					}*/



					//m_eCurState = FSI_SNBARM_R_IDLE;
					// on Ground;
				m_bJump = false;
				m_fGravityDeltaSum = 0;
				m_bGravity = true;
				m_bGround = true;

				m_bLWallClimb = false;
				m_bRWallClimb = false;



				if (m_eCurState != FSI_SNB_R_RUNNING)
				{
					//m_eCurState = FSI_SNB_R_IDLE;
				}

			}
			break;
			case DIR_DOWN:
			{
				int x = 0;
				//if (!m_bGrab)
				Move(DIR_DOWN, fDistance);
			}
			break;
			case DIR_LEFT:
			{
				//if (!m_bGrab)
				Move(DIR_LEFT, -fDistance);
				if (pRect->Get_Option() == ERI_CLIMABLE)
				{
					// 벽 왼쪽에서 벽타기
					if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
					{

						m_bLWallClimb = true;
					}


					if (m_bLWallClimb)
					{
						m_eCurState = FSI_SNB_R_WALLCLIMBUP;
						m_bJump = false;
						m_fJumpDeltaSum = 0;
						m_bGravity = false;
						m_fGravityDeltaSum = 0;

						float fRectY = (pRect->Get_Info()->fY - pRect->Get_Info()->fCY * 0.4f) + (m_tInfo.fCY * 0.0f);
						if (m_tInfo.fY <= fRectY)
						{
							m_bWallTop = true;
						}

						float fRectYDown = (pRect->Get_Info()->fY + pRect->Get_Info()->fCY * 0.5f); /*+ (m_tInfo.fCY * 0.6f)*/
						if (m_tInfo.fY >= fRectYDown)
						{
							m_bWallDown = true;
						}
					}
				}

			}
			break;
			case DIR_RIGHT:
			{
				//if (!m_bGrab)
				Move(DIR_RIGHT, fDistance);

				if (pRect->Get_Option() == ERI_CLIMABLE)
				{
					if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
					{

						m_bRWallClimb = true;
					}


					// 벽 오른쪽에서 벽타기
					// 벽 왼쪽에서 벽타기
					if (m_bRWallClimb)
					{
						m_eCurState = FSI_SNB_R_WALLCLIMBUP;
						m_bJump = false;
						m_fJumpDeltaSum = 0;
						m_bGravity = false;
						m_fGravityDeltaSum = 0;


						float fRectY = (pRect->Get_Info()->fY - pRect->Get_Info()->fCY * 0.4f) + (m_tInfo.fCY * 0.0f);
						if (m_tInfo.fY <= fRectY)
						{
							m_bWallTop = true;
						}

						float fRectYDown = (pRect->Get_Info()->fY + pRect->Get_Info()->fCY * 0.5f); /*+ (m_tInfo.fCY * 0.6f)*/
						if (m_tInfo.fY >= fRectYDown)
						{
							m_bWallDown = true;
						}

					}

				}
			}
			break;
			}
		}
		else if (iRectOpt == ERI_DAMAGE)
		{
			
			if (m_iDamagedInvicibleTime < 0)
			{
				m_iDamagedInvicibleTime = 100;
				m_bDamaged = true;
				m_eDamagedDir = rectExCollEtc.eDir;
			}
		}
	}
}


void CObjPlayer::Grab(CObj* pObj)
{
	if (!m_bGrab)
	{
		CObjGrab* pGrab = dynamic_cast<CObjGrab*>(pObj);
		
		if (pGrab->Get_CollisionOption() != ERI_CLIMABLE)
		{
			pObj->Set_Dead();
			return;
		}

		if (pGrab->Get_Dead())
		{
			return;
		}



		m_eCurState = FSI_SNB_R_SWING;
		m_bGrab = true;
		auto grabInfo = pObj->Get_Info();

		auto width = m_tInfo.fX - grabInfo->fX ;
		auto height = m_tInfo.fY - grabInfo->fY ;

		auto l = sqrtf(width * width + height * height);
		m_fPendLength = l;
		m_fPendDeltaSum = 0;
		m_fPendRad = atan2f(width, height);
		m_fPendStartX = grabInfo->fX;
		m_fPendStartY = grabInfo->fY;
	}
	
}

void CObjPlayer::Move(DIRECTION eDir, float fDistance)
{
	if (eDir == DIR_UP)
	{
		m_tInfo.fY += fDistance;
	}
	else if (eDir == DIR_DOWN)
	{
		m_tInfo.fY += fDistance;
	}
	else if (eDir == DIR_LEFT)
	{
		m_tInfo.fX += fDistance;
	}
	else if (eDir == DIR_RIGHT)
	{
		m_tInfo.fX += fDistance;
	}
}

void CObjPlayer::JumpStart(float fVZero, float fAngle)
{
	m_bJumpJustPressed = true;

	m_eCurState = FSI_SNB_R_JUMPING;

	m_bJump = true;
	m_fJumpDeltaSum = (16.f / 1000.f) * 1.f;

	

	m_bGravity = true;
	m_fGravityDeltaSum = 0;

	m_fJumpVZero = fVZero;
	m_fJumpAngle = fAngle;

	m_bLWallClimb = false;
	m_bRWallClimb = false;


	// 바로 반응 하게 한번 적용
	float fDstX, fDstY;
	ParabolaNoGravityEquation(m_fJumpVZero, m_fJumpAngle, m_fJumpDeltaSum, &fDstX, &fDstY);
	Move(DIR_LEFT, fDstX);
	Move(DIR_UP, -fDstY);


}

void CObjPlayer::JumpEnd()
{
}

void CObjPlayer::GrabLoad()
{
	if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
	{
		if (m_pGrab != nullptr)
		{
			CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
			if (pGrab != nullptr)
			{
				float width = pGrab->Get_Info()->fX - m_tInfo.fX;
				float height = pGrab->Get_Info()->fY - m_tInfo.fY;
				float fRad = atan2f(height, width);
				float x = cosf(fRad) * 30.f;
				float y = sinf(fRad) * 30.f;
				m_tInfo.fX += x;
				m_tInfo.fY += y;

				RECT rc;
				if (IntersectRect(&rc, pGrab->Get_Rect(), this->Get_Rect()))
				{
					if (pGrab->Get_Ceiling())
					{
						m_bGrabLoad = false;
						m_bGrabCeilingMove = true;
						
						// 들어가지 않게 체인 아래 위치시키기

						m_tInfo.fX = pGrab->Get_Info()->fX;
						m_tInfo.fY = (pGrab->Get_Info()->fY + pGrab->Get_Info()->fCY * 0.5f) + (m_tInfo.fCY * 0.5f);
					}
					else if (pGrab->Get_CollisionLeft())
					{
						m_bGrab = false;
						m_bGrabLoad = false;
						m_bLWallClimb = true;
					}
					else if (pGrab->Get_CollisionRight())
					{
						m_bGrab = false;
						m_bGrabLoad = false;
						m_bRWallClimb = true;
						
					}
					else {
						m_bGrab = false;
						m_bGrabLoad = false;

						m_bJump = false;
						m_bGravity = true;
						m_fGravityDeltaSum = 0;
						
						
					}
				}
			}
		}
	}
	
}

void CObjPlayer::MonsterExcStart(CObj* pMonster)
{
	Set_Target(pMonster);
	m_bMonsterExcStart = true;

	

}

void CObjPlayer::Key_Input()
{
	bool bKeyDownA = CKeyMgr::Get_Instance()->Key_Down('A');
	bool bPressingA = CKeyMgr::Get_Instance()->Key_Pressing('A');
	bool bKeyUpA = CKeyMgr::Get_Instance()->Key_Up('A');

	bool bKeyDownD = CKeyMgr::Get_Instance()->Key_Down('D');
	bool bPressingD = CKeyMgr::Get_Instance()->Key_Pressing('D');
	bool bKeyUpD = CKeyMgr::Get_Instance()->Key_Up('D');

	bool bKeyDownW = CKeyMgr::Get_Instance()->Key_Down('W');
	bool bKeyPressingW = CKeyMgr::Get_Instance()->Key_Pressing('W');
	bool bKeyUpW = CKeyMgr::Get_Instance()->Key_Up('W');

	bool bKeyDownS = CKeyMgr::Get_Instance()->Key_Down('S');
	bool bKeyPressingS = CKeyMgr::Get_Instance()->Key_Pressing('S');
	bool bKeyUpS = CKeyMgr::Get_Instance()->Key_Up('S');

	bool bKeyDownSpace = CKeyMgr::Get_Instance()->Key_Down(VK_SPACE);
	bool bKeyPressingSpace = CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE);

	bool bKeyDownLShift = CKeyMgr::Get_Instance()->Key_Pressing('Q');


	if (bKeyDownLShift)
	{
		//m_fPendRad += 1.f * PI / 180.f;
		m_bSwigDash = true;
	}

	if (m_bGrabCeilingMove)
	{
		if (bPressingA)
		{
			if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
			{
				if (m_pGrab != nullptr)
				{
					CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
					if (pGrab != nullptr)
					{
						auto info = m_pGrab->Get_Info();
						m_pGrab->Set_Pos(info->fX - m_fSpeed, info->fY);



						INFO grabCollisionInfo = pGrab->Get_CollisionRectInfo();
						INFO grabRect = *pGrab->Get_Info();


						if (grabRect.fX < grabCollisionInfo.fX - grabCollisionInfo.fCX * 0.5)
						{
							m_bGrabCeilingMove = false;


							if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
							{
								if (m_pGrab != nullptr)
								{
									CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
									if (pGrab != nullptr)
									{

										
										m_pGrab->Set_Dead();
										m_pGrab = nullptr;
										m_bGrab = false;
										m_bGravity = true;
										m_fGravityDeltaSum = 0;
										m_bJump = false;
										m_fJumpDeltaSum = 0;

										JumpStart(10.f, 110.f);
									}

								}
							}
						}


					}

				}
			}

			Move(DIR_LEFT, -m_fSpeed);
		}
		else if (bPressingD)
		{
			if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
			{
				if (m_pGrab != nullptr)
				{
					CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
					if (pGrab != nullptr)
					{
						auto info = m_pGrab->Get_Info();
						m_pGrab->Set_Pos(info->fX + m_fSpeed, info->fY);


						INFO grabCollisionInfo = pGrab->Get_CollisionRectInfo();
						INFO grabRect = *pGrab->Get_Info();


						

						if (grabRect.fX > grabCollisionInfo.fX + grabCollisionInfo.fCX * 0.5)
						{
							m_bGrabCeilingMove = false;


							if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
							{
								if (m_pGrab != nullptr)
								{
									CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
									if (pGrab != nullptr)
									{


										m_pGrab->Set_Dead();
										m_pGrab = nullptr;
										m_bGrab = false;
										m_bGravity = true;
										m_fGravityDeltaSum = 0;
										m_bJump = false;
										m_fJumpDeltaSum = 0;

										JumpStart(10.f, 70.f);
									}

								}
							}
						}


					}

				}
			}


			Move(DIR_RIGHT, m_fSpeed);
		}

		if (bKeyDownSpace)
		{
			m_bGrabCeilingMove = false;

			if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
			{
				if (m_pGrab != nullptr)
				{
					CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
					if (pGrab != nullptr)
					{

						if (m_bGrabCeilingMove)
						{
							if (pGrab->Get_Ceiling())
							{
								return;
							}
						}
						m_pGrab->Set_Dead();
						m_pGrab = nullptr;
						m_bGrab = false;
						m_bGravity = true;
						m_fGravityDeltaSum = 0;
						m_bJump = false;
						m_fJumpDeltaSum = 0;

						JumpStart(10.f, 270.f);
					}

				}
			}
		}
	}

	else if (m_bGrab)
	{
		// 오른쪽
		if (bPressingA)
		{
			
			float fPendAng = m_fPendRad * 180.f / PI;
			if (m_tInfo.fX <= m_fPendStartX)
			{
				// 진폭 늘리기
				if (fPendAng <= 0)
				{
					if (fPendAng > -180)
					{
						m_fPendRad -= 1.f * PI / 180;
					}
						
				}
				else
				{
					if (fPendAng < 180)
					{
						m_fPendRad += 1.f * PI / 180;
					}
						
				}
			}
			else
			{
				// 진폭 줄이기
				if (fPendAng <= 0)
				{
					if (fPendAng < -5)
					{
						m_fPendRad += 1.f * PI / 180;
					}
				}
				else
				{
					if (fPendAng > 5)
					{
						m_fPendRad -= 1.f * PI / 180;
					}
				}
			}
		}
		//  왼쪽
		else if (bPressingD)
		{
			float fPendAng = m_fPendRad * 180.f / PI;
			if (m_tInfo.fX <= m_fPendStartX)
			{
				// 진폭 줄이기
				if (fPendAng <= 0)
				{
					if (fPendAng < -5)
					{
						m_fPendRad += 1.f * PI / 180;
					}
				}
				else
				{
					if (fPendAng > 5)
					{
						m_fPendRad -= 1.f * PI / 180;
					}
				}
			}
			else
			{
				// 진폭 늘리기
				if (fPendAng <= 0)
				{
					if (fPendAng > -180)
					{
						m_fPendRad -= 1.f * PI / 180;
					}

				}
				else
				{
					if (fPendAng < 180)
					{
						m_fPendRad += 1.f * PI / 180;
					}

				}
			}

		}

		if (bKeyDownSpace)
		{
			// 그랩 당기기
			m_bGrabLoad = true;
		}
	}
	
	else if (m_bMonsterExc)
	{
		OBJID eTargetObjId = CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pTarget);
		if (bKeyPressingW)
		{
			Move(DIR_UP, -m_fSpeed);
			if (eTargetObjId != OBJ_END)
			{
				m_pTarget->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			}
			
		}
		if (bPressingA)
		{
			Move(DIR_LEFT, -m_fSpeed);
			if (eTargetObjId != OBJ_END)
			{
				m_pTarget->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			}
		}
		if (bKeyPressingS)
		{
			Move(DIR_DOWN, +m_fSpeed);
			if (eTargetObjId != OBJ_END)
			{
				m_pTarget->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			}
		}
		if (bPressingD)
		{
			Move(DIR_RIGHT, +m_fSpeed);
			if (eTargetObjId != OBJ_END)
			{
				m_pTarget->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			}
		}
	}
	else

	{
		if (bKeyDownA)
		{
			//if (m_eCurState != FSI_SNB_R_JUMPING)
				//m_eCurState = FSI_SNB_R_RUNSTART;
			m_fMoveLeftDeltaSum = 0;
		}

		if (bKeyDownD)
		{
			//if (m_eCurState != FSI_SNB_R_JUMPING)
				//m_eCurState = FSI_SNB_R_RUNSTART;
			m_fMoveRightDeltaSum = 0;
		}
		if (bKeyDownSpace)
		{
			if (m_bJump)
			{
				return;
			}

			if (m_bLWallClimb)
			{
				JumpStart(17.f, 110.f);
				m_bJumpJustPressed = false;
			}
			else if (m_bRWallClimb)
			{
				JumpStart(17.f, 70.f);
				m_bJumpJustPressed = false;
			}
			else
			{
				JumpStart(30.f, 90.f);
			}

		}
		if (bKeyPressingW)
		{
			if (m_bLWallClimb || m_bRWallClimb)
			{
				Move(DIR_UP, -m_fSpeed);
				m_eCurState = FSI_SNB_R_WALLCLIMBUP;
			}

		}
		else if (bKeyPressingS)
		{
			if (m_bLWallClimb || m_bRWallClimb)
			{
				Move(DIR_DOWN, m_fSpeed);
				m_eCurState = FSI_SNB_R_WALLCLIMBDOWN;
			}
		}

		
		if (bPressingA)
		{
			if (m_bLWallClimb)
			{
				// todo: timer
				//JumpStart(30.f, 100.f);
				//Move(DIR_LEFT, -m_fSpeed);
				m_eCurState = FSI_SNB_R_WALLCLIMBUP;
			}
			else
			{
				Move(DIR_LEFT, -m_fSpeed);
				if (!(m_eCurState == FSI_SNB_R_JUMPING || m_eCurState == FSI_SNB_R_FALLING || m_eCurState == FSI_SNB_R_FALLSTART))
					m_eCurState = FSI_SNB_R_RUNSTART;
			}
		}
		else if (bPressingD)
		{
			if (m_bRWallClimb)
			{
				// todo: timer
				//JumpStart(10.f, 75.f);
				//Move(DIR_RIGHT, m_fSpeed);
				m_eCurState = FSI_SNB_R_WALLCLIMBUP;
			}
			else
			{
				Move(DIR_RIGHT, m_fSpeed);
				if (!(m_eCurState == FSI_SNB_R_JUMPING || m_eCurState == FSI_SNB_R_FALLING || m_eCurState == FSI_SNB_R_FALLSTART))
					m_eCurState = FSI_SNB_R_RUNSTART;
			}


		}

		if (bKeyUpA || bKeyUpD)
		{
			if (m_eCurState == FSI_SNB_R_RUNNING)
			{
				m_eCurState = FSI_SNB_R_RUNSTOP;
			}
		}

	}


	

	



	//테스트용
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		Move(DIR_UP, -m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		Move(DIR_DOWN, m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		Move(DIR_LEFT, -m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		Move(DIR_RIGHT, m_fSpeed);
	}
}

void CObjPlayer::Motion_Change()
{
	DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
	if (m_ePreState != m_eCurState)
	{
		m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
		m_ePreState = m_eCurState;
	}
}

void CObjPlayer::Offset()
{
	int	iOffsetminX = 100;
	int	iOffsetmaxX = 700;

	int	iOffsetminY = 100;
	int	iOffsetmaxY = 500;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 왼쪽으로 플레이어가 이동 중
	if (iOffsetminX > m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
	}

	// 오른쪽으로 플레이어가 이동 중
	if (iOffsetmaxX < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}


	if (iOffsetminY > m_tInfo.fY + iScrollY)
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
	}

	if (iOffsetmaxY < m_tInfo.fY + iScrollY)
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
	}

}

void CObjPlayer::DeltaInit()
{
	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_fGravityDeltaSum = 0;
	m_fJumpDeltaSum = 0;

	m_fMoveLeftDeltaSum = 0;
	m_fMoveRightDeltaSum = 0;
	m_fPendDeltaSum = 0;

	m_bGravity = true;
	m_bJump = false;
	m_fJumpVZero = 0.f;
	m_fJumpAngle = 90.f;
}

void CObjPlayer::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;

	m_dwTime = dwNowTime;

	m_fGravityDeltaSum += dwDelta;
	m_fJumpDeltaSum += dwDelta;
	m_fMoveLeftDeltaSum += dwDelta;
	m_fMoveRightDeltaSum += dwDelta;
	m_fPendDeltaSum += dwDelta;

	if (m_bGrab)
	{
		return;
	}

	DWORD  dwGravityDeltaMax = 1;
	if (m_fGravityDeltaSum > dwGravityDeltaMax)
	{
		m_fGravityDeltaSum = dwGravityDeltaMax;
	}

	float tempG = 0;
	if (true && m_bGravity)
	{
		float fTmpG = GRAVITY * (m_fGravityDeltaSum * m_fGravityDeltaSum) * 0.5f;
		float fScaledTmpY = fTmpG * 13;
		float maxGravity = 50;
		if (fScaledTmpY > maxGravity)
		{
			//fScaledTmpY = maxGravity;
		}
		tempG = fScaledTmpY;
		Move(DIR_DOWN, fScaledTmpY);

	}

	if (true && m_bJump)
	{
 		DWORD  dwJumpDeltaMax = 1;
		if (m_fJumpDeltaSum > dwJumpDeltaMax)
		{
			m_fJumpDeltaSum = dwJumpDeltaMax;
		}


		float fDstX, fDstY;
		ParabolaNoGravityEquation(m_fJumpVZero , m_fJumpAngle, m_fJumpDeltaSum, &fDstX, &fDstY);
		Move(DIR_LEFT, fDstX);
		Move(DIR_UP, -fDstY);


		// 최대점프
		if (fDstY - tempG < 0)
		{
			int x = 0;
			//m_eCurState = FSI_SNB_R_FALLSTART;
		}
	}
}


void CObjPlayer::On_Mouse_Pos(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();

		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


		//float fParentX = m_pParent->Get_Info()->fX + iScrollX;
		//float fParentY = m_pParent->Get_Info()->fY + iScrollY;
		//LINEPOINT ptLeft{ fParentX, fParentY };
		float fPointX = (float)ptCurr.x;
		float fPointY = (float)ptCurr.y;
		LINEPOINT ptLeft{ m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY };
		LINEPOINT ptRight{ fPointX, fPointY };

		float fWidth = ptRight.fX - ptLeft.fX;
		float fHeight = ptRight.fY - ptLeft.fY;

		m_fHookAngle = atan2f(fHeight, fWidth);
		float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
		if (fDist > m_fHookMaxLength)
		{

			ptRight.fX = ptLeft.fX + cosf(m_fHookAngle) * m_fHookMaxLength;
			ptRight.fY = ptLeft.fY + sinf(m_fHookAngle) * m_fHookMaxLength;
		}

		m_tHookLine = { ptLeft, ptRight };

		pMouse->Mouse_PreventEvent();
	}
}




void CObjPlayer::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		if (pMouse->Get_Last_Key() == VK_LBUTTON)
		{
			POINT ptCurr = pMouse->Get_Pt_Curr();
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
			{
				if (m_pGrab != nullptr)
				{
					return;
					m_pGrab->Set_Dead();
					m_bGrab = false;
					m_pGrab = nullptr;
				}
			}

			CObjGrab* pGrab = new CObjGrab;
			pGrab->Initialize();
			/*pGrab->Set_Pos(fParentX, fParentY);*/
			pGrab->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			pGrab->Set_Angle(m_fHookAngle);
			pGrab->Set_Target(this);
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pGrab);
			m_pGrab = pGrab;
		}
		

	}
}

void CObjPlayer::On_Mouse_Key_Up(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		//ptCurr.x -= iScrollX;
		//ptCurr.y -= iScrollY;
			if (pMouse->Get_Last_Key() == VK_LBUTTON)
			{
				if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
				{
					if (m_pGrab != nullptr)
					{
						CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
						if (pGrab != nullptr)
						{

							if (m_bGrabCeilingMove)
							{
								if (pGrab->Get_Ceiling())
								{
									return;
								}
							}
							m_pGrab->Set_Dead();
							m_pGrab = nullptr;
							m_bGrab = false;
							m_bGravity = true;
							m_fGravityDeltaSum = 0;
							m_bJump = false;
							m_fJumpDeltaSum = 0;


							if (m_fPendStartX < m_tInfo.fX)
							{
								JumpStart(5.f, 45.f);
							}
							else
							{
								JumpStart(5.f, 135.f);
							}
						}
					}
				}
			}
			else if (pMouse->Get_Last_Key() == VK_RBUTTON)
			{
				if (m_bMonsterExc)
				{
					m_bMonsterExc = false;
					m_bGravity = true;
					m_fGravityDeltaSum = 0;


					auto pltBomb = dynamic_cast<CObjMonsterFloatingBomb*>(m_pTarget);
					if (pltBomb != nullptr)
					{
						
						/*auto w = ptCurr.x - m_tInfo.fX  ;
						auto h = ptCurr.y - m_tInfo.fY ;*/
						auto w = (float)ptCurr.x - (m_tInfo.fX + iScrollX);
						auto h = (float)ptCurr.y - (m_tInfo.fY + iScrollY);
						auto rad = atan2f(h, w);
						pltBomb->Excuted(this, rad);

						auto ang = rad * 180.f / PI;
						auto ang2 = ang * -1;
						
						JumpStart(30.f, ang2);
					}

					m_pTarget = nullptr;
				}
			}
		
	}
	
}

void CObjPlayer::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

//TCHAR* CObjPlayer::Dbg_Text()
//{
//	TCHAR szText[256]{};
//
//	const INFO* info = this->Get_Info();
//
//	
//
//	swprintf_s(szText, _T("m_fPendCurr: %f"), m_fPendCurr);
//
//	TCHAR* pText = new TCHAR[lstrlen(szText) + 1];
//	lstrcpy(pText, szText);
//	
//	return pText;
//}

void CObjPlayer::ParabolaNoGravityEquation(float fVZero, float fAngle, float fDeltaSum, float* fDstX, float* fDstY)
{
	*fDstX = fVZero * cosf(fAngle * PI / 180.f) * fDeltaSum;
	*fDstY = fVZero * sinf(fAngle * PI / 180.f) * fDeltaSum;
}