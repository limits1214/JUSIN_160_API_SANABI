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
#include "CKeyMgr2.h"

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
	m_eAniStateSNBARM = AST_RIGHT_ARM_IDLE_START;

	m_bLeftWallClimb = false;
	m_bRightWallClimb = false;
	m_bWallTopEscape = false;
	m_bWallDownEscape = false;
	m_bWallLeftEscape = false;
	m_bWallRightEscape = false;

	m_pGrab = nullptr;

	m_bGrabbing = false;
	m_bGrabHookResize = false;


	m_fHookGuideLength = 400.f;
	m_fHookMaxLength = 200.f;
	m_fHookMinLength = 100.f;
	m_bGrabLoad = false;
	m_bCeilStick = false;

	m_bExc = false;

	m_bGround = false;

	CObjPlayer2SNBSprite* pSNB = new CObjPlayer2SNBSprite;
	pSNB->Initialize();
	pSNB->Set_Pos(-5, -10);
	pSNB->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pSNB);


	CObjPlayer2SNBARMSprite* pSNBARM = new CObjPlayer2SNBARMSprite;
	pSNBARM->Initialize();
	pSNBARM->Set_Pos(-5, -10);
	pSNBARM->Set_Parent(this);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pSNBARM);

	m_tBeforeInfo = m_tInfo;
}

int CObjPlayer2::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	DeltaUpdate();
	Apply_Jump();
	Apply_Gravity();

	Key_Input();

	// 최소길이 보다 길어지면 제거 
	if (m_pGrab != nullptr)
	{
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		float grabX = m_pGrab->Get_Info()->fX;
		float grabY = m_pGrab->Get_Info()->fY;
		float width = grabX - m_tInfo.fX;
		float height = grabY - m_tInfo.fY;


		if (sqrtf(width * width + height * height) > m_fHookGuideLength)
		{
			m_pGrab->Set_Dead_Cascade();
			m_pGrab = nullptr;
			m_bGrabbing = false;
		}
	}

	if (m_bGrabLoad)
	{
		GrabLoad();
	}

	if (m_bGrabHookResize)
	{
		GrabHookResize();
	}

	
	if (!m_bGrabLoad && !m_bCeilStick && !m_bGrabHookResize &&   m_bGrabbing)
	{
		if (false && m_pGrab != nullptr)
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

		if ( m_pGrab != nullptr)
		{
			float newL = m_fPendLength + 20;
			float newL2 = m_fPendLength - 10;
			float grabX = m_pGrab->Get_Info()->fX;
			float grabY = m_pGrab->Get_Info()->fY;

			float playerGrabWidth = m_tInfo.fX - grabX;
			float playerGrabHeight = m_tInfo.fY - grabY;
			float playerGrabLength = sqrtf(playerGrabWidth * playerGrabWidth + playerGrabHeight * playerGrabHeight);

			if (true || m_tInfo.fY > grabY)
			{
				if (playerGrabLength > newL2)
				{
					m_fGravityDeltaSum = 0;
					m_fJumpDeltaSum = 0;

					//m_bGravity = false;
					//m_bJump = false;

					float w = sqrtf(/*GRAVITY*/ 500 / m_fPendLength);
					float l = m_fPendLength;

					auto ang0 = m_fPendRad;

					auto dbgAng = ang0 * 180.f / PI;

					//cout << "dbgAng0: " << dbgAng << endl;

					float tar = ang0 * cosf(w * (m_fPendDeltaSum)+0.f);

					cout << "dbgTar: " << (tar * 180.f / PI) << endl;

					m_fPendCurr = tar;

					m_tInfo.fX = grabX + sinf(tar) * l;
					m_tInfo.fY = grabY + cosf(tar) * l;
				}
				else
				{
					//m_bGravity = true;
					//m_fGravityDeltaSum = 0;
					//m_fJumpDeltaSum = 0;
				}
			}
			


		}
	}

	if (m_bWallTopEscape)
	{
		m_bWallTopEscape = false;

		JumpRoutine(90.f, 21.f);
		
	}
	else if (m_bWallDownEscape)
	{
		m_bWallDownEscape = false;
		
		JumpRoutine(270.f, 1.f);
	}
	else if (m_bWallLeftEscape)
	{

	}
	else if (m_bWallRightEscape)
	{

	}

	//낮아지고 있는 상태
	if ((int)m_tInfo.fY > (int)m_tBeforeInfo.fY) 
	{
		// 벽에 붙은 상태가 아니라면 체크
		if (!(m_bLeftWallClimb || m_bRightWallClimb))
		{
			if (m_eLastLRDir == DIR_LEFT)
			{

				//m_eAniStateSNB = AST_LEFT_SNB_FALLSTART_START;
			}
			else
			{
				//m_eAniStateSNB = AST_RIGHT_SNB_FALLSTART_START;
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
		if (m_pGrab != nullptr)
		{
			int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			float grabX = m_pGrab->Get_Info()->fX + iScrollX;
			float grabY = m_pGrab->Get_Info()->fY + iScrollY;

			MoveToEx(hDC, grabX, grabY, nullptr);
			LineTo(hDC, m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY);
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
					if (CKeyMgr2::Get_Instance()->Key_Pressing('D'))
					{
						m_eAniStateSNB = AST_RIGHT_SNB_LAND2RUN_START;
						m_eAniStateSNBARM = AST_RIGHT_ARM_LAND2RUN_START;
					}
					else if (CKeyMgr2::Get_Instance()->Key_Pressing('A'))
					{
						m_eAniStateSNB = AST_LEFT_SNB_LAND2RUN_START;
						m_eAniStateSNBARM = AST_LEFT_ARM_LAND2RUN_START;
					}
					else
					{
						if (m_eLastLRDir == DIR_LEFT)
						{
							m_eAniStateSNB = AST_LEFT_SNB_LANDING_START;
							m_eAniStateSNBARM = AST_LEFT_ARM_LANDING_START;
						}
						else
						{
							m_eAniStateSNB = AST_RIGHT_SNB_LANDING_START;
							m_eAniStateSNBARM = AST_RIGHT_ARM_LANDING_START;
						}
					}
				}

				if (m_bGrabbing)
				{
					if (m_pGrab != nullptr)
					{
						m_pGrab->Set_Dead_Cascade();
						m_pGrab = nullptr;
					}

					m_bGrabbing = false;

					m_bGravity = true;
					m_fGravityDeltaSum = 0;

					m_bJump = false;
					m_fJumpDeltaSum = 0;
				}

				
			}
			break;
			case DIR_DOWN:
			{
				// 플레이어가 위에 닿은 경우 밀어준다.
				Move(270.f, fDistance);

				if (m_bGrabbing)
				{
					//if (m_pGrab != nullptr)
					//{
					//	m_pGrab->Set_Dead_Cascade();
					//	m_pGrab = nullptr;
					//}


					//m_bGrabbing = false;

					//m_bGravity = true;
					//m_fGravityDeltaSum = 0;

					//m_bJump = false;
					//m_fJumpDeltaSum = 0;

					if (m_pGrab != nullptr)
					{
						auto width = m_tInfo.fX - m_pGrab->Get_Info()->fX;
						auto height = m_tInfo.fY - m_pGrab->Get_Info()->fY;

						// 진폭 세팅
						auto l = sqrtf(width * width + height * height);
						m_fPendLength = l;
						m_fPendDeltaSum = 0;
						m_fPendRad = atan2f(width, height);
						m_fPendStartX = m_pGrab->Get_Info()->fX;
						m_fPendStartY = m_pGrab->Get_Info()->fY;
					}
					
				}
			}
			break;
			case DIR_LEFT:
			{
				// 플레이어가 왼쪽에 닿은 경우밀어준다.
				Move(180.f, fDistance);


				if (m_bGrabbing)
				{
					if (m_pGrab != nullptr)
					{
						m_pGrab->Set_Dead_Cascade();
						m_pGrab = nullptr;
					}
					

					m_bGrabbing = false;

					m_bGravity = true;
					m_fGravityDeltaSum = 0;

					m_bJump = false;
					m_fJumpDeltaSum = 0;




					m_bLeftWallClimb = true;
				}

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
							m_fGravityDeltaSum = 0;
							m_bJump = false;
							m_fJumpDeltaSum = 0;

							m_eAniStateSNB = AST_RIGHT_SNB_WALL_SLIDE_START_START;
							m_eAniStateSNBARM = AST_RIGHT_ARM_WALL_SLIDE_START_START;
						}
					}

					// 충돌 업데이트
					if (m_bLeftWallClimb)
					{
						m_bGravity = false;
						m_fGravityDeltaSum = 0;
						m_bJump = false;
						m_fJumpDeltaSum = 0;

						// 벽의 위 또는 아래에 도착하면 탈출처리 필요
						float fRectY = (pRect->Get_Info()->fY - pRect->Get_Info()->fCY * 0.5f) + (m_tInfo.fCY * 0.0f);
						if (m_tInfo.fY <= fRectY)
						{
							m_bWallTopEscape = true;
						}

						float fRectYDown = (pRect->Get_Info()->fY + pRect->Get_Info()->fCY * 0.5f); /*+ (m_tInfo.fCY * 0.6f)*/
						if (m_tInfo.fY >= fRectYDown)
						{
							m_bWallDownEscape = true;
						}
					}
				}



			}
			break;
			case DIR_RIGHT:
			{
				// 플레이어가 오른쪽에 닿은 경우 밀어준다.
				Move(0.f, fDistance);


				if (m_bGrabbing)
				{
					if (m_pGrab != nullptr)
					{
						m_pGrab->Set_Dead_Cascade();
						m_pGrab = nullptr;
					}

					m_bGrabbing = false;

					m_bGravity = true;
					m_fGravityDeltaSum = 0;

					m_bJump = false;
					m_fJumpDeltaSum = 0;



					m_bRightWallClimb = true;
				}

				// 벽탈수 있는거면
				if (pRect->Get_Option() == ERI_CLIMABLE)
				{
					// 충돌 Init
					if (!m_bRightWallClimb)
					{
						// 벽에 붙은상태에서 키입력이 들어오면
						if (CKeyMgr2::Get_Instance()->Key_Pressing('A'))
						{
							m_bRightWallClimb = true;

							m_bGravity = false;
							m_fGravityDeltaSum = 0;
							m_bJump = false;
							m_fJumpDeltaSum = 0;

							m_eAniStateSNB = AST_LEFT_SNB_WALL_SLIDE_START_START;
							m_eAniStateSNBARM = AST_LEFT_ARM_WALL_SLIDE_START_START;
						}
					}

					// 충돌 업데이트
					if (m_bRightWallClimb)
					{
						m_bGravity = false;
						m_fGravityDeltaSum = 0;
						m_bJump = false;
						m_fJumpDeltaSum = 0;

						// 벽의 위 또는 아래에 도착하면 탈출처리 필요
						float fRectY = (pRect->Get_Info()->fY - pRect->Get_Info()->fCY * 0.5f) + (m_tInfo.fCY * 0.0f);
						if (m_tInfo.fY <= fRectY)
						{
							m_bWallTopEscape = true;
						}

						float fRectYDown = (pRect->Get_Info()->fY + pRect->Get_Info()->fCY * 0.5f); /*+ (m_tInfo.fCY * 0.6f)*/
						if (m_tInfo.fY >= fRectYDown)
						{
							m_bWallDownEscape = true;
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

		m_fHookRadian = atan2f(fHeight, fWidth);
		float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
		if (fDist > m_fHookGuideLength)
		{

			ptRight.fX = ptLeft.fX + cosf(m_fHookRadian) * m_fHookGuideLength;
			ptRight.fY = ptLeft.fY + sinf(m_fHookRadian) * m_fHookGuideLength;
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
			
			if (m_pGrab != nullptr)
			{
				m_pGrab->Set_Dead_Cascade();
				m_bGrabbing = false;
				m_pGrab = nullptr;
			}
			
			// 그랩쏘기
			// TODO: 현재상태에 따라 진폭 결정
			float ang = m_fHookRadian * 180.f / PI;


			// 발사시 그랩방향
			DIRECTION eGrabDir = DIR_RIGHT;
			if (ang < -45 && ang  >-135)
			{
				// TOP
				eGrabDir = DIR_UP;
			}
			else if (ang < -135 && ang  >-180 || ang < 180 && ang > 135)
			{
				//LEFT
				eGrabDir = DIR_LEFT;
			}
			else if (ang > 45 && ang < 135)
			{
				//BOTM
				eGrabDir = DIR_DOWN;
			}
			else
			{
				//right

			}
			
			CObjPlayer2Grab* pGrab = new CObjPlayer2Grab;
			pGrab->Initialize();
			pGrab->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			pGrab->Set_Radian(m_fHookRadian);
			pGrab->Set_Target(this);
			pGrab->Set_GrabDir(eGrabDir);
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
			// 그랩 풀고 제거
			if (m_pGrab != nullptr)
			{
				// 그랩 풀었는데 천장상태라면 그랩은 살려줘야한다.
				// 천장 내려올때 그랩을 죽인다
				if (m_bCeilStick)
				{
					return;
					//if (m_pGrab->Get_Ceiling())
					//{
					//	
					//}
				}
				m_bGrabLoad = false;

				m_pGrab->Set_Dead_Cascade();
				m_pGrab = nullptr;

				m_bGrabbing = false;

				m_bGravity = true;
				m_fGravityDeltaSum = 0;

				m_bJump = false;
				m_fJumpDeltaSum = 0;

				
				if (m_eLastLRDir == DIR_LEFT)
				{
					m_eAniStateSNB = AST_LEFT_SNB_SWINGJUMP_START;
					m_eAniStateSNBARM = AST_LEFT_ARM_SWINGJUMP_START;
				}
				else
				{
					m_eAniStateSNB = AST_RIGHT_SNB_SWINGJUMP_START;
					m_eAniStateSNBARM = AST_RIGHT_ARM_SWINGJUMP_START;
				}


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
	bool bKeyPressingA = CKeyMgr2::Get_Instance()->Key_Pressing('A');
	bool bKeyDownA = CKeyMgr2::Get_Instance()->Key_Down('A');
	bool bKeyUpA = CKeyMgr2::Get_Instance()->Key_Up('A');

	bool bKeyPressingD = CKeyMgr2::Get_Instance()->Key_Pressing('D');
	bool bKeyDownD = CKeyMgr2::Get_Instance()->Key_Down('D');
	bool bKeyUpD = CKeyMgr2::Get_Instance()->Key_Up('D');

	bool bKeyPressingW = CKeyMgr2::Get_Instance()->Key_Pressing('W');
	bool bKeyDownW = CKeyMgr2::Get_Instance()->Key_Down('W');
	bool bKeyUpW = CKeyMgr2::Get_Instance()->Key_Up('W');

	bool bKeyPressingS = CKeyMgr2::Get_Instance()->Key_Pressing('S');
	bool bKeyDownS = CKeyMgr2::Get_Instance()->Key_Down('S');
	bool bKeyUpS = CKeyMgr2::Get_Instance()->Key_Up('S');

	bool bKeyPressingSpace = CKeyMgr2::Get_Instance()->Key_Pressing(VK_SPACE);
	bool bKeyDownSpace = CKeyMgr2::Get_Instance()->Key_Down(VK_SPACE);
	bool bKeyUpSpace = CKeyMgr2::Get_Instance()->Key_Pressing(VK_SPACE);

	// 벽타기 경우
	if (m_bLeftWallClimb
		||
		m_bRightWallClimb)
	{
		if (bKeyDownW)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_CLIMBUP_START;
				m_eAniStateSNBARM = AST_LEFT_ARM_WALL_CLIMBUP_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_CLIMBUP_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_WALL_CLIMBUP_START;
			}
		}
		else if (bKeyDownS)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_CLIMBDOWN_START;
				m_eAniStateSNBARM = AST_LEFT_ARM_WALL_CLIMBDOWN_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_CLIMBDOWN_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_WALL_CLIMBDOWN_START;
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
				m_eAniStateSNBARM = AST_LEFT_ARM_WALL_SLIDING_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_SLIDING_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_WALL_SLIDING_START;
			}
		}
		else if (bKeyUpS)
		{
			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_WALL_SLIDING_START;
				m_eAniStateSNBARM = AST_LEFT_ARM_WALL_SLIDING_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_WALL_SLIDING_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_WALL_SLIDING_START;
			}
		}

		if (bKeyDownSpace)
		{
			if (!m_bJump)
			{
				//TODO: 벽 점프의 느낌이
				// 대각 포물선이아니라
				// 중력은 중력대로 받고
				// 그냥 왼쪽 오른쪽 대시 느낌임
				if (m_bLeftWallClimb)
				{
					JumpRoutine(100.f, 20.f);
				}
				else
				{
					JumpRoutine(80.f, 20.f);
				}
			}
		}
	}
	
	// 천장에 붙었을경우
	else if (m_bCeilStick)
	{
		//왼쪽 움직이기
		if (bKeyPressingA)
		{
			Move(180.f, m_fSpeed);

			if (m_tInfo.fX < m_tCeilStickCollisionRectInfo.fX - m_tCeilStickCollisionRectInfo.fCX * 0.5)
			{
				m_bCeilStick = false;


				
				m_bGrabbing = false;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;
				m_bJump = false;
				m_fJumpDeltaSum = 0;

				m_bRightWallClimb = false;
				m_bLeftWallClimb = false;

				//JumpStart(10.f, 110.f);

				if (m_eLastLRDir == DIR_LEFT)
				{
					m_eAniStateSNB = AST_LEFT_SNB_CEILINGSTICKJUMP_START;
					m_eAniStateSNBARM = AST_LEFT_ARM_CEILINGSTICKJUMP_START;
				}
				else
				{
					m_eAniStateSNB = AST_RIGHT_SNB_CEILINGSTICKJUMP_START;
					m_eAniStateSNBARM = AST_RIGHT_ARM_CEILINGSTICKJUMP_START;
				}
			}
			
		}
		// 오른쪽 움직이기
		else if (bKeyPressingD)
		{
			
			Move(0.f, m_fSpeed);

			if (m_tInfo.fX > m_tCeilStickCollisionRectInfo.fX + m_tCeilStickCollisionRectInfo.fCX * 0.5)
			{
				m_bCeilStick = false;


				m_bGrabbing = false;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;
				m_bJump = false;
				m_fJumpDeltaSum = 0;

				m_bRightWallClimb = false;
				m_bLeftWallClimb = false;

				//JumpStart(10.f, 110.f);
				if (m_eLastLRDir == DIR_LEFT)
				{
					m_eAniStateSNB = AST_LEFT_SNB_CEILINGSTICKJUMP_START;
					m_eAniStateSNBARM = AST_LEFT_ARM_CEILINGSTICKJUMP_START;
				}
				else
				{
					m_eAniStateSNB = AST_RIGHT_SNB_CEILINGSTICKJUMP_START;
					m_eAniStateSNBARM = AST_RIGHT_ARM_CEILINGSTICKJUMP_START;
				}
			}
			
		}

		// 천장 탈출
		if (bKeyDownSpace)
		{
			m_bCeilStick = false;
			

			m_bGravity = true;
			m_fGravityDeltaSum = 0;

			m_bJump = false;
			m_fJumpDeltaSum = 0;

			m_bGrabbing = false;

			m_bRightWallClimb = false;
			m_bLeftWallClimb = false;

			if (m_eLastLRDir == DIR_LEFT)
			{
				m_eAniStateSNB = AST_LEFT_SNB_CEILINGSTICKJUMP_START;
				m_eAniStateSNBARM = AST_LEFT_ARM_CEILINGSTICKJUMP_START;
			}
			else
			{
				m_eAniStateSNB = AST_RIGHT_SNB_CEILINGSTICKJUMP_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_CEILINGSTICKJUMP_START;
			}
		}
		
	}

	//그랩을 타는경우
	else if (m_bGrabbing)
	{
		if (false)
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
		}
		
		if (bKeyPressingA)
		{
			Move(180.f, m_fSpeed);


		}
		//우
		else if (bKeyPressingD)
		{
			Move(0.f, m_fSpeed);

		}


		if (bKeyDownSpace)
		{
			// 그랩 당기기
			m_bGrabLoad = true;

			m_bJump = false;
			m_fJumpDeltaSum = 0;
		}
	}

	// 모든 상태가 아닌경우
	else
	{
		//좌
		if (bKeyDownA)
		{
			cout << "bKeyDownA" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_LEFT_SNB_RUNSTART_START;
				m_eAniStateSNBARM = AST_LEFT_ARM_RUNSTART_START;
			}

		}
		//우
		else if (bKeyDownD)
		{
			cout << "bKeyDownD" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_RIGHT_SNB_RUNSTART_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_RUNSTART_START;
			}
		}

		//좌
		if (bKeyPressingA)
		{
			Move(180.f, m_fSpeed);
			

		}
		//우
		else if (bKeyPressingD)
		{
			Move(0.f, m_fSpeed);
			
		}

		//좌
		if (bKeyUpA)
		{
			cout << "bKeyUpA" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_LEFT_SNB_RUNSTOP_START;
				m_eAniStateSNBARM = AST_LEFT_ARM_RUNSTOP_START;
			}
		}
		//우
		else if (bKeyUpD)
		{
			cout << "bKeyUpD" << endl;
			if (!m_bJump)
			{
				m_eAniStateSNB = AST_RIGHT_SNB_RUNSTOP_START;
				m_eAniStateSNBARM = AST_RIGHT_ARM_RUNSTOP_START;
			}
		}


		// Jump
		if (bKeyDownSpace)
		{
			if (m_bGrabLoad)
			{
				return;
			}

			if (!m_bJump)
			{
				JumpRoutine(90.f, 21.f);
			}
		}
	}
	

	if (bKeyPressingA)
	{
		m_eLastLRDir = DIR_LEFT;
	}
	else if(bKeyPressingD)
	{
		m_eLastLRDir = DIR_RIGHT;
	}

}

// 그랩이 충돌체에 닿았을때
void CObjPlayer2::Grab(CObjPlayer2Grab* pObj)
{
	// 벽타기충돌체가 아니면 취소
	if (pObj->Get_CollisionOption() != ERI_CLIMABLE)
	{
		if (m_pGrab != nullptr)
		{
			m_pGrab->Set_Dead_Cascade();
			m_pGrab = nullptr;
		}
		return;
	}

	if (m_pGrab != nullptr)
	{
		if (m_pGrab->Get_Dead())
		{
			return;
		}

		// TODO: 최소 그랩까지 당기는로직
		auto tmpWidth = m_tInfo.fX - m_pGrab->Get_Info()->fX;
		auto tmpHeigh = m_tInfo.fY - m_pGrab->Get_Info()->fY;
		auto tmpLen = sqrtf(tmpWidth * tmpWidth + tmpHeigh * tmpHeigh);

		if (tmpLen > m_fHookMaxLength)
		{
			// 훅 줄이기 리사이즈 필요
			m_bGrabHookResize = true;

			float rad = atan2f(tmpHeigh, tmpWidth);
			
			float tarX = m_pGrab->Get_Info()->fX + cosf(rad)* m_fHookMaxLength;
			float tarY = m_pGrab->Get_Info()->fY + sinf(rad)* m_fHookMaxLength;


			m_fGrabHookResizeTargetX = tarX;
			m_fGrabHookResizeTargetY = tarY;

			//m_tInfo.fX = tarX;
			//m_tInfo.fY = tarY;

			
		}

		if (tmpLen < m_fHookMinLength)
		{
			// 훅 늘이기 리사이즈 필요
			// 하지만 중력이 알아서?
		}






		//그랩 시작
		m_bGrabbing = true;


		if (m_eLastLRDir == DIR_LEFT)
		{
			m_eAniStateSNB = AST_LEFT_SNB_SWING_START;
			//m_eAniStateSNBARM = AST_LEFT_ARM_SWING_START;
		}
		else
		{
			m_eAniStateSNB = AST_RIGHT_SNB_SWING_START;
			//m_eAniStateSNBARM = AST_RIGHT_ARM_SWING_START;
		}
		

		auto width = m_tInfo.fX - m_pGrab->Get_Info()->fX;
		auto height = m_tInfo.fY - m_pGrab->Get_Info()->fY;

		// 진폭 세팅
		auto l = sqrtf(width * width + height * height);
		m_fPendLength = l;
		m_fPendDeltaSum = 0;
		m_fPendRad = atan2f(width, height);
		m_fPendStartX = m_pGrab->Get_Info()->fX;
		m_fPendStartY = m_pGrab->Get_Info()->fY;
	}
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

		float fTmpG = 9.81f * (m_fGravityDeltaSum * m_fGravityDeltaSum) * 0.5f;
		float fScaledTmpY = fTmpG * 7.0f;
		
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

void CObjPlayer2::JumpRoutine(float fAngle, float fSpeed)
{
	m_tInfo.fY -= 0.1;

	m_bJump = true;
	m_fJumpDeltaSum = 0.016 * 0;
	m_fJumpAngle = fAngle;
	m_fJumpVelocity = fSpeed;
	Apply_Jump();

	m_bGravity = true;
	m_fGravityDeltaSum = 0;

	m_bGround = false;

	m_bLeftWallClimb = false;
	m_bRightWallClimb = false;

	if (m_eLastLRDir == DIR_LEFT)
	{
		m_eAniStateSNB = AST_LEFT_SNB_JUMPING_START;
		m_eAniStateSNBARM = AST_LEFT_ARM_JUMPING_START;
	}
	else
	{
		m_eAniStateSNB = AST_RIGHT_SNB_JUMPING_START;
		m_eAniStateSNBARM = AST_RIGHT_ARM_JUMPING_START;
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
	// 그랩을 땡기고난후에는 그랩은 사라진다.
	if (m_pGrab != nullptr)
	{
		float width = m_pGrab->Get_Info()->fX - m_tInfo.fX;
		float height = m_pGrab->Get_Info()->fY - m_tInfo.fY;
		float fRad = atan2f(height, width);
		float x = cosf(fRad) * 30.f;
 		float y = sinf(fRad) * 30.f;
		m_tInfo.fX += x;
		m_tInfo.fY += y;
		//cout << x << endl;
		//cout << y << endl;
		

		// 플레이어가 그랩으로 당겨져셔 닿았을때
		RECT rc;
		if (IntersectRect(&rc, m_pGrab->Get_Rect(), this->Get_Rect()))
		{
			m_bGrabLoad = false;


			if (m_pGrab->Get_Ceiling())
			{
				//m_bCeilStick 시작지점
				m_bCeilStick = true;
				m_bGravity = false;

				m_tCeilStickCollisionRectInfo = m_pGrab->Get_CollisionRectInfo();

				if (m_eLastLRDir == DIR_LEFT)
				{
					m_eAniStateSNB = AST_LEFT_SNB_CEILINGSTICKSTART_START;
					m_eAniStateSNBARM = AST_LEFT_ARM_CEILINGSTICKSTART_START;
				}
				else
				{
					m_eAniStateSNB = AST_RIGHT_SNB_CEILINGSTICKSTART_START;
					m_eAniStateSNBARM = AST_RIGHT_ARM_CEILINGSTICKSTART_START;
				}
				
				// 들어가지 않게 체인 아래 위치시키기
				m_tInfo.fX = m_pGrab->Get_Info()->fX;
				m_tInfo.fY = (m_tCeilStickCollisionRectInfo.fY + m_tCeilStickCollisionRectInfo.fCY * 0.5f) + (m_tInfo.fCY * 0.5f);
			}
			else if (m_pGrab->Get_CollisionLeft())
			{
				m_bGrabbing = false;
				m_bLeftWallClimb = true;
				
				// 그랩 옆에 위치 시키기
				m_tInfo.fX = (m_pGrab->Get_CollisionRectInfo().fX - m_pGrab->Get_CollisionRectInfo().fCX * 0.5f) - (m_tInfo.fCX * 0.5f);
				m_tInfo.fY = m_pGrab->Get_Info()->fY; 
			}
			else if (m_pGrab->Get_CollisionRight())
			{
				m_bGrabbing = false;
				m_bRightWallClimb = true;

				// 그랩 옆에 위치 시키기
				m_tInfo.fX = (m_pGrab->Get_CollisionRectInfo().fX + m_pGrab->Get_CollisionRectInfo().fCX * 0.5f) + (m_tInfo.fCX * 0.5f);
				m_tInfo.fY = m_pGrab->Get_Info()->fY;
			}
			else {
				// 그랩 땡겼는데 땅이라면
				m_bGrabbing = false;

				m_bJump = false;
				m_bGravity = true;
				m_fGravityDeltaSum = 0;

			}

			// 땡긴 이후에는 그랩 제거
			m_pGrab->Set_Dead_Cascade();
			m_pGrab = nullptr;
		}
			
	}
	
}

void CObjPlayer2::GrabHookResize()
{
	if (m_pGrab != nullptr)
	{
		auto tmpWidth = m_pGrab->Get_Info()->fX -  m_tInfo.fX ;
		auto tmpHeigh = m_pGrab->Get_Info()->fY - m_tInfo.fY;
		auto tmpLen = sqrtf(tmpWidth * tmpWidth + tmpHeigh * tmpHeigh);
		float fRad = atan2f(tmpHeigh, tmpWidth);
		float x = cosf(fRad) * 30.f;
		float y = sinf(fRad) * 30.f;
		m_tInfo.fX += x;
		m_tInfo.fY += y;



		auto tmpAfterWidth = m_tInfo.fX - m_pGrab->Get_Info()->fX;
		auto tmpAfterHeigh = m_tInfo.fY - m_pGrab->Get_Info()->fY;
		auto tmpAfterLen = sqrtf(tmpAfterWidth * tmpAfterWidth + tmpAfterHeigh * tmpAfterHeigh);

		if (tmpAfterLen < m_fHookMaxLength)
		{
			m_bGrabHookResize = false;

			auto width = m_tInfo.fX - m_pGrab->Get_Info()->fX;
			auto height = m_tInfo.fY - m_pGrab->Get_Info()->fY;

			// 진폭 세팅
			auto l = sqrtf(width * width + height * height);
			m_fPendLength = l;
			m_fPendDeltaSum = 0;
			m_fPendRad = atan2f(width, height);
			m_fPendStartX = m_pGrab->Get_Info()->fX;
			m_fPendStartY = m_pGrab->Get_Info()->fY;
		}
	}
}
