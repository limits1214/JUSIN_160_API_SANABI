#include "pch.h"
#include "CObjMovable.h"
#include "CTimeMgr.h"

const float fTmpScale = 0.0000001f;

CObjMovable::CObjMovable()
{
    Set_DbgName(_T("CObjMovable"));
}

CObjMovable::~CObjMovable()
{
    Release();
}

void CObjMovable::Initialize()
{
	m_dwDeltaSum = 0;
	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();

	m_dwGravityDeltaSum = 0;
	m_dwJumpDeltaSum = 0;

	m_dwMoveLeftDeltaSum = 0;
	m_dwMoveRightDeltaSum = 0;

	m_bJump = false;
	m_fJumpVZero = 0.f;
	m_fJumpAngle = 90.f;
}

int CObjMovable::Update()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	DWORD dwDelta = dwNowTime - m_dwTime;

	m_dwTime = dwNowTime;
	m_dwDeltaSum += dwDelta;
	m_dwGravityDeltaSum += dwDelta;
	m_dwJumpDeltaSum += dwDelta;


 	DWORD  dwGravityDeltaMax = 1000;
	if (m_dwGravityDeltaSum > dwGravityDeltaMax)
	{
		//m_dwGravityDeltaSum = dwGravityDeltaMax;
	}

	if (true)
	{
		float fTmpG = 0.5f * 7.0f * GRAVITY * (m_dwGravityDeltaSum * m_dwGravityDeltaSum);
		float fScaledTmpY = fTmpG * fTmpScale;
		//float fMaxGravity = 100;
		//if (fTmpG > fMaxGravity)
		//{
		//	fScaledTmpY = fMaxGravity;
		//}
		_Move(DIR_DOWN, fScaledTmpY);

	}

	if (true && m_bJump)
	{
		DWORD  dwJumpDeltaMax = 1200;
		if (m_dwJumpDeltaSum > dwJumpDeltaMax)
		{
			//m_dwJumpDeltaSum = dwJumpDeltaMax;
		}

		float fDstX, fDstY;
		ParabolaNoGravityEquation(m_fJumpVZero, m_fJumpAngle, m_dwJumpDeltaSum, &fDstX, &fDstY);
		//_Move(DIR_LEFT, fDstX);
		_Move(DIR_UP, -fDstY);
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
