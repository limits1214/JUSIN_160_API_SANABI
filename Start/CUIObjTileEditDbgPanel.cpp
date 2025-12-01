#include "pch.h"
#include "CUIObjTileEditDbgPanel.h"
#include "CObjMgr.h"
#include "CUIObjRectButton.h"
#include "CUIObjText.h"
#include "CObjSprite.h"
#include "CEditMgr.h"
#include "CObjThings.h"
#include "CScrollMgr.h"

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

			
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(LineId_To_Text(static_cast<LINE_ID>(i)));

				++idx;
			}
		}
	}
	else if (m_eTEM == TEM_RECT)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = ERI_END;
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
					if (static_cast<EDIT_RECT_ID>(i) == ERI_START)
					{
						CEditMgr::Get_Instance()->Set_EditRect(true);

					}
					else if (static_cast<EDIT_RECT_ID>(i) == ERI_STOP)
					{
						CEditMgr::Get_Instance()->Set_EditRect(false);
					}
					else
					{
						CEditMgr::Get_Instance()->Set_Rect((static_cast<EDIT_RECT_ID>(i)));
					}
					});


				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(EditRectId_To_Text(static_cast<EDIT_RECT_ID>(i)));

				++idx;
			}
		}
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


				;
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(EditMousePickingMode_To_Text(static_cast<EDIT_MOUSE_PICKING_MODE>(i)));

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
					else if (static_cast<TILE_ID>(i) == TILE_END)
					{
						CEditMgr::Get_Instance()->Set_EditTile(false);
					}
					else
					{
						CEditMgr::Get_Instance()->Set_Tile(static_cast<TILE_ID>(i));
					}
					});


				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(Tile_Id_To_Text(static_cast<TILE_ID>(i)));











				if (!(i == 0 || i == 1))
				{
					//INFO tileInfo = Tile_Id_To_TileInfo(static_cast<TILE_ID>(i));
					TILE_INFO tileInfo = Tile_Id_To_TileInfo(static_cast<TILE_ID>(i));

					FRAME frame = FRAME{ tileInfo.iX, tileInfo.iX, tileInfo.iY, 0, 0 };

					auto iter4 = std::next(targetSpriteList.begin(), idx);
					(*iter4)->Set_Active_Cascade(true);
					(*iter4)->Set_CX(tileInfo.iCX);
					(*iter4)->Set_CY(tileInfo.iCY);
					(*iter4)->Set_Pos(-110, +(itemHeight * 0.5) - (info->fCY * 0.5) + (idx * itemHeight));
					//(*iter4)->Set_FrameKey(Tile_Id_To_FrameKey(static_cast<TILE_ID>(i)));
					(*iter4)->Set_FrameKeyId(Tile_Id_To_FrameKeyId(static_cast<TILE_ID>(i)));
					(*iter4)->Set_MoveFrame(false);
					(*iter4)->Set_Frame(frame);
				}

				

				



				++idx;
			}
		}
	}

	else if (m_eTEM == TEM_THINGS)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = TGS_END;
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

					int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
					int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

					CObjThings* pThgins = new CObjThings;
					pThgins->Set_Thgins(static_cast<THINGS_ID>(i));
					pThgins->Initialize();
					pThgins->Set_Pos((WINCX >> 1) - iScrollX, (WINCY >> 1) - iScrollY);
					CObjMgr::Get_Instance()->Add_Object(OBJ_THINGS, pThgins);
					});


				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(ThginsId_To_Text(static_cast<THINGS_ID>(i)));

				++idx;
			}
		}
	}
	
	else if (m_eTEM == TEM_FILE_SAVE || m_eTEM == TEM_FILE_LOAD)
	{
		{
			auto info = this->m_pUIContentBox->Get_Info();
			auto itemHeight = 20;
			int viewItemCnt = info->fCY / itemHeight;
			int listSize = FNI_END;
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
					if (m_eTEM == TEM_FILE_LOAD)
					{
						CEditMgr::Get_Instance()->Load_File(static_cast<FILE_NAME_ID>(i), true, []() {
							
							});
					}
					else if (m_eTEM == TEM_FILE_SAVE)
					{
						CEditMgr::Get_Instance()->Save_File(static_cast<FILE_NAME_ID>(i));
					}
					
					});

				;
				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(FileNameId_To_Text(static_cast<FILE_NAME_ID>(i)));

				++idx;
			}
		}
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
					case TEM_RECT:
						this->m_eTEM = TEM_RECT;
						break;
					case TEM_TILE:
						this->m_eTEM = TEM_TILE;
						break;
					case TEM_THINGS:
						this->m_eTEM = TEM_THINGS;
						break;
					case TEM_GRID_TOGGLE:
						CEditMgr::Get_Instance()->Set_ShowGrid(!CEditMgr::Get_Instance()->Get_ShowGrid());
						break;
					case TEM_PICKING_MODE:
						this->m_eTEM = TEM_PICKING_MODE;
						break;
					case TEM_FILE_LOAD:
						this->m_eTEM = TEM_FILE_LOAD;
						break;
					case TEM_FILE_SAVE:
						this->m_eTEM = TEM_FILE_SAVE;
						break;
					case TEM_CLEAR_ALL:
						
						CObjMgr::Get_Instance()->Dead_ID_Except({OBJ_EDIT_AREA, OBJ_MOUSE});

						break;

					case TEM_RUN:

						for (auto*& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_THINGS))
						{
							CObjThings* pTgs = dynamic_cast<CObjThings*>(pObj);
							if (pTgs != nullptr)
							{
								pTgs->ChangeReal();
							}
						}

						break;
					}
					});


				auto hiermap2 = CObjMgr::Get_Instance()->Get_HierarchyMap(this->m_pUIContentBox);
				dynamic_cast<CUIObjText*>(hiermap2[*iter3].front())->Set_Text(TileEditMode_To_Text(static_cast<TILE_EDIT_MODE>(i)));

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
