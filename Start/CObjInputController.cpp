#include "pch.h"
#include "CObjInputController.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CObjGrp.h"
#include "CObjPlayer.h"
CObjInputController::CObjInputController()
{
	Set_DbgName(_T("CObjInputController"));
}

CObjInputController::~CObjInputController()
{
	Release();
}

void CObjInputController::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
}

int CObjInputController::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjInputController::Late_Update()
{
}

void CObjInputController::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjInputController::Release()
{
}

void CObjInputController::Key_Input()
{

	

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		CObjGrp* grp = dynamic_cast<CObjGrp*>(this->m_pParent);
		if (grp != nullptr)
		{
			auto info = grp->Get_Info();
			grp->Set_Pos(info->fX - 5, info->fY);
		}
		for (auto*& pChild : CObjMgr::Get_Instance()->Get_HierarchyList(grp))
		{
			CObjPlayer* pPlayer = dynamic_cast<CObjPlayer*>(pChild);
			if (pPlayer != nullptr)
			{
				pPlayer->Set_PlayerState(CObjPlayer::STATE::RUNNING);
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		//m_tInfo.fX += 5;
		CObjGrp* grp = dynamic_cast<CObjGrp*>(this->m_pParent);
		if (grp != nullptr)
		{
			auto info = grp->Get_Info();
			grp->Set_Pos(info->fX + 5, info->fY);
		}
		for (auto*& pChild : CObjMgr::Get_Instance()->Get_HierarchyList(grp))
		{
			CObjPlayer* pPlayer = dynamic_cast<CObjPlayer*>(pChild);
			if (pPlayer != nullptr)
			{
				pPlayer->Set_PlayerState(CObjPlayer::STATE::RUNNING);
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		CObjGrp* grp = dynamic_cast<CObjGrp*>(this->m_pParent);
		if (grp != nullptr)
		{
			auto info = grp->Get_Info();
			grp->Set_Pos(info->fX, info->fY - 5);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		CObjGrp* grp = dynamic_cast<CObjGrp*>(this->m_pParent);
		if (grp != nullptr)
		{
			auto info = grp->Get_Info();
			grp->Set_Pos(info->fX, info->fY + 5);
		}
	}
}