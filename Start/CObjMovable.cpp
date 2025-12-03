#include "pch.h"
#include "CObjMovable.h"
#include "CTimeMgr.h"

const float fTmpScale = 0.0000001f;

CObjMovable::CObjMovable(): m_bGrab(false), m_fPendLength(0.f), m_fPendRad(0.f)
{
    Set_DbgName(_T("CObjMovable"));
}

CObjMovable::~CObjMovable()
{
    Release();
}

void CObjMovable::Initialize()
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

int CObjMovable::Update()
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

	// 1 초에 16 정도
	// 1초 1000미리세컨
	// 

	


 	DWORD  dwGravityDeltaMax = 1000;
	if (m_fGravityDeltaSum > dwGravityDeltaMax)
	{
		//m_dwGravityDeltaSum = dwGravityDeltaMax;
	}
	if (m_bGrab)
	{
		return OBJ_NOEVENT;
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
		_Move(DIR_DOWN, fScaledTmpY);

	}

	if (true && m_bJump)
	{
		DWORD  dwJumpDeltaMax = 1200;
		if (m_fJumpDeltaSum > dwJumpDeltaMax)
		{
			//m_dwJumpDeltaSum = dwJumpDeltaMax;
		}


		float fDstX, fDstY;
		ParabolaNoGravityEquation(m_fJumpVZero * 4, m_fJumpAngle, m_fJumpDeltaSum, &fDstX, &fDstY);
		_Move(DIR_LEFT, fDstX);
		_Move(DIR_UP, -fDstY);

	
		
		if (fDstY - tempG < 0)
		{
			int x = 0;
		}
	}
    return OBJ_NOEVENT;
}

void CObjMovable::Late_Update()
{
}

void CObjMovable::Render(HDC hDC)
{
}

void CObjMovable::Release()
{
}

void CObjMovable::_Move(DIRECTION eDir, float fDistance)
{
}

void CObjMovable::ParabolaNoGravityEquation(float fVZero, float fAngle, float fDeltaSum, float* fDstX, float* fDstY)
{
	*fDstX = fVZero * cosf(fAngle * PI / 180.f) * fDeltaSum;
	*fDstY = fVZero * sinf(fAngle * PI / 180.f) * fDeltaSum;
}
