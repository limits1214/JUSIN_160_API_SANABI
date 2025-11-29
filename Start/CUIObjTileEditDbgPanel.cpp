#include "pch.h"
#include "CUIObjTileEditDbgPanel.h"
#include "CObjMgr.h"
#include "CUIObjRectButton.h"
#include "CUIObjText.h"
#include "CObjSprite.h"
#include "CEditMgr.h"

CUIObjTileEditDbgPanel::CUIObjTileEditDbgPanel()
	: m_eTEM(TEM_END)
{
	Set_DbgName(_T("CUIObjTileEditDbgPanel"));
}

CUIObjTileEditDbgPanel::~CUIObjTileEditDbgPanel()
{
	Release();
}

void CUIObjTileEditDbgPanel::Initialize()
{
	CUIObjPanel::Initialize();


}

int CUIObjTileEditDbgPanel::Update()
{
	int iUpdateResult = CUIObjPanel::Update();
	if (iUpdateResult != OBJ_NOEVENT)
		return iUpdateResult;




	
	auto hiermap = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
	list<CObj*> hier = CObjMgr::Get_Instance()->Get_HierarchyList(this->m_pUIContentBox);
	CObj* parent = hier.front();
	hier.pop_front();
	for (auto*& a : hier)
	{
		a->Set_Active_Cascade(false);
	}


	
	//CObjSprite* pSprite = new CObjSprite;
	//pSprite->Initialize();
	//pSprite->Set_CX(128);
	//pSprite->Set_CY(64);
	//pSprite->Set_Pos(WINCX >> 1, WINCY >> 1);
	//pSprite->Set_FrameKey(_T("TEST_TILE"));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pSprite);

	if (m_eTEM == TEM_LINE)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = LINE_ID_END;
			int startIemIdx = 0;
			if (listSize > viewItemCnt)
			{
				startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
			}
			int endItemIdx = startIemIdx + viewItemCnt;
			if (endItemIdx > listSize)
			{
				endItemIdx = listSize;
			}

			list<CUIObjRectButton*> targetBtnList;

			for (auto iter = hiermap.begin(); iter != hiermap.end(); ++iter)
			{
				auto pBtn = dynamic_cast<CUIObjRectButton*>((*iter).first);
				if (pBtn != nullptr)
				{
					targetBtnList.push_back(pBtn);
				}
			}

			auto shortageCnt = viewItemCnt - targetBtnList.size();
			if (shortageCnt > 0)
			{
				list<CObj*> tempList;
				for (int i = 0; i < shortageCnt; ++i)
				{
					CUIObjRectButton* pRectBtn = new CUIObjRectButton;
					pRectBtn->Initialize();
					pRectBtn->Set_Parent(this->m_pUIContentBox);

					CUIObjText* pText = new CUIObjText;
					pText->Initialize();
					pText->Set_Parent(pRectBtn);

					tempList.push_back(pText);
					tempList.push_back(pRectBtn);

					targetBtnList.push_back(pRectBtn);
				}

				for (auto*& a : tempList)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
				}
			}


			int idx = 0;
			for (int i = startIemIdx; i < endItemIdx; ++i)
			{
				auto iter3 = std::next(targetBtnList.begin(), idx);
				(*iter3)->Set_Active_Cascade(true);

				(*iter3)->Set_CX(info->fCX);
				(*iter3)->Set_CY(itemHeight);
				(*iter3)->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
				(*iter3)->Set_Parent(this->m_pUIContentBox);

				(*iter3)->Set_OnKeyDown([=]() {
					if (static_cast<LINE_ID>(i) == LINE_START)
					{
						CEditMgr::Get_Instance()->Set_EditLine(true);

					}
					else if (static_cast<LINE_ID>(i) == LINE_END)
					{
						CEditMgr::Get_Instance()->Set_EditLine(false);
					}
					else
					{
						CEditMgr::Get_Instance()->Set_Line(static_cast<LINE_ID>(i));
					}
					});

				TCHAR szTemp[256]{};
				LineId_To_Text(static_cast<LINE_ID>(i), szTemp);
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTemp);

				++idx;
			}
		}
	}
	else if (m_eTEM == TEM_GRID_TOGGLE)
	{

	}
	else if (m_eTEM == TEM_PICKING_MODE)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = EMPM_END;
			int startIemIdx = 0;
			if (listSize > viewItemCnt)
			{
				startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
			}
			int endItemIdx = startIemIdx + viewItemCnt;
			if (endItemIdx > listSize)
			{
				endItemIdx = listSize;
			}

			list<CUIObjRectButton*> targetBtnList;

			for (auto iter = hiermap.begin(); iter != hiermap.end(); ++iter)
			{
				auto pBtn = dynamic_cast<CUIObjRectButton*>((*iter).first);
				if (pBtn != nullptr)
				{
					targetBtnList.push_back(pBtn);
				}
			}

			auto shortageCnt = viewItemCnt - targetBtnList.size();
			if (shortageCnt > 0)
			{
				list<CObj*> tempList;
				for (int i = 0; i < shortageCnt; ++i)
				{
					CUIObjRectButton* pRectBtn = new CUIObjRectButton;
					pRectBtn->Initialize();
					pRectBtn->Set_Parent(this->m_pUIContentBox);

					CUIObjText* pText = new CUIObjText;
					pText->Initialize();
					pText->Set_Parent(pRectBtn);

					tempList.push_back(pText);
					tempList.push_back(pRectBtn);

					targetBtnList.push_back(pRectBtn);
				}

				for (auto*& a : tempList)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
				}
			}


			int idx = 0;
			for (int i = startIemIdx; i < endItemIdx; ++i)
			{
				auto iter3 = std::next(targetBtnList.begin(), idx);
				(*iter3)->Set_Active_Cascade(true);

				(*iter3)->Set_CX(info->fCX);
				(*iter3)->Set_CY(itemHeight);
				(*iter3)->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
				(*iter3)->Set_Parent(this->m_pUIContentBox);

				(*iter3)->Set_OnKeyDown([=]() {
					CEditMgr::Get_Instance()->Set_MousePickingMode(static_cast<EDIT_MOUSE_PICKING_MODE>(i));
					});

				TCHAR szTemp[256]{};
				EditMousePickingMode_To_Text(static_cast<EDIT_MOUSE_PICKING_MODE>(i), szTemp);
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTemp);

				++idx;
			}
		}
	}
	else if (m_eTEM == TEM_TILE)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = TILE_ID_END;
			int startIemIdx = 0;
			if (listSize > viewItemCnt)
			{
				startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
			}
			int endItemIdx = startIemIdx + viewItemCnt;
			if (endItemIdx > listSize)
			{
				endItemIdx = listSize;
			}

			list<CUIObjRectButton*> targetBtnList;

			for (auto iter = hiermap.begin(); iter != hiermap.end(); ++iter)
			{
				auto pBtn = dynamic_cast<CUIObjRectButton*>((*iter).first);
				if (pBtn != nullptr)
				{
					targetBtnList.push_back(pBtn);
				}
			}

			auto shortageBtnCnt = viewItemCnt - targetBtnList.size();
			if (shortageBtnCnt > 0)
			{
				list<CObj*> tempList;
				for (int i = 0; i < shortageBtnCnt; ++i)
				{
					CUIObjRectButton* pRectBtn = new CUIObjRectButton;
					pRectBtn->Initialize();
					pRectBtn->Set_Parent(this->m_pUIContentBox);

					CUIObjText* pText = new CUIObjText;
					pText->Initialize();
					pText->Set_Parent(pRectBtn);

					tempList.push_back(pText);
					tempList.push_back(pRectBtn);

					targetBtnList.push_back(pRectBtn);
				}

				for (auto*& a : tempList)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
				}
			}





			list<CObjSprite*> targetSpriteList;
			for (auto iter = hiermap.begin(); iter != hiermap.end(); ++iter)
			{
				auto pSprite = dynamic_cast<CObjSprite*>((*iter).first);
				if (pSprite != nullptr)
				{
					targetSpriteList.push_back(pSprite);
				}
			}
			auto shortageSpriteCnt = viewItemCnt - targetSpriteList.size();
			if (shortageSpriteCnt > 0)
			{
				list<CObj*> tempList;
				for (int i = 0; i < shortageSpriteCnt; ++i)
				{
					CObjSprite* pSprite = new CObjSprite;
					pSprite->Initialize();
					pSprite->Set_Parent(this->m_pUIContentBox);


					tempList.push_back(pSprite);

					targetSpriteList.push_back(pSprite);
				}

				for (auto*& a : tempList)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_SPRITE, a);
				}
			}








			int idx = 0;
			for (int i = startIemIdx; i < endItemIdx; ++i)
			{
				auto iter3 = std::next(targetBtnList.begin(), idx);
				(*iter3)->Set_Active_Cascade(true);

				(*iter3)->Set_CX(info->fCX  );
				(*iter3)->Set_CY(itemHeight);
				(*iter3)->Set_Pos(0 , +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
				(*iter3)->Set_Parent(this->m_pUIContentBox);

				(*iter3)->Set_OnKeyDown([=]() {
					if (static_cast<TILE_ID>(i) == TILE_START)
					{
						CEditMgr::Get_Instance()->Set_EditTile(true);

					}
					else if (static_cast<TILE_ID>(i) == TILE_START)
					{
						CEditMgr::Get_Instance()->Set_EditTile(false);
					}
					else
					{
						CEditMgr::Get_Instance()->Set_Tile(static_cast<TILE_ID>(i));
					}
					});

				TCHAR szTemp[256]{};
				Tile_Id_To_Text(static_cast<TILE_ID>(i), szTemp);
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTemp);













				INFO tileInfo = Tile_Id_To_TileInfo(static_cast<TILE_ID>(i));

				TCHAR szTileFrameKey[256]{};
				Tile_Id_To_FrameKey(static_cast<TILE_ID>(i), szTileFrameKey);
				
				auto iter4 = std::next(targetSpriteList.begin(), idx);
				(*iter4)->Set_Active_Cascade(true);
				(*iter4)->Set_CX(tileInfo.fCX);
				(*iter4)->Set_CY(tileInfo.fCY);
				(*iter4)->Set_Pos(-110, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
				(*iter4)->Set_FrameKey(szTileFrameKey);
				(*iter4)->Set_MoveFrame(false);
				(*iter4)->Set_Frame(FRAME{ int(tileInfo.fX / tileInfo.fCX),int(tileInfo.fX / tileInfo.fCX), int(tileInfo.fY / tileInfo.fCY), 0, 0});

				



				++idx;
			}
		}
	}
	else if (m_eTEM == TEM_IMG)
	{
		
	}
	else if (m_eTEM == TEM_END)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = TEM_END;
			int startIemIdx = 0;
			if (listSize > viewItemCnt)
			{
				startIemIdx = (listSize - viewItemCnt) * m_fYScrollPercent;
			}
			int endItemIdx = startIemIdx + viewItemCnt;
			if (endItemIdx > listSize)
			{
				endItemIdx = listSize;
			}

			list<CUIObjRectButton*> targetBtnList;

			for (auto iter = hiermap.begin(); iter != hiermap.end(); ++iter)
			{
				auto pBtn = dynamic_cast<CUIObjRectButton*>((*iter).first);
				if (pBtn != nullptr)
				{
					targetBtnList.push_back(pBtn);
				}
			}

			auto shortageCnt = viewItemCnt - targetBtnList.size();
			if (shortageCnt > 0)
			{
				list<CObj*> tempList;
				for (int i = 0; i < shortageCnt; ++i)
				{
					CUIObjRectButton* pRectBtn = new CUIObjRectButton;
					pRectBtn->Initialize();
					pRectBtn->Set_Parent(this->m_pUIContentBox);

					CUIObjText* pText = new CUIObjText;
					pText->Initialize();
					pText->Set_Parent(pRectBtn);

					tempList.push_back(pText);
					tempList.push_back(pRectBtn);

					targetBtnList.push_back(pRectBtn);
				}

				for (auto*& a : tempList)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, a);
				}
			}


			int idx = 0;
			for (int i = startIemIdx; i < endItemIdx; ++i)
			{
				auto iter3 = std::next(targetBtnList.begin(), idx);
				(*iter3)->Set_Active_Cascade(true);

				(*iter3)->Set_CX(info->fCX);
				(*iter3)->Set_CY(itemHeight);
				(*iter3)->Set_Pos(0, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
				(*iter3)->Set_Parent(this->m_pUIContentBox);
				
				(*iter3)->Set_OnKeyDown([=]() {
					switch (i)
					{
					case TEM_LINE:
						this->m_eTEM = TEM_LINE;
						break;
					case TEM_TILE:
						this->m_eTEM = TEM_TILE;
						break;
					case TEM_IMG:
						this->m_eTEM = TEM_IMG;
					case TEM_GRID_TOGGLE:
						CEditMgr::Get_Instance()->Set_ShowGrid(!CEditMgr::Get_Instance()->Get_ShowGrid());
						break;
					case TEM_PICKING_MODE:
						this->m_eTEM = TEM_PICKING_MODE;
						break;
					}
					});

				TCHAR szTemp[256]{};
				TileEditMode_To_Text(static_cast<TILE_EDIT_MODE>(i), szTemp);
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(szTemp);

				++idx;
			}
		}
	}

	





	return OBJ_NOEVENT;
}

void CUIObjTileEditDbgPanel::Late_Update()
{
	CUIObjPanel::Late_Update();
}

void CUIObjTileEditDbgPanel::Render(HDC hDC)
{
	CUIObjPanel::Render(hDC);
}

void CUIObjTileEditDbgPanel::Release()
{
	CUIObjPanel::Release();
}
