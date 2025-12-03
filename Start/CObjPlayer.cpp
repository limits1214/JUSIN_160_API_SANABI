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

	m_fHookMaxLength = 200.f;

	//m_tInfo.fCX = 112.f;
	//m_tInfo.fCY = 104.f;

	m_bGrab = false;
	m_bGrabLoad = false;
	m_bGrabCeilingMove = false;

	m_fSpeed = 4.f;

	auto a = CBmpMgr::Get_Instance();

	//m_eFrameKey = FKI_SNB;
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_SHEET.bmp", FrameKeyId_To_Text2(m_eFrameKey));
	
	//m_eFrameKey = FKI_Spr_SNB_SHEET_2;
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_Sheet2.bmp", FrameKeyId_To_Text2(m_eFrameKey));
	//m_tFrame.dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	//m_eCurState = FSI_SNB_R_IDLE;

	m_bUseMainScroll = true;

	

}

int CObjPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	

	DeltaUpdate();


	//m_eCurState = FSI_SNB_R_IDLE;
	Key_Input();

	if (m_eCurState == FSI_SNB_R_RUNSTART && m_tFrame.iStart == 1)
	{
		m_eCurState = FSI_SNB_R_RUNNING;
	}
	else if (m_eCurState == FSI_SNB_R_RUNSTOP && m_tFrame.iStart == 5)
	{
		m_eCurState = FSI_SNB_R_IDLE;
	}


	Move_Frame();

	if (m_bGrabCeilingMove)
	{
		//m_bGravity = false;
		//m_bJump = false;
		//m_bGrab = false;
	}

	if (m_bGrabLoad)
	{
		GrabLoad();
	}

	if (!m_bGrabLoad && !m_bGrabCeilingMove && m_bGrab)
	{
		auto pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
		if (pGrab != nullptr)
		{
			float w = sqrtf(/*GRAVITY*/ 500 / m_fPendLength);
			float l = m_fPendLength;

			auto ang0 = m_fPendRad;

			auto dbgAng = ang0 * 180 / PI;


			float tar = ang0 * cosf(w * (m_fPendDeltaSum )+0.f);

			m_tInfo.fX = m_fPendStartX + sinf(tar) * l;
			m_tInfo.fY = m_fPendStartY + cosf(tar) * l ; //+ (m_tInfo.fCY * 0.5f)
		}
	}

	if (m_bWallTop)
	{
		m_bWallTop = false;
		JumpStart(27.f, 90.f);
		m_bJumpJustPressed = false;
	}


	return OBJ_NOEVENT;
}

void CObjPlayer::Late_Update()
{
	Offset();
	Motion_Change();

	// 입력받고 그릴지 아니면 그리고 입력받을지...
	__super::Update_Rect();
}

void CObjPlayer::Render(HDC hDC)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(FrameKeyId_To_Text2(m_eFrameKey));
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BmpRender(
		hDC,
		m_tRect.left , m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,

		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,(int) m_tInfo.fCY
		);


	if (!m_bGrab)
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
	if (eCollID == COLL_RECT_EX && pRect != nullptr && pRectExCollEtc != nullptr)
	{
		COLL_ETC_RECT_EX rectExCollEtc = *pRectExCollEtc;
		float fDistance = rectExCollEtc.fDistance;

		
		
		switch (rectExCollEtc.eDir)
		{
		case DIR_UP:
		{
			Move(DIR_UP, -fDistance);
			if (m_bJumpJustPressed)
			{
				m_bJumpJustPressed = false;
				return;
			}
			

			

			// on Ground;
			m_bJump = false;
			m_fGravityDeltaSum = 0;
			m_bGravity = true;
		}
			break;
		case DIR_DOWN:
		{
			int x = 0;
			Move(DIR_DOWN, fDistance);
		}
			break;
		case DIR_LEFT:
		{
			/*if (fDistance == 0)
			{
				return;
			}*/
			Move(DIR_LEFT, -fDistance);
			if (pRect->Get_Option() == ERI_CLIMABLE)
			{// 벽 왼쪽에서 벽타기
				if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
				{
					m_bLWallClimb = true;
				}
				
			
				

				if (m_bLWallClimb)
				{
					m_bJump = false;
					m_fJumpDeltaSum = 0;
					m_bGravity = false;
					m_fGravityDeltaSum = 0;

					float fRectY = (pRect->Get_Info()->fY - pRect->Get_Info()->fCY * 0.5f) + (m_tInfo.fCY * 0.6f);
					if (m_tInfo.fY <= fRectY)
					{
						m_bWallTop = true;
					}
				}
			}
			
		}
			break;
		case DIR_RIGHT:
		{
			/*if (fDistance == 0)
			{
				return;
			}*/
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
					m_bJump = false;
					m_fJumpDeltaSum = 0;
					m_bGravity = false;
					m_fGravityDeltaSum = 0;


					float fRectY = (pRect->Get_Info()->fY - pRect->Get_Info()->fCY * 0.5f) + (m_tInfo.fCY * 0.6f);
					if (m_tInfo.fY <= fRectY)
					{
						m_bWallTop = true;
					}

					
				}

			}

			
		}
			break;
		}
	}
}


void CObjPlayer::Grab(CObj* pObj)
{
	if (!m_bGrab)
	{
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

	m_eCurState = FSI_SNB_R_JUMP;

	m_bJump = true;
	m_fJumpDeltaSum = 0;

	m_bGravity = true;
	m_fGravityDeltaSum = 0;

	m_fJumpVZero = fVZero;
	m_fJumpAngle = fAngle;

	m_bLWallClimb = false;
	m_bRWallClimb = false;
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
					else {
						m_bGrab = false;
						m_bGrabLoad = false;
					}
				}
			}
		}
	}
		//m_bGrabLoad = false;
		//m_bGrab = false;
		//m_bGrabCeilingMove = true;

		//m_bGravity = false;
		//m_bJump = false;
		//m_bGrab = false;
	
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

	bool bKeyDownLShift = CKeyMgr::Get_Instance()->Key_Pressing('Q');


	if (bKeyDownLShift)
	{
		m_fPendRad += 1.f * PI / 180.f;
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

	if (m_bGrab)
	{
		// 오른쪽
		if (bPressingA)
		{
			//m_fPendRad -= 0.01;
		}
		//  왼쪽
		else if (bPressingD)
		{
			//m_fPendRad += 0.01;

		}

		if (bKeyDownSpace)
		{
			// 그랩 당기기
			m_bGrabLoad = true;
			//if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
			//{
			//	if (m_pGrab != nullptr)
			//	{
			//		CObjGrab* pGrab = dynamic_cast<CObjGrab*>(m_pGrab);
			//		if (pGrab != nullptr)
			//		{
			//			m_bGrabLoad = true;
			//			float fGrabX = pGrab->Get_Info()->fX;
			//			float fGrabY = pGrab->Get_Info()->fY;
			//			m_fGrabLoadX = fGrabX;
			//			m_fGrabLoadY = fGrabY;
			//			m_tGrabRect = *pGrab->Get_Rect();
			//			int x = 0;
			//		}
			//	}
			//}
			

		}
	}
	else
	{
		if (bKeyDownA)
		{
			m_eCurState = FSI_SNB_R_RUNSTART;
			m_fMoveLeftDeltaSum = 0;
		}

		if (bKeyDownD)
		{
			m_eCurState = FSI_SNB_R_RUNSTART;
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
			}
			else if (m_bRWallClimb)
			{
				JumpStart(17.f, 70.f);
			}
			else
			{
				JumpStart(27.f, 90.f);
			}

		}
		if (bKeyPressingW)
		{
			if (m_bLWallClimb || m_bRWallClimb)
			{
				Move(DIR_UP, -m_fSpeed);
			}

		}

		if (bKeyPressingS)
		{
			if (m_bLWallClimb || m_bRWallClimb)
			{
				Move(DIR_DOWN, m_fSpeed);
			}

		}

		// 오른쪽 이동
		if (bPressingA)
		{
			int x = 0;
			if (m_bLWallClimb)
			{
				// todo: timer
				//JumpStart(30.f, 100.f);
				//Move(DIR_LEFT, -m_fSpeed);
			}
			else
			{
				Move(DIR_LEFT, -m_fSpeed);
			}
		}
		//  왼쪽 이동
		else if (bPressingD)
		{
			if (m_bRWallClimb)
			{
				// todo: timer
				//JumpStart(10.f, 75.f);
				//Move(DIR_RIGHT, m_fSpeed);
			}
			else
			{
				Move(DIR_RIGHT, m_fSpeed);
			}


		}

		if (bKeyUpA)
		{
			m_eCurState = FSI_SNB_R_RUNSTOP;
		}

		if (bKeyUpD)
		{
			m_eCurState = FSI_SNB_R_RUNSTOP;
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
	//dwDelta = 0.2;
	//dwDelta /= 1000.f;
	m_dwTime = dwNowTime;

	//dwDelta *= 3.f;
	//m_dwDeltaSum += dwDelta;
	m_fGravityDeltaSum += dwDelta;
	m_fJumpDeltaSum += dwDelta;
	m_fMoveLeftDeltaSum += dwDelta;
	m_fMoveRightDeltaSum += dwDelta;
	m_fPendDeltaSum += dwDelta;



	DWORD  dwGravityDeltaMax = 1000;
	if (m_fGravityDeltaSum > dwGravityDeltaMax)
	{
		//m_dwGravityDeltaSum = dwGravityDeltaMax;
	}
	if (m_bGrab)
	{
		return ;
	}
	float tempG = 0;
	if (true && m_bGravity)
	{
		float fTmpG = GRAVITY * (m_fGravityDeltaSum * m_fGravityDeltaSum) * 0.5f;
		float fScaledTmpY = fTmpG * 10;
		//float fMaxGravity = 100;
		//if (fTmpG > fMaxGravity)
		//{
		//	fScaledTmpY = fMaxGravity;
		//}
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
 		DWORD  dwJumpDeltaMax = 1200;
		if (m_fJumpDeltaSum > dwJumpDeltaMax)
		{
			//m_dwJumpDeltaSum = dwJumpDeltaMax;
		}


		float fDstX, fDstY;
		ParabolaNoGravityEquation(m_fJumpVZero , m_fJumpAngle, m_fJumpDeltaSum, &fDstX, &fDstY);
		Move(DIR_LEFT, fDstX);
		Move(DIR_UP, -fDstY);


		// 최대점프
		if (fDstY - tempG < 0)
		{
			int x = 0;
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
		POINT ptCurr = pMouse->Get_Pt_Curr();
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		//float fParentX = m_pParent->Get_Info()->fX + iScrollX;
		//float fParentY = m_pParent->Get_Info()->fY + iScrollY;

		

		if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
		{
			if (m_pGrab != nullptr)
			{
				return;
				m_pGrab->Set_Dead();
				m_bGrab = false;
			}
		}

		CObjGrab* pGrab = new CObjGrab;
		pGrab->Initialize();
		/*pGrab->Set_Pos(fParentX, fParentY);*/
		pGrab->Set_Pos(m_tInfo.fX , m_tInfo.fY);
		pGrab->Set_Angle(m_fHookAngle);
		pGrab->Set_Target(this);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pGrab);
		m_pGrab = pGrab;

	}
}

void CObjPlayer::On_Mouse_Key_Up(CObj* pMouse)
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
			}
			
		}
	}
}

void CObjPlayer::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CObjPlayer::ParabolaNoGravityEquation(float fVZero, float fAngle, float fDeltaSum, float* fDstX, float* fDstY)
{
	*fDstX = fVZero * cosf(fAngle * PI / 180.f) * fDeltaSum;
	*fDstY = fVZero * sinf(fAngle * PI / 180.f) * fDeltaSum;
}