#include "pch.h"
#include "CObjThings.h"
#include "CEditMgr.h"
#include "CObjMgr.h"
#include "CUIObjText.h"
#include "CObjMouse.h"
#include "CScrollMgr.h"
#include "CObjPlayer.h"
#include "CObjPlayer2.h"
#include "CObjSprite.h"
#include "CObjGameUiChapterBtn.h"
#include "CObjMonsterFloatingBomb.h"
#include "CObjUnstableKnockbackPlatformA.h"

CObjThings::CObjThings()
	:m_bMouseTrack(false)
{
	Set_DbgName(_T("CObjThings"));
}

CObjThings::~CObjThings()
{
	Release();
}

void CObjThings::Initialize()
{
	m_bUseMainScroll = true;

	if (m_eThings == TGS_PLAYER_POS)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_MONSTER_A_POS)
	{
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_MONSTER_G_POS)
	{
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_MONSTER_B_POS)
	{
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eThings == TGS_BOSS_FIREBIRD_POS)
	{
		m_tInfo.fCX = 300.f;
		m_tInfo.fCY = 300.f;
	}
	else
	{
		m_tInfo.fCX = TILECX * 4;
		m_tInfo.fCY = TILECY * 4;
	}

	


	CUIObjText* pText = new CUIObjText;
	pText->Initialize();
	pText->Set_Text(ThginsId_To_Text(m_eThings));
	pText->Set_Pos(0, 0);
	pText->Set_Parent(this);
	pText->Set_UseMainScroll(true);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pText);

}

int CObjThings::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjThings::Late_Update()
{
}

void CObjThings::Render(HDC hDC)
{
//	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
//	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Rectangle(hDC, m_tRect.left, m_tRect.top , m_tRect.right , m_tRect.bottom );
}

void CObjThings::Release()
{
}

void CObjThings::On_Mouse_Key_Down(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{

		POINT ptCurr = pMouse->Get_Pt_Curr();


		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		ptCurr.x -= iScrollX;
		ptCurr.y -= iScrollY;

		if (PtInRect(&m_tRect, ptCurr))
		{
			if (pMouse->Get_Last_Key() == VK_LBUTTON)
			{
				m_bMouseTrack = true;
			}
			else if (pMouse->Get_Last_Key() == VK_RBUTTON)
			{
				if (1 == MessageBox(g_hWnd, L"지우나요", L"지우나요", MB_OKCANCEL))
				{
					Set_Dead_Cascade();
				}
				
			}
			
			pMouse->Mouse_PreventEvent();
		}
	}
}

void CObjThings::On_Mouse_Key_Up(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		if (m_bMouseTrack)
		{
			m_bMouseTrack = false;
			pMouse->Mouse_PreventEvent();
		}
	}
}

void CObjThings::On_Mouse_Key_Pressing(CObj* pObj)
{
	CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
	if (pMouse != nullptr)
	{
		POINT ptCurr = pMouse->Get_Pt_Curr();
		POINT ptPrev = pMouse->Get_Pt_Prev();
		
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		ptPrev.x -= iScrollX;
		ptPrev.y -= iScrollY;

		ptCurr.x -= iScrollX;
		ptCurr.y -= iScrollY;


		if (m_bMouseTrack)
		{
			EDIT_MOUSE_PICKING_MODE pickingMode = CEditMgr::Get_Instance()->Get_MousePickingMode();
			if (pickingMode == EMPM_TILE_ORIGIN)
			{
				int	x = ptCurr.x / TILECX;
				int	y = ptCurr.y / TILECY;

				x *= TILECX;
				y *= TILECY;
				POINT _ptCurr = POINT{ x, y };

				m_tInfo.fX = _ptCurr.x + (TILECX >> 1);
				m_tInfo.fY = _ptCurr.y + (TILECY >> 1);
			}
			else if (pickingMode == EMPM_TILE_SIDE)
			{
				int	x = ptCurr.x / TILECX;
				int	y = ptCurr.y / TILECY;

				x *= TILECX;
				y *= TILECY;
				POINT _ptCurr = POINT{ x, y };

				m_tInfo.fX = _ptCurr.x;
				m_tInfo.fY = _ptCurr.y;
			}
			else
			{
				long movedX = ptCurr.x - ptPrev.x;
				long movedY = ptCurr.y - ptPrev.y;

				m_tInfo.fX += movedX;
				m_tInfo.fY += movedY;
			}
			pMouse->Mouse_PreventEvent();
		}
		
	}
}


void Util_CreateThingsSprite(CObj* pObj, TILE_ID eTileId)
{
	CObjSprite* pSprite = new CObjSprite;
	TILE_INFO tileInfo = Tile_Id_To_TileInfo(eTileId);
	FRAME frame = FRAME{ tileInfo.iX, tileInfo.iX, tileInfo.iY, 0, 0 };

	pSprite->Set_CX(tileInfo.iCX);
	pSprite->Set_CY(tileInfo.iCY);
	pSprite->Set_Pos(pObj->Get_Info()->fX, pObj->Get_Info()->fY);
	pSprite->Set_FrameKeyId(Tile_Id_To_FrameKeyId(eTileId));
	pSprite->Set_MoveFrame(false);
	pSprite->Set_Frame(frame);
	CObjMgr::Get_Instance()->Add_Object(OBJ_SPRITE, pSprite);
}

#define CREATE_THINGS_SPRITE(A) case TGS_##A: Util_CreateThingsSprite(this, A); break;

void CObjThings::ChangeReal()
{

	switch (m_eThings)
	{
	case TGS_PLAYER_POS:
	{
		CObjPlayer2* pPlayer = new CObjPlayer2;
		pPlayer->Initialize();
		pPlayer->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
	}
		break;
	case TGS_MONSTER_A_POS:
		break;
	case TGS_MONSTER_B_POS:
		break;
	case TGS_MONSTER_G_POS:
		break;
	case TGS_BOSS_FIREBIRD_POS:
		break;

	case TGS_FLTBOMB_POS:
	{
		CObjMonsterFloatingBomb* pFlotBomb = new CObjMonsterFloatingBomb;
		pFlotBomb->Initialize();
		pFlotBomb->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFlotBomb);
	}
		break;

	case TGS_UNSTABLE_KNOCKBACK_PLATFORM_A_POS:
	{
		CObjUnstableKnockbackPlatformA* pPlatform = new CObjUnstableKnockbackPlatformA;
		pPlatform->Initialize();
		pPlatform->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		//TODO: OBJ_PLATFORM
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform);
	}
	break;
	case TGS_UI_Chapter1_Btn:
	{
		CObjGameUiChapterBtn* pBtn = new CObjGameUiChapterBtn;
		pBtn->Set_Option(0);
		pBtn->Initialize();
		pBtn->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pBtn);
	}
		break;
	case TGS_UI_Chapter2_Btn:
	{
		CObjGameUiChapterBtn* pBtn = new CObjGameUiChapterBtn;
		pBtn->Set_Option(1);
		pBtn->Initialize();
		pBtn->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pBtn);
	}
		break;
	case TGS_UI_Chapter3_Btn:
	{
		CObjGameUiChapterBtn* pBtn = new CObjGameUiChapterBtn;
		pBtn->Set_Option(2);
		pBtn->Initialize();
		pBtn->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pBtn);
	}
		break;




	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58)
	CREATE_THINGS_SPRITE(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59)

	}

	// 음... 죽일까 아니면 놔둘까...?
	Set_Dead_Cascade();
}

