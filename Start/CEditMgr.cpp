#include "pch.h"
#include "CEditMgr.h"
#include "CObjTile.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CObjCollisionLine.h"
#include "CObjCollisionRect.h"
#include "CCollisionMgr.h"
#include "CObjThings.h"
#include "CScrollMgr.h"

CEditMgr* CEditMgr::m_pInstance = nullptr;


CEditMgr::CEditMgr()
	:m_bShowGrid(false),
	m_bEditLine(false),
	m_bEditRect(false),
	m_bEditTile(false),
	m_eTile(TILE_ID_END),
	m_eFileName(FNI_END),
	m_eMousePickingMode(EMPM_END),
	m_bFirstLine(true),
	m_bFirstRect(true),
	m_eLine(LINE_ID_END),
	m_eEditRect(ERI_END)
{
	ZeroMemory(&m_ptLastLine, sizeof(POINT));
	ZeroMemory(&m_ptLastRect, sizeof(POINT));
}

CEditMgr::~CEditMgr()
{
}


void CEditMgr::EditAreaLineMLKeyDown(POINT ptMouse)
{
	if (m_eLine == LINE_ID_END || m_eLine == LINE_START)
	{
		return;
	}
	if (!m_bEditLine)
	{
		return;
	}
	if (m_bFirstLine)
	{
		m_bFirstLine = false;
		m_ptLastLine = ptMouse;
	}
	else
	{

		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		ptMouse.x -= iScrollX;
		ptMouse.y -= iScrollY;

		m_ptLastLine.x -= iScrollX;
		m_ptLastLine.y -= iScrollY;


		LONG lWidth = ptMouse.x - m_ptLastLine.x;
		LONG lHeight = ptMouse.y - m_ptLastLine.y;
		LINEPOINT lpLeft = { (float)m_ptLastLine.x , (float)m_ptLastLine.y};
		LINEPOINT lpRight = { (float)ptMouse.x , (float)ptMouse.y };


		float posx = m_ptLastLine.x + lWidth * 0.5f;
		float posy = m_ptLastLine.y + lHeight * 0.5f;
		if (m_eLine == LINE_CLIMABLE)
		{
			CObjCollisionLine* line = new CObjCollisionLine;
			line->Initialize();
			line->Set_Pos(posx, posy);
			line->Set_Line_Point( lpLeft, lpRight);
			line->Set_Option(LCT_CLIMABLE);
			CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, line);
		}
		else if (m_eLine == LINE_NO_CLIMABLE)
		{
			CObjCollisionLine* line = new CObjCollisionLine;
			line->Initialize();
			line->Set_Pos(posx, posy);
			line->Set_Line_Point(lpLeft, lpRight);
			line->Set_Option(LCT_NOCLIMABLE);
			CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, line);
		}
		//m_ptLastLine = ptMouse;

		m_bFirstLine = true;
	}
}

void CEditMgr::EditAreaLineMRKeyDown(POINT ptMouse)
{
	if (m_eLine == LINE_ID_END || m_eLine == LINE_START || m_eLine == LINE_END)
	{
		return;
	}
	if (!m_bEditLine)
	{
		return;
	}

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	ptMouse.x -= iScrollX;
	ptMouse.y -= iScrollY;

	// 마우스 너비에 포함되는지 순회 돌면서 포함되면 첫번째 제거
	list<CObj*>* lineObjList = CObjMgr::Get_Instance()->Get_ObjectList(OBJ_LINE);

	CObj* pTargetObj = nullptr;
	for (auto iter = lineObjList->begin(); iter != lineObjList->end(); ++iter)
	{
		CObjLine* pLine = dynamic_cast<CObjLine*>(*iter);
		INFO lineInfo = *pLine->Get_Info();
		float outputX = 0;
		float outputY = 0;
		if (CCollisionMgr::Line_Equation(pLine, ptMouse.x, ptMouse.y, 0, 0, &outputX, &outputY))
		{
			if (isnan(outputY))
			{
				// 기울기가 세로인경우
					if (
						ptMouse.y <= pLine->Get_Rect()->bottom + 16
						&&
						ptMouse.y >= pLine->Get_Rect()->top - 16
						)
					{
						pTargetObj = pLine;
					}
			}
			else
			{
				if (
					// bottomMarin
					outputY <= ptMouse.y + 16
					&&
					// topMargin
					outputY >=  ptMouse.y - 16
					)
				{
					pTargetObj = pLine;
				}
			}
		}
	}

	if (pTargetObj != nullptr)
	{
		pTargetObj->Set_Dead();
	}


}

void CEditMgr::EditAreaRectMLKeyDown(POINT ptMouse)
{
	if (m_eEditRect == ERI_END || m_eEditRect == ERI_START || m_eEditRect == ERI_STOP)
	{
		return;
	}
	if (!m_bEditRect)
	{
		return;
	}

	if (m_bFirstRect)
	{
		m_bFirstRect = false;
		m_ptLastRect = ptMouse;
	}
	else
	{
		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		ptMouse.x -= iScrollX;
		ptMouse.y -= iScrollY;

		m_ptLastRect.x -= iScrollX;
		m_ptLastRect.y -= iScrollY;

		LONG lWidth = ptMouse.x - m_ptLastRect.x;
		LONG lHeight = ptMouse.y - m_ptLastRect.y;
		//LONG lWidth = fabsf(ptMouse.x - m_ptLastRect.x);
		//LONG lHeight = fabsf(ptMouse.y - m_ptLastRect.y);
		LINEPOINT lpLeft = { (float)m_ptLastRect.x , (float)m_ptLastRect.y };
		LINEPOINT lpRight = { (float)ptMouse.x , (float)ptMouse.y };


		float posx = m_ptLastRect.x + lWidth * 0.5f;
		float posy = m_ptLastRect.y + lHeight * 0.5f;
		if (m_eEditRect == ERI_CLIMABLE)
		{
			CObjCollisionRect* rect = new CObjCollisionRect;
			rect->Initialize();
			rect->Set_Pos(posx, posy);
			rect->Set_CX(fabsf(lWidth));
			rect->Set_CY(fabsf(lHeight));
			rect->Set_Option(ERI_CLIMABLE);
			CObjMgr::Get_Instance()->Add_Object(OBJ_RECT, rect);
		}
		else if (m_eEditRect == ERI_NO_CLIMABLE)
		{
			CObjCollisionRect* rect = new CObjCollisionRect;
			rect->Initialize();
			rect->Set_Pos(posx, posy); 
			rect->Set_CX(lWidth);
			rect->Set_CY(lHeight);
			rect->Set_Option(ERI_NO_CLIMABLE);
			CObjMgr::Get_Instance()->Add_Object(OBJ_RECT, rect);
		}

		m_bFirstRect = true;
	}
}

void CEditMgr::EditAreaRectMRKeyDown(POINT ptMouse)
{
	if (m_eEditRect == ERI_END || m_eEditRect == ERI_START)
	{
		return;
	}
	if (!m_bEditRect)
	{
		return;
	}

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	ptMouse.x -= iScrollX;
	ptMouse.y -= iScrollY;

	// 마우스 너비에 포함되는지 순회 돌면서 포함되면 첫번째 제거
	list<CObj*>* rectObjList = CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT);

	CObj* pTargetObj = nullptr;
	for (auto iter = rectObjList->begin(); iter != rectObjList->end(); ++iter)
	{
		CObjRect* pRect = dynamic_cast<CObjRect*>(*iter);
		if (PtInRect(pRect->Get_Rect(), ptMouse))
		{
			pTargetObj = pRect;
		}
	}

	if (pTargetObj != nullptr)
	{
		pTargetObj->Set_Dead();
	}
}

void CEditMgr::Save_File(FILE_NAME_ID eID)
{
	const TCHAR* szFileName = FileNameId_To_Text(eID);

	TCHAR szText[256]{};
	swprintf_s(szText, _T("%s 저장 합니까"), szFileName);
	// OK: 1, NO OK: 2
	auto res = MessageBox(g_hWnd, szText, L"Save_File", MB_OKCANCEL);

	if (res == 1)
	{
		TCHAR szPath[256]{};
		swprintf_s(szPath, _T("../Data/%s"), szFileName);
		HANDLE	hFile = CreateFile(szPath, // 파일 이름이 포함된 경로
			GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
			NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
			NULL,				// 보안 속성(기본값인 경우 NULL)
			CREATE_ALWAYS,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
			FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
			NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(g_hWnd, _T("OPEN FAIL"), L"Save_File", MB_OKCANCEL);
			return;
		}
		
		/*
		
		저장할 데이터
		1. 라인데이터
		2. 렉트데이터
		3. 타일데이터
		4. 띵스 데이터

		// TODO: 
		*/

		list<CObj*> lineList = *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_LINE);
		list<CObj*> rectList = *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT);
		list<CObj*> tileList = *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_TILE);
		list<CObj*> thingsList = *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_THINGS);

		DWORD		dwByte(0);

		// 파일 버전
		int fileVersion = 0;
		WriteFile(hFile, &fileVersion, sizeof(int), &dwByte, NULL);

		// 파일 헤더
		int lineListSize = lineList.size();
		int rectListSize = rectList.size();
		int tileListSize = tileList.size();
		int thingsListSize = thingsList.size();

		WriteFile(hFile, &lineListSize, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &rectListSize, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &tileListSize, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &thingsListSize, sizeof(int), &dwByte, NULL);

		// 파일 데이터

		// 파일 데이터 - 라인
		for (auto *& line: lineList)
		{
			CObjCollisionLine* cline = dynamic_cast<CObjCollisionLine*>(line);
			if (cline != nullptr)
			{
				INFO info = *line->Get_Info();
				//FRAME frame = line->Get_Frame();
				LINE l = cline->Get_Line();
				int option = cline->Get_Option();
				
				float fWidth = l.tRight.fX - l.tLeft.fX;
				float fHeight = l.tRight.fY - l.tRight.fY;

				WriteFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				//WriteFile(hFile, &frame, sizeof(FRAME), &dwByte, NULL);
				WriteFile(hFile, &l, sizeof(LINE), &dwByte, NULL);
				WriteFile(hFile, &option, sizeof(int), &dwByte, NULL);
			}
		}

		// 파일데이터 - 렉트
		for (auto*& rect : rectList)
		{
			CObjCollisionRect* crect = dynamic_cast<CObjCollisionRect*>(rect);
			if (crect != nullptr)
			{
				INFO info = *crect->Get_Info();
				int option = crect->Get_Option();

				WriteFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				WriteFile(hFile, &option, sizeof(int), &dwByte, NULL);
			}
		}

		// 파일 데이터 - 타일
		for (auto*& tile : tileList)
		{
			CObjTile* pTile = dynamic_cast<CObjTile*>(tile);
			if (pTile != nullptr)
			{
				INFO info = *pTile->Get_Info();
				FRAME frame = pTile->Get_Frame();
				FRAME_KEY_ID frameKeyId = pTile->Get_FrameKeyId();
				int option = pTile->Get_Option();

				WriteFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				WriteFile(hFile, &frame, sizeof(FRAME), &dwByte, NULL);
				WriteFile(hFile, &frameKeyId, sizeof(FRAME_KEY_ID), &dwByte, NULL);
				WriteFile(hFile, &option, sizeof(int), &dwByte, NULL);
			}
		}

		for (auto*& things : thingsList)
		{
			CObjThings* pThgins = dynamic_cast<CObjThings*>(things);
			if (pThgins != nullptr)
			{
				INFO info = *pThgins->Get_Info();
				THINGS_ID eThings = pThgins->Get_Thgins();
				WriteFile(hFile, &info, sizeof(INFO), &dwByte, NULL);
				WriteFile(hFile, &eThings, sizeof(THINGS_ID), &dwByte, NULL);
			}
		}





		CloseHandle(hFile);
		MessageBox(g_hWnd, L"저장완료", L"Save_File", MB_OK);
	}
	else if (res == 2)
	{
		MessageBox(g_hWnd, L"취소 되었습니다.", L"Save_File", MB_OK);
	}
}

//template<typename F>
void CEditMgr::Load_File(FILE_NAME_ID eID, bool bMsgBox, function<void()> fCallback)
{
	const TCHAR* szFileName = FileNameId_To_Text(eID);

	auto res = 1;
	if (bMsgBox)
	{
		TCHAR szText[256]{};
		swprintf_s(szText, _T("%s 로드 합니까"), szFileName);
		// OK: 1, NO OK: 2
		res = MessageBox(g_hWnd, szText, L"Load_File", MB_OKCANCEL);
	}
	
	

	if (res == 1)
	{
		TCHAR szPath[256]{};
		swprintf_s(szPath, _T("../Data/%s"), szFileName);
		HANDLE	hFile = CreateFile(szPath, // 파일 이름이 포함된 경로
			GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
			NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
			NULL,				// 보안 속성(기본값인 경우 NULL)
			OPEN_EXISTING,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
			FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
			NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(g_hWnd, _T("OPEN FAIL"), L"Load_File", MB_OKCANCEL);
			return;
		}

		/*

		로드할 데이터
		1. 버전
		2. 헤더
		3. 파일


		1. 라인데이터
		2. 타일데이터
		3. 띵스 데이터
		*/

		DWORD	dwByte(0);		// eof 역할
		
		// 버전 읽기;
		int iVersion = 0;
		ReadFile(hFile, &iVersion, sizeof(int), &dwByte, nullptr);

		// 헤더 일기
		int lineListSize = 0;
		int rectListSize = 0;
		int tileListSize = 0;
		int thingsListSize = 0;
		ReadFile(hFile, &lineListSize, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &rectListSize, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &tileListSize, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &thingsListSize, sizeof(int), &dwByte, nullptr);

		for (int i = 0; i < lineListSize; ++i)
		{
			INFO info;
			//FRAME frame;
			LINE l;
			int option;
			
			ReadFile(hFile, &info, sizeof(INFO), &dwByte, nullptr);
			//ReadFile(hFile, &frame, sizeof(FRAME), &dwByte, nullptr);
			ReadFile(hFile, &l, sizeof(LINE), &dwByte, nullptr);
			ReadFile(hFile, &option, sizeof(int), &dwByte, nullptr);

			CObjCollisionLine* cLine = new CObjCollisionLine;
			cLine->Initialize();
			cLine->Set_Pos(info.fX, info.fY);
			cLine->Set_Line_Point(l.tLeft, l.tRight);
			cLine->Set_Option(option);
			CObjMgr::Get_Instance()->Add_Object(OBJ_LINE, cLine);
		}

		for (int i = 0; i < rectListSize; ++i)
		{
			INFO info;
			int option;

			ReadFile(hFile, &info, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &option, sizeof(int), &dwByte, nullptr);


			CObjCollisionRect* cRect = new CObjCollisionRect;
			cRect->Initialize();
			cRect->Set_Pos(info.fX, info.fY);
			cRect->Set_CX(info.fCX);
			cRect->Set_CY(info.fCY);
			cRect->Set_Option(option);
			CObjMgr::Get_Instance()->Add_Object(OBJ_RECT, cRect);
		}

		for (int i = 0; i < tileListSize; ++i)
		{
			INFO info;
			FRAME frame;
			FRAME_KEY_ID frameKeyId;
			int option;

			ReadFile(hFile, &info, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &frame, sizeof(FRAME), &dwByte, nullptr);
			ReadFile(hFile, &frameKeyId, sizeof(FRAME_KEY_ID), &dwByte, nullptr);
			ReadFile(hFile, &option, sizeof(int), &dwByte, nullptr);

			CObjTile* pTile = new CObjTile;
			pTile->Initialize();
			pTile->Set_Pos(info.fX, info.fY);
			pTile->Set_Option(option);
			pTile->Set_FrameKeyId(frameKeyId);
			pTile->Set_Frame(frame);
			CObjMgr::Get_Instance()->Add_Object(OBJ_TILE, pTile);
		}

		for (int i = 0; i < thingsListSize; ++i)
		{
			INFO info ;
			THINGS_ID eThings;

			ReadFile(hFile, &info, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &eThings, sizeof(THINGS_ID), &dwByte, nullptr);

			CObjThings* pThings = new CObjThings;
			pThings->Set_Thgins(eThings);
			pThings->Initialize();
			pThings->Set_Pos(info.fX, info.fY);
			
			CObjMgr::Get_Instance()->Add_Object(OBJ_THINGS, pThings);
		}

		CloseHandle(hFile);

		fCallback();

		if (bMsgBox)
		{
			MessageBox(g_hWnd, L"로드완료", L"Save_File", MB_OK);
		}
	}
	else if (res == 2)
	{
		MessageBox(g_hWnd, L"취소 되었습니다.", L"Save_File", MB_OK);
	}
}

void CEditMgr::EditAreaTileMRKeyDown(POINT ptMouse)
{
	if (m_eTile == TILE_ID_END || m_eTile == TILE_START)
	{
		return;
	}
	if (!m_bEditTile)
	{
		return;
	}

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	ptMouse.x -= iScrollX;
	ptMouse.y -= iScrollY;

	int x = ptMouse.x;
	int y = ptMouse.y;
	for (auto& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_TILE))
	{
		int fx = pObj->Get_Info()->fX / TILECX;
		int fy = pObj->Get_Info()->fY / TILECY;
		fx *= TILECX;
		fy *= TILECY;
		if (fx == x && fy == y)
		{
			pObj->Set_Dead();
		}
	}

}
void CEditMgr::EditAreaTileMLKeyDown(POINT ptMouse)
{
	if (m_eTile == TILE_ID_END || m_eTile == TILE_START || m_eTile == TILE_END)
	{
		return;
	}
	if (!m_bEditTile)
	{
		return;
	}

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	ptMouse.x -= iScrollX;
	ptMouse.y -= iScrollY;
	
	int x = ptMouse.x;
	int y = ptMouse.y;
	for (auto& pObj : *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_TILE))
	{
		int fx = pObj->Get_Info()->fX / TILECX;
		int fy = pObj->Get_Info()->fY / TILECY;
		fx *= TILECX;
		fy *= TILECY;
		if (fx == x && fy == y)
		{
			pObj->Set_Dead();
		}
	}

	TILE_INFO tileInfo = Tile_Id_To_TileInfo(m_eTile);

	FRAME frame = FRAME{ tileInfo.iX, tileInfo.iX, tileInfo.iY, 0, 0 };

	CObjTile* pTile = new CObjTile;
	pTile->Initialize();
	pTile->Set_Pos(x, y);
	pTile->Set_FrameKeyId(Tile_Id_To_FrameKeyId(m_eTile));
	pTile->Set_Frame(frame);
	CObjMgr::Get_Instance()->Add_Object(OBJ_TILE, pTile);
}
