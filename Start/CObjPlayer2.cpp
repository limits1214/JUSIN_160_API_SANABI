#include "pch.h"
#include "CObjPlayer2.h"
#include "CTimeMgr.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CObjCollisionRect.h"
#include "CCollisionMgr.h"
#include "CScrollMgr.h"
#include "CObjPlayer2SNBSprite.h"
#include "CObjPlayer2SNBARMSprite.h"
#include "CObjMgr.h"
#include "CObjMouse.h"
#include "CObjPlayer2Grab.h"

CObjPlayer2::CObjPlayer2()
{
	Set_DbgName(_T("CObjPlayer2"));
	ZeroMemory(&m_tHookLine, sizeof(LINE));
}

CObjPlayer2::~CObjPlayer2()
{
	Release();
}

void CObjPlayer2::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 4.f;


	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_bGravity = true;
	m_fGravityDeltaSum = 0;

	m_bJump = true;
	m_fJumpAngle = 90.f;
	m_fJumpVelocity = 0.f;
	m_fJumpDeltaSum = 0;

	m_fPendDeltaSum = 0;

	m_eAniStateSNB = AST_RIGHT_SNB_IDLE_START;

	m_bLeftWallClimb = false;
	m_bRightWallClimb = false;
	m_bWallTop = false;
	m_bWallDown = false;

	m_pGrab = nullptr;

	m_bGrabbing = false;

	m_fHookMaxLength = 400.f;
	m_fHookMinLength = 200.f;
	m_bGrabLoad = false;
	m_bCeilStick = false;

	CObjPlayer2SNBSprite* pSNB = new CObjPlayer2SNBSprite;
	pSNB->Initialize();
	pSNB->Set_Pos(-5, -10);
	pSNB->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pSNB);


	//CObjPlayer2SNBARMSprite* pSNBARM = new CObjPlayer2SNBARMSprite;
	//pSNBARM->Initialize();
	//pSNBARM->Set_Pos(0, 0);
	//pSNBARM->Set_Parent(this);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pSNBARM);

	m_tBeforeInfo = m_tInfo;
}

int CObjPlayer2::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	DeltaUpdate();
	Apply_Gravity();
	Apply_Jump();

	Key_Input();

	/*if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
	{
		
	}*/

	// 최소길이 보다 길어지면 제거 
	if (m_pGrab != nullptr)
	{
		CObjPlayer2Grab* pGrab = dynamic_cast<CObjPlayer2Grab*>(m_pGrab);
		if (pGrab != nullptr)
		{
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			float grabX = pGrab->Get_Info()->fX;
			float grabY = pGrab->Get_Info()->fY;
			float width = grabX - m_tInfo.fX;
			float height = grabY - m_tInfo.fY;


			if (sqrtf(width * width + height * height) > m_fHookMaxLength)
			{
				m_pGrab->Set_Dead();
				m_pGrab = nullptr;
				m_bGrabbing = false;
			}
		}
	}

	if (m_bGrabLoad)
	{
		GrabLoad();
	}

	
	if (!m_bGrabLoad && !m_bCeilStick &&  m_bGrabbing)
	{
		if (m_pGrab != nullptr)
		{

			m_fGravityDeltaSum = 0;
			m_fJumpDeltaSum = 0;

			float w = sqrtf(/*GRAVITY*/ 500 / m_fPendLength);
			float l = m_fPendLength;

			auto ang0 = m_fPendRad;

			auto dbgAng = ang0 * 180.f / PI;

			//cout << "dbgAng0: " << dbgAng << endl;

			float tar = ang0 * cosf(w * (m_fPendDeltaSum)+0.f);

			//cout << "dbgTar: " << (tar * 180.f / PI) << endl;

			m_fPendCurr = tar;

			m_tInfo.fX = m_fPendStartX + sinf(tar) * l;
			m_tInfo.fY = m_fPendStartY + cosf(tar) * l;
		}
	}

	if (m_bWallTop)
	{
		m_bWallTop = false;
		m_fJumpAngle = 90.f;
		m_fJumpVelocity = 3.f;

		m_bJump = true;
		m_fJumpDeltaSum = 10;
		m_bGravity = true;
		m_fGravityDeltaSum = 0;
		Apply_Jump();

		m_bLeftWallClimb = false;
		m_bRightWallClimb = false;
	}

	if (m_bWallDown)
	{
		m_bWallDown = false;
		m_fJumpAngle = 270.f;
		m_fJumpVelocity = 3.f;
		
		m_bJump = true;
		m_fJumpDeltaSum = 0;
		m_bGravity = true;
		m_fGravityDeltaSum = 0;
		Apply_Jump();

		m_bLeftWallClimb = false;
		m_bRightWallClimb = false;
	}
 	 
	//낮아지고 있는 상태
	if ((int)m_tInfo.fY > (int)m_tBeforeInfo.fY) 
	{
		// 벽에 붙은 상태가 아니라면 체크
		if (!(m_bLeftWallClimb || m_bRightWallClimb))
		{
			if (m_eLastLRDir == DIR_LEFT)
			{

				m_eAniStateSNB = AST_LEFT_SNB_FALLSTART_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_FALLSTART_START;
			}
		}
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CObjPlayer2::Late_Update()
{
	Offset();
	m_tBeforeInfo = m_tInfo;

	// 첫번째는 충돌처리를위한 업데이트
	// 두번째는 화면 맞추기 위한 업데이트
	__super::Update_Rect();
}

void CObjPlayer2::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);



	if (m_bGrabbing)
	{
		// 임시
		if (OBJ_END != CObjMgr::Get_Instance()->Get_ObjID_By_Obj(m_pGrab))
		{
			if (m_pGrab != nullptr)
			{
				CObjPlayer2Grab* pGrab = dynamic_cast<CObjPlayer2Grab*>(m_pGrab);
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

void CObjPlayer2::Release()
{
}

void CObjPlayer2::On_Collision(CObj* pObj, COLLISIONID eCollID, void* etc)
{
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
				// 플레이어가 바닥에 닿은 경우 밀어준다.
				Move(90.f, fDistance);

				// 중력 델타를 0으로 변경
				m_bGravity = true;
				m_fGravityDeltaSum = 0;

				// 점프 다시 뛰지 않도록
				m_bJump = false;
				m_fJumpDeltaSum = 0;

				m_bFall = false;
				
				 
 				if (!m_bGround)  
				{
					m_bGround = true;
					if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
					{
						m_eAniStateSNB = AST_RIGHT_SNB_LAND2RUN_START;
					}
					else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
					{
						m_eAniStateSNB = AST_LEFT_SNB_LAND2RUN_START;
					}
					else
					{
						if (m_eLastLRDir == DIR_LEFT)
						{
							m_eAniStateSNB = AST_LEFT_SNB_LANDING_START;
						}
						else
						{
							m_eAniStateSNB = AST_RIGHT_SNB_LANDING_START;
						}
					}
				}

				
			}
			break;
			case DIR_DOWN:
			{
				// 플레이어가 위에 닿은 경우 밀어준다.
				Move(270.f, fDistance);
			}
			break;
			case DIR_LEFT:
			{
				// 플레이어가 왼쪽에 닿은 경우밀어준다.
				Move(180.f, fDistance);

				// 벽탈수 있는거면
				if (pRect->Get_Option() == ERI_CLIMABLE)
				{
					// 충돌 Init
					if (!m_bLeftWallClimb)
					{
						// 벽에 붙은상태에서 키입력이 들어오면
						if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
						{
							m_bLeftWallClimb = true;

							m_bGravity = false;
							m_bJump = false;

							m_eAniStateSNB = AST_RIGHT_SNB_WALL_SLIDE_START_START;
						}
					}

					// 충돌 업데이트
					if (m_bLeftWallClimb)
					{
						m_bGravity = false;
						m_bJump = false;

						// 벽의 위 또는 아래에 도착하면 탈출처리 필요
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
				// 플레이어가 오른쪽에 닿은 경우 밀어준다.
				Move(0.f, fDistance);

				// 벽탈수 있는거면
				if (pRect->Get_Option() == ERI_CLIMABLE)
				{
					// 충돌 Init
					if (!m_bRightWallClimb)
					{
						// 벽에 붙은상태에서 키입력이 들어오면
						if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
						{
							m_bRightWallClimb = true;
							m_bGravity = false;
							m_bJump = false;

							m_eAniStateSNB = AST_LEFT_SNB_WALL_SLIDE_START_START;
						}
					}

					// 충돌 업데이트
					if (m_bRightWallClimb)
					{
						m_bGravity = false;
						m_bJump = false;

						// 벽의 위 또는 아래에 도착하면 탈출처리 필요
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
	}
}

void CObjPlayer2::On_Mouse_Pos(CObj* pObj)
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

void CObjPlayer2::On_Mouse_Key_Down(CObj* pObj)
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
					m_bGrabbing = false;
					m_pGrab = nullptr;
				}
			}
			CObjPlayer2Grab* pGrab = new CObjPlayer2Grab;
			pGrab->Initialize();
			pGrab->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			pGrab->Set_Angle(m_fHookAngle);
			pGrab->Set_Target(this);
			CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pGrab);
			m_pGrab = pGrab;
		}
	}
}

void CObjPlayer2::On_Mouse_Key_Up(CObj* pObj)
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
			
			if (m_pGrab != nullptr)
			{
				if (m_bCeilStick)
				{
					if (m_pGrab->Get_Ceiling())
					{
						return;
					}
				}
				m_pGrab->Set_Dead();
				m_pGrab = nullptr;
				m_bGrabbing = false;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;
				m_bJump = false;
				m_fJumpDeltaSum = 0;


				// 끝단 점프
				if (m_fPendStartX < m_tInfo.fX)
				{
					//m_fJumpAngle = 45.f;
					//m_fJumpVelocity = 5.f;
						
					//m_bJump = true;
					//m_bGravity = true;
					//m_fGravityDeltaSum = 0;
					//Apply_Jump();

					//m_bLeftWallClimb = false;
					//m_bRightWallClimb = false;
				}
				else
				{
					//m_fJumpAngle = 135.f;
					//m_fJumpVelocity = 5.f;
						
					//m_bJump = true;
					//m_bGravity = true;
					//m_fGravityDeltaSum = 0;
					//Apply_Jump();

					//m_bLeftWallClimb = false;
					//m_bRightWallClimb = false;
				}
			}
			
		}
		else if (pMouse->Get_Last_Key() == VK_RBUTTON)
		{
			//if (m_bMonsterExc)
			//{
			//	m_bMonsterExc = false;
			//	m_bGravity = true;
			//	m_fGravityDeltaSum = 0;


			//	auto pltBomb = dynamic_cast<CObjMonsterFloatingBomb*>(m_pTarget);
			//	if (pltBomb != nullptr)
			//	{

			//		/*auto w = ptCurr.x - m_tInfo.fX  ;
			//		auto h = ptCurr.y - m_tInfo.fY ;*/
			//		auto w = (float)ptCurr.x - (m_tInfo.fX + iScrollX);
			//		auto h = (float)ptCurr.y - (m_tInfo.fY + iScrollY);
			//		auto rad = atan2f(h, w);
			//		pltBomb->Excuted(this, rad);

			//		auto ang = rad * 180.f / PI;
			//		auto ang2 = ang * -1;

			//		JumpStart(30.f, ang2);
			//	}

			//	m_pTarget = nullptr;
			//}
		}

	}
}

void CObjPlayer2::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CObjPlayer2::Key_Input()
{
	bool bKeyDownA = CKeyMgr::Get_Instance()->Key_Down('A');
	bool bKeyPressingA = CKeyMgr::Get_Instance()->Key_Pressing('A');
	bool bKeyUpA = CKeyMgr::Get_Instance()->Key_Up('A');

	bool bKeyDownD = CKeyMgr::Get_Instance()->Key_Down('D');
	bool bKeyPressingD = CKeyMgr::Get_Instance()->Key_Pressing('D');
	bool bKeyUpD = CKeyMgr::Get_Instance()->Key_Up('D');

	bool bKeyDownW = CKeyMgr::Get_Instance()->Key_Down('W');
	bool bKeyPressingW = CKeyMgr::Get_Instance()->Key_Pressing('W');
	bool bKeyUpW = CKeyMgr::Get_Instance()->Key_Up('W');

	bool bKeyDownS = CKeyMgr::Get_Instance()->Key_Down('S');
	bool bKeyPressingS = CKeyMgr::Get_Instance()->Key_Pressing('S');
	bool bKeyUpS = CKeyMgr::Get_Instance()->Key_Up('S');

	bool bKeyDownSpace = CKeyMgr::Get_Instance()->Key_Down(VK_SPACE);
	bool bKeyPressingSpace = CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE);
	bool bKeyUpSpace = CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE);

	if (
		m_bLeftWallClimb
		||
		m_bRightWallClimb
		)
	{
		if (bKeyDownW)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_CLIMBUP_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_CLIMBUP_START;
			}
		}
		else if (bKeyDownS)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_CLIMBDOWN_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_CLIMBDOWN_START;
			}
		}

		if (bKeyPressingW)
		{
			Move(90.f, m_fSpeed);
		}
		else if (bKeyPressingS)
		{
			Move(270.f, m_fSpeed);
		}

		if (bKeyUpW)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_SLIDING_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_SLIDING_START;
			}
		}
		else if (bKeyUpS)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_SLIDING_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_SLIDING_START;
			}
		}

		if (bKeyDownSpace)
		{
			if (!m_bJump)
			{
				m_bJump = true;
				m_fJumpDeltaSum = 70;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;

				if (m_bLeftWallClimb)
				{
					m_fJumpAngle = 110.f;
				}
				else
				{
					m_fJumpAngle = 70.f;
				}

				
				m_fJumpVelocity = 2.5f;
				Apply_Jump();
				m_bGround = false;
				if (m_eLastLRDir == DIR_LEFT)
				{
					m_eAniStateSNB = AST_LEFT_SNB_JUMPING_START;
				}
				else
				{
					m_eAniStateSNB = AST_RIGHT_SNB_JUMPING_START;
				}

				m_bLeftWallClimb = false;
				m_bRightWallClimb = false;

			}
		}
	}
	
	else if (m_bCeilStick)
	{
		

		
		
	}

	else if (m_bGrabbing)
	{
		// 오른쪽
		if (bKeyPressingA)
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
		else if (bKeyPressingD)
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
	else
	{
		//좌
		if (bKeyDownA)
		{
			cout << "bKeyDownA" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_LEFT_SNB_RUNSTART_START;
			}

		}
		//우
		else if (bKeyDownD)
		{
			cout << "bKeyDownD" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_RIGHT_SNB_RUNSTART_START;
			}
		}

		//좌
		if (bKeyPressingA)
		{
			Move(180.f, m_fSpeed);
			m_eLastLRDir = DIR_LEFT;

		}
		//우
		else if (bKeyPressingD)
		{
			Move(0.f, m_fSpeed);
			m_eLastLRDir = DIR_RIGHT;
		}

		//좌
		if (bKeyUpA)
		{
			cout << "bKeyUpA" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_LEFT_SNB_RUNSTOP_START;
			}
		}
		//우
		else if (bKeyUpD)
		{
			cout << "bKeyUpD" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_RIGHT_SNB_RUNSTOP_START;
			}
		}



		if (bKeyDownSpace)
		{
			if (!m_bJump)
			{
				m_bJump = true;
				m_fJumpDeltaSum = 70;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;
				m_fJumpAngle = 90.f;
				m_fJumpVelocity = 2.5f;
				Apply_Jump();
				m_bGround = false;
				if (m_eLastLRDir == DIR_LEFT)
				{
					m_eAniStateSNB = AST_LEFT_SNB_JUMPING_START;
				}
				else
				{
					m_eAniStateSNB = AST_RIGHT_SNB_JUMPING_START;
				}

			}
		}
	}
	

	

}

void CObjPlayer2::Grab(CObjPlayer2Grab* pObj)
{
	if (pObj->Get_CollisionOption() != ERI_CLIMABLE)
	{
		pObj->Set_Dead();
		return;
	}

	if (pObj->Get_Dead())
	{
		return;
	}



	//m_eCurState = FSI_SNB_R_SWING;
	m_bGrabbing = true;
	auto grabInfo = pObj->Get_Info();

	auto width = m_tInfo.fX - grabInfo->fX;
	auto height = m_tInfo.fY - grabInfo->fY;

	auto l = sqrtf(width * width + height * height);
	m_fPendLength = l;
	m_fPendDeltaSum = 0;
	m_fPendRad = atan2f(width, height);
	m_fPendStartX = grabInfo->fX;
	m_fPendStartY = grabInfo->fY;
}

void CObjPlayer2::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;
	m_dwTime = dwNowTime;

	m_fGravityDeltaSum += dwDelta;
	m_fJumpDeltaSum += dwDelta;
	m_fPendDeltaSum += dwDelta;
}

void CObjPlayer2::Apply_Gravity()
{
	if (m_bGravity)
	{
		float fGravityDeltaMax = 1.5f;
		if (m_fGravityDeltaSum > fGravityDeltaMax)
		{
			m_fGravityDeltaSum = fGravityDeltaMax;
		}

		float fTmpG = GRAVITY * (m_fGravityDeltaSum * m_fGravityDeltaSum) * 0.5f;
		float fScaledTmpY = fTmpG * 1.5f;
		
		Move(270.f, fScaledTmpY);
	}
}

void CObjPlayer2::Apply_Jump()
{
	if (m_bJump)
	{
		float fJumpDeltaMax = 1.5f;
		if (m_fJumpDeltaSum > fJumpDeltaMax)
		{
			m_fJumpDeltaSum = fJumpDeltaMax;
		}
		Move(m_fJumpAngle, m_fJumpVelocity * m_fJumpDeltaSum);
	}
}

void CObjPlayer2::Apply_Pend()
{
}


void CObjPlayer2::Move(float fAngle, float fLength)
{
	m_tInfo.fX += cosf(fAngle * PI / 180.f) * fLength;
	m_tInfo.fY -= sinf(fAngle * PI / 180.f) * fLength;
}

void CObjPlayer2::Offset()
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
void CObjPlayer2::GrabLoad()
{
	
	if (m_pGrab != nullptr)
	{
		float width = m_pGrab->Get_Info()->fX - m_tInfo.fX;
		float height = m_pGrab->Get_Info()->fY - m_tInfo.fY;
		float fRad = atan2f(height, width);
		float x = cosf(fRad) * 30.f;
 		float y = sinf(fRad) * 30.f;
		m_tInfo.fX += x;
		m_tInfo.fY += y;
		//cout << "1" << endl;
		cout << x << endl;
		cout << y << endl;
		RECT rc;
		if (IntersectRect(&rc, m_pGrab->Get_Rect(), this->Get_Rect()))
		{
			if (m_pGrab->Get_Ceiling())
			{
				m_bGrabLoad = false;
				m_bCeilStick = true;

				m_bGravity = false;

				// 들어가지 않게 체인 아래 위치시키기

				m_tInfo.fX = m_pGrab->Get_Info()->fX;
				m_tInfo.fY = (m_pGrab->Get_Info()->fY + m_pGrab->Get_Info()->fCY * 0.5f) + (m_tInfo.fCY * 0.5f);
			}
			else if (m_pGrab->Get_CollisionLeft())
			{
				m_bGrabbing = false;
				m_bGrabLoad = false;
				m_bLeftWallClimb = true;
			}
			else if (m_pGrab->Get_CollisionRight())
			{
				m_bGrabbing = false;
				m_bGrabLoad = false;
				m_bRightWallClimb = true;

			}
			else {
				m_bGrabbing = false;
				m_bGrabLoad = false;

				m_bJump = false;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;


			}
		}
			
	}
	
}