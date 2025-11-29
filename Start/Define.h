#pragma once

#define WINCX 800
#define WINCY 600

#define PURE = 0

#define PI 3.141592f

#define VK_MAX 0xff

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define TILECX 16
#define TILECY 16


#define CASE_MACRO(t) case t: lstrcpy(szText, _T(#t)); break;

enum OBJID
{
	OBJ_GRP,
	OBJ_LINE,
	OBJ_SPRITE,
	OBJ_INPUTCONTROLLER,

	OBJ_CLIMABLE_LINE,
	OBJ_NO_CLIMABLE_LINE,

	OBJ_PLAYER,

	OBJ_BUTTON,

	OBJ_DBG_UI,
	OBJ_UI,
	OBJ_EDIT_AREA,

	OBJ_TILE,

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
		CASE_MACRO(SC_LOGO)
		CASE_MACRO(SC_MENU)
		CASE_MACRO(SC_STAGE)
		CASE_MACRO(SC_TEST_UI)
		CASE_MACRO(SC_TUTORIAL)
		CASE_MACRO(SC_TILEEIDT)
		CASE_MACRO(SC_END)
	}
}

inline void ObjID_To_Text(OBJID eID, TCHAR* szText)
{
	switch (eID)
	{
		CASE_MACRO(OBJ_CLIMABLE_LINE)
		CASE_MACRO(OBJ_NO_CLIMABLE_LINE)
		CASE_MACRO(OBJ_PLAYER)
		CASE_MACRO(OBJ_LINE)
		CASE_MACRO(OBJ_INPUTCONTROLLER)
		CASE_MACRO(OBJ_SPRITE)
		CASE_MACRO(OBJ_BUTTON)
		CASE_MACRO(OBJ_UI)
		CASE_MACRO(OBJ_DBG_UI)
		CASE_MACRO(OBJ_MOUSE)
		CASE_MACRO(OBJ_GRP)
		CASE_MACRO(OBJ_EDIT_AREA)
		CASE_MACRO(OBJ_TILE)
		CASE_MACRO(OBJ_END)
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
	);
}

enum TILE_EDIT_MODE
{
	TEM_LINE,
	TEM_TILE,
	TEM_IMG,
	TEM_TRIGGER,
	TEM_GRID_TOGGLE,
	TEM_PICKING_MODE,
	TEM_FILE_SAVE,
	TEM_FILE_LOAD,
	TEM_END
};

enum TRIGGER_ID
{
	TRIG_END
};

inline void TileEditMode_To_Text(TILE_EDIT_MODE eID, TCHAR* szText)
{
	switch (eID)
	{
		CASE_MACRO(TEM_LINE)
		CASE_MACRO(TEM_TILE)
		CASE_MACRO(TEM_IMG)
		CASE_MACRO(TEM_GRID_TOGGLE)
		CASE_MACRO(TEM_TRIGGER)
		CASE_MACRO(TEM_PICKING_MODE)
		CASE_MACRO(TEM_FILE_SAVE)
		CASE_MACRO(TEM_FILE_LOAD)
		CASE_MACRO(TEM_END)
	}
}

enum FILE_NAME_ID
{
	FNI_TUTORIAL,
	FNI_ETC,
	FNI_END
};

inline void FileNameId_To_Text(FILE_NAME_ID eID, TCHAR* szText)
{
	switch (eID)
	{
		CASE_MACRO(FNI_TUTORIAL)
		CASE_MACRO(FNI_ETC)
		CASE_MACRO(FNI_END)
	}
}

enum TILE_ID
{
	TILE_START,
	TILE_END,
	TILE_TEST_1,
	TILE_TEST_2,
	Spr_Prologue_Tileset_1,
	TILE_ID_END
};

inline void Tile_Id_To_Text(TILE_ID eID, TCHAR* szText)
{
	switch (eID)
	{
		CASE_MACRO(TILE_START)
		CASE_MACRO(TILE_END)

		CASE_MACRO(TILE_TEST_1)
		CASE_MACRO(TILE_TEST_2)
		CASE_MACRO(Spr_Prologue_Tileset_1)
		CASE_MACRO(TILE_ID_END)
	}
}

inline void Tile_Id_To_FrameKey(TILE_ID eID, TCHAR* szText)
{
	switch (eID)
	{
	case TILE_TEST_1:
	case TILE_TEST_2:
		lstrcpy(szText, _T("TILE_TEST"));
		break;
	case Spr_Prologue_Tileset_1:
		lstrcpy(szText, _T("Spr_Prologue_Tileset"));
		break;
	case TILE_ID_END:
		break;
	}
}


inline INFO Tile_Id_To_TileInfo(TILE_ID eID)
{
	switch (eID)
	{
		case TILE_TEST_1: return {0, 0, 64, 64};
		case TILE_TEST_2: return { 64, 0, 64, 64 };
		case Spr_Prologue_Tileset_1: return { 0, 0, 16, 16 };

		case TILE_ID_END: return { 0, 0, 0, 0 };
	}
}

enum EDIT_MOUSE_PICKING_MODE
{
	EMPM_TILE_ORIGIN,
	EMPM_TILE_SIDE,
	EMPM_NONE,
	EMPM_END
};

inline void EditMousePickingMode_To_Text(EDIT_MOUSE_PICKING_MODE eID, TCHAR* szText)
{
	switch (eID)
	{
		CASE_MACRO(EMPM_TILE_ORIGIN)
		CASE_MACRO(EMPM_TILE_SIDE)
		CASE_MACRO(EMPM_NONE)
		CASE_MACRO(EMPM_END)
	}
}

enum LINE_ID
{
	LINE_START,
	LINE_END,
	LINE_CLIMABLE,
	LINE_NO_CLIMABLE,
	LINE_ID_END
};

inline void LineId_To_Text(LINE_ID eID, TCHAR* szText)
{
	switch (eID)
	{
		CASE_MACRO(LINE_START)
		CASE_MACRO(LINE_END)
		CASE_MACRO(LINE_CLIMABLE)
		CASE_MACRO(LINE_NO_CLIMABLE)
		CASE_MACRO(LINE_ID_END)
	}
}
