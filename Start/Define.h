#pragma once

#define WINCX 800
#define WINCY 600

#define PURE = 0

#define PI 3.141592f

#define VK_MAX 0xff

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

enum OBJID
{
	OBJ_GRP,
	OBJ_LINE,
	OBJ_SPRITE,
	OBJ_INPUTCONTROLLER,

	OBJ_PLAYER,

	OBJ_BUTTON,

	OBJ_DBG_UI,
	OBJ_UI,

	OBJ_MOUSE,

	OBJ_END
};

enum SCENEID
{
	SC_LOGO,
	SC_MENU,
	SC_STAGE,
	SC_TEST_UI,
	SC_TUTORIAL,
	SC_TILEEIDT,
	SC_END
};

enum RENDER_ORDERID
{
	RDO_0,
	RDO_1,
	RDO_2,
	RDO_3,
	RDO_4,
	RDO_5,
	RDO_6,
	RDO_7,
	RDO_8,
	RDO_9,
	RDO_END
};

enum COLLISIONID
{
	COLL_LINE,

	COLL_END
};

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;
} INFO;



extern HWND g_hWnd;



typedef struct tagTimerInfo
{
	bool bStart;
	DWORD dwTime;
	DWORD dwLastTime;
	function<void()> func;
} TIMERINFO;

struct tagFinder
{
	tagFinder(const TCHAR* pTag): m_pTag(pTag){}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}

	const TCHAR* m_pTag;
};

struct tagDeleteMap
{
	template<typename T>
	void operator()(T& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};

typedef struct tagFrame
{
	int iStart;
	int iEnd;
	int iMotion;
	DWORD dwSpeed;
	DWORD dwTime;
} FRAME;

inline void SceneID_To_Text(SCENEID eID, TCHAR* szText)
{
	switch (eID)
	{
	case SC_LOGO:
		lstrcpy(szText, _T("SC_LOGO"));
		break;
	case SC_MENU:
		lstrcpy(szText, _T("SC_MENU"));
		break;
	case SC_STAGE:
		lstrcpy(szText, _T("SC_STAGE"));
		break;
	case SC_TEST_UI:
		lstrcpy(szText, _T("SC_TEST_UI"));
		break;
	case SC_TUTORIAL:
		lstrcpy(szText, _T("SC_TUTORIAL"));
		break;
	case SC_TILEEIDT:
		lstrcpy(szText, _T("SC_TILEEIDT"));
		break;
	case SC_END:
		lstrcpy(szText, _T("SC_END"));
		break;
	}
}

inline void ObjID_To_Text(OBJID eID, TCHAR* szText)
{
	switch (eID)
	{
	case OBJ_PLAYER:
		lstrcpy(szText, _T("OBJ_PLAYER"));
		break;
	case OBJ_LINE:
		lstrcpy(szText, _T("OBJ_LINE"));
		break;
	case OBJ_INPUTCONTROLLER:
		lstrcpy(szText, _T("OBJ_INPUTCONTROLLER"));
		break;
	case OBJ_SPRITE:
		lstrcpy(szText, _T("OBJ_SPRITE"));
		break;
	case OBJ_BUTTON:
		lstrcpy(szText, _T("OBJ_BUTTON"));
		break;
	case OBJ_UI:
		lstrcpy(szText, _T("OBJ_UI"));
		break;
	case OBJ_DBG_UI:
		lstrcpy(szText, _T("OBJ_DBG_UI"));
		break;
	case OBJ_MOUSE:
		lstrcpy(szText, _T("OBJ_MOUSE"));
		break;
	case OBJ_GRP:
		lstrcpy(szText, _T("OBJ_GRP"));
		break;
	case OBJ_END:
		lstrcpy(szText, _T("OBJ_END"));
		break;
	}
}

typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;


typedef struct tagLine
{
	tagLinePoint		tLeft;
	tagLinePoint		tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(tagLinePoint _tLeft, tagLinePoint _tRight)
		: tLeft(_tLeft), tRight(_tRight) {
	}

}LINE;

/// <summary>
/// 
/// 
/// </summary>
/// <param name="dsthDC">대상 </param>
/// <param name="dstX">대상의 레프트</param>
/// <param name="dstY">대상의 탑</param>
/// <param name="dstWidth">대상의 가로</param>
/// <param name="dstHeight">대상 세로</param>
/// <param name="srchDC">이미지</param>
/// <param name="srcX">이미지 레프트</param>
/// <param name="srcY">이미지 탑</param>
/// <param name="srcWidth">이미지 가로</param>
/// <param name="srcHeight">이미지 세로</param>
inline void BmpRender(
	HDC dsthDC,
	int dstX, int dstY,
	int dstWidth, int dstHeight,
	HDC srchDC,
	int srcX, int srcY,
	int srcWidth, int srcHeight
	)
{
	GdiTransparentBlt(dsthDC,				
		dstX,	// 복사 받을 공간의 LEFT	
		dstY,				// 복사 받을 공간의 TOP
		dstWidth,			// 복사 받을 공간의 가로 
		dstHeight,			// 복사 받을 공간의 세로 
		srchDC,				// 복사 할 DC
		srcX,					// 복사할 이미지의 LEFT, TOP
		srcY,
		srcWidth,		// 복사할 이미지의 가로, 세로
		srcHeight,
		RGB(255, 0, 255)
	);	// 제거할 색상
}