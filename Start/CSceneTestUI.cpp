#include "pch.h"
#include "CSceneTestUI.h"

#include "CUIObjRectButton.h"
//#include "CUIObjNode.h"

#include "CUIObjPanel.h"

#include "CObjMgr.h"

#include "CUIObjText.h"


#include "CUIObjDbgPanel.h"

CSceneTestUI::CSceneTestUI()
{
}

CSceneTestUI::~CSceneTestUI()
{
	Release();
}

void CSceneTestUI::Initialize()
{
	//CUIObjNode* pRootNode = new CUIObjNode;
	//pRootNode->Initialize();
	//pRootNode->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pRootNode);

	//CUIObjPanel* pUiPanel = new CUIObjPanel;
	//pUiPanel->Initialize();
	//pUiPanel->Set_CX(WINCX >> 1);
	//pUiPanel->Set_CY(WINCY >> 1);
	//pUiPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pUiPanel);

	//CUIObjRectButton* pRectBtn1 = new CUIObjRectButton;
	//pRectBtn1->Initialize();
	//pRectBtn1->Set_CX(100);
	//pRectBtn1->Set_CY(20);
	//pRectBtn1->Set_Pos(WINCX >> 1, WINCY >> 1);
	//pRectBtn1->Set_OnKeyDown([=]() {
	//	pRectBtn1->Set_CY(100);
	//	});
	//
	//CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pRectBtn1);

	//CUIObjRectButton* pRectBtn2 = new CUIObjRectButton;
	//pRectBtn2->Initialize();
	//pRectBtn2->Set_CX(100);
	//pRectBtn2->Set_CY(20);
	//pRectBtn2->Set_Pos((WINCX >> 1) + 100, WINCY >> 1);
	//pRectBtn2->Set_OnKeyDown([=]() {
	//	pRectBtn1->Set_Active(true);
	//	});
	//CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pRectBtn2);

	//CUIObjRectButton* pRectBtn3 = new CUIObjRectButton;
	//pRectBtn3->Initialize();
	//pRectBtn3->Set_CX(100);
	//pRectBtn3->Set_CY(20);
	//pRectBtn3->Set_Pos((WINCX >> 1) + 200, WINCY >> 1);
	//pRectBtn3->Set_OnKeyDown([=]() {
	//	pRectBtn1->Set_Active(false);
	//	});
	//CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pRectBtn3);

	//CUIObjRectButton* pRectBtn2 = new CUIObjRectButton;
	//pRectBtn2->Initialize();
	//pRectBtn2->Set_CX(100);
	//pRectBtn2->Set_CY(50);
	//pRectBtn2->Set_Pos(200, 0);
	//pRectBtn2->Set_Parent(pUiPanel);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pRectBtn2);

	//CUIObjRectButton* pRectBtn3 = new CUIObjRectButton;
	//pRectBtn3->Initialize();
	//pRectBtn3->Set_CX(100);
	//pRectBtn3->Set_CY(50);
	//pRectBtn3->Set_Pos(0, 100);
	//pRectBtn3->Set_Parent(pRectBtn2);
	//pRectBtn3->Set_OnKeyDown([=]() {
	//	pRectBtn2->Set_Dead_Cascade();
	//	});
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pRectBtn3);

	//CUIObjText* pRectBtn3Text = new CUIObjText;
	//pRectBtn3Text->Initialize();
	//pRectBtn3Text->Set_CX(100);
	//pRectBtn3Text->Set_CY(50);
	//pRectBtn3Text->Set_Pos(0, 0);
	//pRectBtn3Text->Set_Text(_T("asfsdf"));
	//pRectBtn3Text->Set_Parent(pRectBtn3);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pRectBtn3Text);

	//CUIObjPanel* pUiPanel2 = new CUIObjPanel;
	//pUiPanel2->Initialize();
	//pUiPanel2->Set_CX(WINCX >> 2);
	//pUiPanel2->Set_CY(WINCY >> 2);
	//pUiPanel2->Set_Pos((WINCX >> 1) + 330, (WINCY >> 1) + 0);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pUiPanel2);

	//CUIObjText* pUiPanel2Text = new CUIObjText;
	//pUiPanel2Text->Initialize();
	//pUiPanel2Text->Set_Pos(0,0);
	//pUiPanel2Text->Set_Text(_T("Temp"));
	//pUiPanel2Text->Set_Parent(pUiPanel2);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pUiPanel2Text);



	//CUIObjBox* pBox = new CUIObjBox;
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, pBox);
	//pBox->Initialize();
	//pBox->Set_Pos(100, 100);
	//pBox->Set_CX(100);
	//pBox->Set_CY(100);

	//CUIObjText* pUiTextTemp = new CUIObjText;
	//pUiTextTemp->Initialize();
	//pUiTextTemp->Set_Pos(100,100);
	//pUiTextTemp->Set_Text(_T("asdfasdfasdfasdfasdfasdf"));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pUiTextTemp);

	CUIObjDbgPanel* pDbgPanel = new CUIObjDbgPanel;
	CObjMgr::Get_Instance()->Add_Object(OBJ_DBG_UI, pDbgPanel);
	pDbgPanel->Initialize();
	pDbgPanel->Set_CX(WINCX >> 2);
	pDbgPanel->Set_CY(WINCY >> 2);
	pDbgPanel->Set_Pos((WINCX >> 1) + 0, (WINCY >> 1) + 0);
	pDbgPanel->Set_Header_Text(_T("DBG_PANEL"));
}

int CSceneTestUI::Update()
{
	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CSceneTestUI::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneTestUI::Render(HDC hDC)
{

	//Rectangle(hDC, 100, 100, 300, 300);

	//TCHAR szText[256];
	//swprintf_s(szText, _T("asdf\nqwer\nasdf\nd"));

	RECT rc{};
	////DrawText(hDC, szText, lstrlen(szText), &rc, DT_CALCRECT);
	//OffsetRect(&rc, 100, 100);

	//Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
	//DrawText(hDC, szText, lstrlen(szText), &rc, DT_TOP);
	CObjMgr::Get_Instance()->Render(hDC);

}

void CSceneTestUI::Release()
{
	//CObjMgr::Get_Instance()->Release();
}
