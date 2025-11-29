#pragma once

extern HWND g_hWnd;

#define WINCX 800
#define WINCY 600

#define PURE = 0

#define PI 3.141592f

#define VK_MAX 0xff

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define TILECX 16
#define TILECY 16

#define STR_MACRO(A) static const TCHAR* STR_##A = _T(#A)
#define STR_MACRO2(A, B) static const TCHAR* STR_##A = _T(B)
#define STR_CASE_MACRO(A) case A: return STR_##A;

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

enum FRAME_KEY_ID
{
	FKI_TILE_TEST,
	FKI_Spr_Prologue_Tileset,
	FKI_TEST_BTN_START,
	FKI_TEST_BTN_EDIT,
	FKI_TEST_BTN_EXIT,
	FKI_SNB,
	FKI_END
};

STR_MACRO2(FKI_TILE_TEST, "TILE_TEST");
STR_MACRO2(FKI_Spr_Prologue_Tileset, "Spr_Prologue_Tileset");
STR_MACRO2(FKI_TEST_BTN_START, "Start");
STR_MACRO2(FKI_TEST_BTN_EDIT, "Edit");
STR_MACRO2(FKI_TEST_BTN_EXIT, "Exit");
STR_MACRO2(FKI_SNB, "SNB");
STR_MACRO(FKI_END);

inline const TCHAR* FrameKeyId_To_Text2(FRAME_KEY_ID eID)
{
	switch (eID)
	{
	case FKI_TILE_TEST:
		return STR_FKI_TILE_TEST;
	case FKI_Spr_Prologue_Tileset:
		return STR_FKI_Spr_Prologue_Tileset;
	case FKI_TEST_BTN_START:
		return STR_FKI_TEST_BTN_START;
	case FKI_TEST_BTN_EDIT:
		return STR_FKI_TEST_BTN_EDIT;
	case FKI_TEST_BTN_EXIT:
		return STR_FKI_TEST_BTN_EXIT;
	case FKI_SNB:
		return STR_FKI_SNB;


	case FKI_END:
		return STR_FKI_TILE_TEST;
	}
}

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


STR_MACRO(SC_LOGO);
STR_MACRO(SC_MENU);
STR_MACRO(SC_STAGE);
STR_MACRO(SC_TEST_UI);
STR_MACRO(SC_TUTORIAL);
STR_MACRO(SC_TILEEIDT);
STR_MACRO(SC_END);

inline const TCHAR* SceneID_To_Text(SCENEID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(SC_LOGO)
		STR_CASE_MACRO(SC_MENU)
		STR_CASE_MACRO(SC_STAGE)
		STR_CASE_MACRO(SC_TEST_UI)
		STR_CASE_MACRO(SC_TUTORIAL)
		STR_CASE_MACRO(SC_TILEEIDT)
		STR_CASE_MACRO(SC_END)
	}
}


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
	OBJ_THINGS,

	OBJ_DBG_UI,
	OBJ_UI,
	OBJ_EDIT_AREA,


	OBJ_TILE,

	OBJ_MOUSE,

	OBJ_END
};

STR_MACRO(OBJ_CLIMABLE_LINE);
STR_MACRO(OBJ_NO_CLIMABLE_LINE);
STR_MACRO(OBJ_LINE);
STR_MACRO(OBJ_PLAYER);
STR_MACRO(OBJ_INPUTCONTROLLER);
STR_MACRO(OBJ_SPRITE);
STR_MACRO(OBJ_BUTTON);
STR_MACRO(OBJ_UI);
STR_MACRO(OBJ_DBG_UI);
STR_MACRO(OBJ_MOUSE);
STR_MACRO(OBJ_GRP);
STR_MACRO(OBJ_THINGS);
STR_MACRO(OBJ_EDIT_AREA);
STR_MACRO(OBJ_TILE);
STR_MACRO(OBJ_END);

inline const TCHAR* ObjID_To_Text(OBJID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(OBJ_CLIMABLE_LINE)
		STR_CASE_MACRO(OBJ_NO_CLIMABLE_LINE)
		STR_CASE_MACRO(OBJ_LINE)
		STR_CASE_MACRO(OBJ_PLAYER)
		STR_CASE_MACRO(OBJ_INPUTCONTROLLER)
		STR_CASE_MACRO(OBJ_SPRITE)
		STR_CASE_MACRO(OBJ_BUTTON)
		STR_CASE_MACRO(OBJ_UI)
		STR_CASE_MACRO(OBJ_DBG_UI)
		STR_CASE_MACRO(OBJ_THINGS)
		STR_CASE_MACRO(OBJ_MOUSE)
		STR_CASE_MACRO(OBJ_GRP)
		STR_CASE_MACRO(OBJ_EDIT_AREA)
		STR_CASE_MACRO(OBJ_TILE)
		STR_CASE_MACRO(OBJ_END)
	}
}


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
	TEM_THINGS,
	TEM_GRID_TOGGLE,
	TEM_PICKING_MODE,
	TEM_FILE_SAVE,
	TEM_FILE_LOAD,
	TEM_END
};


STR_MACRO(TEM_LINE);
STR_MACRO(TEM_TILE);
STR_MACRO(TEM_THINGS);
STR_MACRO(TEM_GRID_TOGGLE);
STR_MACRO(TEM_PICKING_MODE);
STR_MACRO(TEM_FILE_SAVE);
STR_MACRO(TEM_FILE_LOAD);
STR_MACRO(TEM_END);

inline const TCHAR* TileEditMode_To_Text(TILE_EDIT_MODE eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(TEM_LINE)
		STR_CASE_MACRO(TEM_TILE)
		STR_CASE_MACRO(TEM_THINGS)
		STR_CASE_MACRO(TEM_GRID_TOGGLE)
		STR_CASE_MACRO(TEM_PICKING_MODE)
		STR_CASE_MACRO(TEM_FILE_SAVE)
		STR_CASE_MACRO(TEM_FILE_LOAD)
		STR_CASE_MACRO(TEM_END)
	}
}


enum THINGS_ID
{
	TGS_PLAYER_POS,
	TGS_MONSTER_A_POS,
	TGS_MONSTER_G_POS,
	TGS_MONSTER_B_POS,
	TGS_BOSS_FIREBIRD_POS,
	TGS_END
};

STR_MACRO(TGS_PLAYER_POS);
STR_MACRO(TGS_MONSTER_A_POS);
STR_MACRO(TGS_MONSTER_G_POS);
STR_MACRO(TGS_MONSTER_B_POS);
STR_MACRO(TGS_BOSS_FIREBIRD_POS);
STR_MACRO(TGS_END);

inline const TCHAR* ThginsId_To_Text(THINGS_ID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(TGS_PLAYER_POS)
		STR_CASE_MACRO(TGS_MONSTER_A_POS)
		STR_CASE_MACRO(TGS_MONSTER_G_POS)
		STR_CASE_MACRO(TGS_MONSTER_B_POS)
		STR_CASE_MACRO(TGS_BOSS_FIREBIRD_POS)
		STR_CASE_MACRO(TGS_END)
	}
}


enum FILE_NAME_ID
{
	FNI_TUTORIAL,
	FNI_ETC,
	FNI_END
};


STR_MACRO(FNI_TUTORIAL);
STR_MACRO(FNI_ETC);
STR_MACRO(FNI_END);

inline const TCHAR* FileNameId_To_Text(FILE_NAME_ID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(FNI_TUTORIAL)
		STR_CASE_MACRO(FNI_ETC);
		STR_CASE_MACRO(FNI_END);
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

STR_MACRO(TILE_START);
STR_MACRO(TILE_END);
STR_MACRO(TILE_TEST_1);
STR_MACRO(TILE_TEST_2);
STR_MACRO(Spr_Prologue_Tileset_1);
STR_MACRO(TILE_ID_END);

inline const TCHAR* Tile_Id_To_Text(TILE_ID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(TILE_START)
		STR_CASE_MACRO(TILE_END)
		STR_CASE_MACRO(TILE_TEST_1)
		STR_CASE_MACRO(TILE_TEST_2)
		STR_CASE_MACRO(Spr_Prologue_Tileset_1)
		STR_CASE_MACRO(TILE_ID_END)
	}
}

inline const TCHAR* Tile_Id_To_FrameKey(TILE_ID eID)
{
	switch (eID)
	{
	case TILE_TEST_1:
	case TILE_TEST_2:
		return STR_FKI_TILE_TEST;
	case Spr_Prologue_Tileset_1:
		return STR_FKI_Spr_Prologue_Tileset;
	case TILE_ID_END:
		return STR_FKI_END;
	}
}

inline const FRAME_KEY_ID Tile_Id_To_FrameKeyId(TILE_ID eID)
{
	switch (eID)
	{
	case TILE_TEST_1:
	case TILE_TEST_2:
		return FKI_TILE_TEST;
	case Spr_Prologue_Tileset_1:
		return FKI_Spr_Prologue_Tileset;
	case TILE_ID_END:
		return FKI_END;
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

STR_MACRO(EMPM_TILE_ORIGIN);
STR_MACRO(EMPM_TILE_SIDE);
STR_MACRO(EMPM_NONE);
STR_MACRO(EMPM_END);

inline const TCHAR* EditMousePickingMode_To_Text(EDIT_MOUSE_PICKING_MODE eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(EMPM_TILE_ORIGIN)
		STR_CASE_MACRO(EMPM_TILE_SIDE)
		STR_CASE_MACRO(EMPM_NONE)
		STR_CASE_MACRO(EMPM_END)
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

STR_MACRO(LINE_START);
STR_MACRO(LINE_END);
STR_MACRO(LINE_CLIMABLE);
STR_MACRO(LINE_NO_CLIMABLE);
STR_MACRO(LINE_ID_END);

inline const TCHAR* LineId_To_Text(LINE_ID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(LINE_START)
		STR_CASE_MACRO(LINE_END)
		STR_CASE_MACRO(LINE_CLIMABLE)
		STR_CASE_MACRO(LINE_NO_CLIMABLE)
		STR_CASE_MACRO(LINE_ID_END)
	}
}


enum LINE_COLL_TYPE
{
	LCT_CLIMABLE,
	LCT_NOCLIMABLE,
	LCT_END
};

