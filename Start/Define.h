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

#define GRAVITY 9.81f

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


enum DIRECTION
{
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_V,
	DIR_H,
	DIR_ID_END
} ;

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
	COLL_RECT,
	COLL_RECT_EX,
	COLL_END
};

enum FRAME_KEY_ID
{
	FKI_TILE_TEST,
	FKI_Spr_Prologue_Tileset,
	FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60,
	FKI_UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6,
	FKI_TEST_BTN_START,
	FKI_TEST_BTN_EDIT,
	FKI_TEST_BTN_EXIT,
	FKI_SNB,
	FKI_END
};

STR_MACRO2(FKI_TILE_TEST, "TILE_TEST");
STR_MACRO2(FKI_Spr_Prologue_Tileset, "Spr_Prologue_Tileset");
STR_MACRO2(FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60, "Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60");
STR_MACRO2(FKI_UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6, "UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6");
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
	case FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60:
		return STR_FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60;
	case FKI_UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6:
		return STR_FKI_UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6;
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

enum FRAME_STATE_ID
{
	FSI_SNB_IDLE,
	FSI_SNB_RUNNING,
	FSI_SNB_JUMP,

	FSI_UI_CHAPTER1_BTN_SELECT,
	FSI_UI_CHAPTER1_BTN_UN_SELECT,
	FSI_UI_CHAPTER2_BTN_SELECT,
	FSI_UI_CHAPTER2_BTN_UN_SELECT,
	FSI_UI_CHAPTER3_BTN_SELECT,
	FSI_UI_CHAPTER3_BTN_UN_SELECT,
	FSI_UI_CHAPTER_BTN_LOCKED,


	FSI_END
};

inline FRAME FrameStateId_To_Frame(FRAME_STATE_ID eID, DWORD dwNow)
{
	
#define FRAME_STATE_CASE_MACRO(A, B, C, D, E) case A: return {B, C, D, E, dwNow};
	//int iStart;
	//int iEnd;
	//int iMotion;
	//DWORD dwSpeed;
	//DWORD dwTime;

	switch (eID)
	{
	FRAME_STATE_CASE_MACRO(FSI_SNB_IDLE,					0, 7, 4, 200)
	FRAME_STATE_CASE_MACRO(FSI_SNB_RUNNING,					0, 19, 3, 80)
	FRAME_STATE_CASE_MACRO(FSI_SNB_JUMP,					0, 5, 2, 200)

	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER1_BTN_SELECT,		0, 0, 0, 0)
	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER1_BTN_UN_SELECT,	1, 1, 0, 0)
	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER2_BTN_SELECT,		2, 2, 0, 0)
	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER2_BTN_UN_SELECT,	3, 3, 0, 0)
	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER3_BTN_SELECT,		4, 4, 0, 0)
	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER3_BTN_UN_SELECT,	5, 5, 0, 0)
	FRAME_STATE_CASE_MACRO(FSI_UI_CHAPTER_BTN_LOCKED,		0, 0, 0, 0)

	case FSI_END:return { 0, 0, 0, 0, 0 };
	}
}


enum SCENEID
{
	SC_LOGO,
	SC_MENU,
	SC_LAB,
	SC_TUTORIAL,
	SC_TILEEIDT,
	SC_BOSS,
	SC_STAGE,
	SC_TEST_UI,
	SC_END
};


STR_MACRO(SC_LOGO);
STR_MACRO(SC_MENU);
STR_MACRO(SC_STAGE);
STR_MACRO(SC_BOSS);
STR_MACRO(SC_TEST_UI);
STR_MACRO(SC_TUTORIAL);
STR_MACRO(SC_TILEEIDT);
STR_MACRO(SC_LAB);
STR_MACRO(SC_END);

inline const TCHAR* SceneID_To_Text(SCENEID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(SC_LOGO)
		STR_CASE_MACRO(SC_MENU)
		STR_CASE_MACRO(SC_STAGE)
		STR_CASE_MACRO(SC_BOSS)
		STR_CASE_MACRO(SC_TEST_UI)
		STR_CASE_MACRO(SC_TUTORIAL)
		STR_CASE_MACRO(SC_TILEEIDT)
		STR_CASE_MACRO(SC_LAB)
		STR_CASE_MACRO(SC_END)
	}
}


enum OBJID
{
	OBJ_GRP,
	OBJ_LINE,
	OBJ_RECT,
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
STR_MACRO(OBJ_RECT);
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
		STR_CASE_MACRO(OBJ_RECT)
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
	TEM_RECT,
	TEM_THINGS,
	TEM_GRID_TOGGLE,
	TEM_PICKING_MODE,
	TEM_FILE_SAVE,
	TEM_FILE_LOAD,
	TEM_CLEAR_ALL,
	TEM_RUN,
	TEM_END
};


STR_MACRO(TEM_LINE);
STR_MACRO(TEM_TILE);
STR_MACRO(TEM_RECT);
STR_MACRO(TEM_THINGS);
STR_MACRO(TEM_GRID_TOGGLE);
STR_MACRO(TEM_PICKING_MODE);
STR_MACRO(TEM_FILE_SAVE);
STR_MACRO(TEM_FILE_LOAD);
STR_MACRO(TEM_CLEAR_ALL);
STR_MACRO(TEM_RUN);
STR_MACRO(TEM_END);

inline const TCHAR* TileEditMode_To_Text(TILE_EDIT_MODE eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(TEM_LINE)
		STR_CASE_MACRO(TEM_TILE)
		STR_CASE_MACRO(TEM_RECT)
		STR_CASE_MACRO(TEM_THINGS)
		STR_CASE_MACRO(TEM_GRID_TOGGLE)
		STR_CASE_MACRO(TEM_PICKING_MODE)
		STR_CASE_MACRO(TEM_FILE_SAVE)
		STR_CASE_MACRO(TEM_FILE_LOAD)
		STR_CASE_MACRO(TEM_CLEAR_ALL)
		STR_CASE_MACRO(TEM_RUN)
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


	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58,
	TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59,

	TGS_UI_Chapter1_Btn,
	TGS_UI_Chapter2_Btn,
	TGS_UI_Chapter3_Btn,

	TGS_END
};

STR_MACRO(TGS_PLAYER_POS);
STR_MACRO(TGS_MONSTER_A_POS);
STR_MACRO(TGS_MONSTER_G_POS);
STR_MACRO(TGS_MONSTER_B_POS);
STR_MACRO(TGS_BOSS_FIREBIRD_POS);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58);
STR_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59);
STR_MACRO(TGS_UI_Chapter1_Btn);
STR_MACRO(TGS_UI_Chapter2_Btn);
STR_MACRO(TGS_UI_Chapter3_Btn);
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

			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58)
			STR_CASE_MACRO(TGS_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59)

			STR_CASE_MACRO(TGS_UI_Chapter1_Btn)
			STR_CASE_MACRO(TGS_UI_Chapter2_Btn)
			STR_CASE_MACRO(TGS_UI_Chapter3_Btn)

		STR_CASE_MACRO(TGS_END)
	}
}


enum FILE_NAME_ID
{
	FNI_MENU,
	FNI_TUTORIAL,
	FNI_LAB1_LINECOLL,
	FNI_ETC,
	FNI_END
};

STR_MACRO(FNI_MENU);
STR_MACRO(FNI_TUTORIAL);
STR_MACRO(FNI_LAB1_LINECOLL);
STR_MACRO(FNI_ETC);
STR_MACRO(FNI_END);

inline const TCHAR* FileNameId_To_Text(FILE_NAME_ID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(FNI_MENU)
		STR_CASE_MACRO(FNI_TUTORIAL)
		STR_CASE_MACRO(FNI_LAB1_LINECOLL);
		STR_CASE_MACRO(FNI_ETC);
		STR_CASE_MACRO(FNI_END);
	}
}

/*
Spr_Prologue_Tileset: 64 * 224, 가로 4 세로 14,  56개
*/


enum TILE_ID
{
	TILE_START,
	TILE_END,
	//TILE_TEST_1,
	//TILE_TEST_2,
	Spr_Prologue_Tileset_0,
	Spr_Prologue_Tileset_1,
	Spr_Prologue_Tileset_2,
	Spr_Prologue_Tileset_3,
	Spr_Prologue_Tileset_4,
	Spr_Prologue_Tileset_5,
	Spr_Prologue_Tileset_6,
	Spr_Prologue_Tileset_7,
	Spr_Prologue_Tileset_8,
	Spr_Prologue_Tileset_9,
	Spr_Prologue_Tileset_10,
	Spr_Prologue_Tileset_11,
	Spr_Prologue_Tileset_12,
	Spr_Prologue_Tileset_13,
	Spr_Prologue_Tileset_14,
	Spr_Prologue_Tileset_15,
	Spr_Prologue_Tileset_16,
	Spr_Prologue_Tileset_17,
	Spr_Prologue_Tileset_18,
	Spr_Prologue_Tileset_19,
	Spr_Prologue_Tileset_20,
	Spr_Prologue_Tileset_21,
	Spr_Prologue_Tileset_22,
	Spr_Prologue_Tileset_23,
	Spr_Prologue_Tileset_24,
	Spr_Prologue_Tileset_25,
	Spr_Prologue_Tileset_26,
	Spr_Prologue_Tileset_27,
	Spr_Prologue_Tileset_28,
	Spr_Prologue_Tileset_29,
	Spr_Prologue_Tileset_30,
	Spr_Prologue_Tileset_31,
	Spr_Prologue_Tileset_32,
	Spr_Prologue_Tileset_33,
	Spr_Prologue_Tileset_34,
	Spr_Prologue_Tileset_35,
	Spr_Prologue_Tileset_36,
	Spr_Prologue_Tileset_37,
	Spr_Prologue_Tileset_38,
	Spr_Prologue_Tileset_39,
	Spr_Prologue_Tileset_40,
	Spr_Prologue_Tileset_41,
	Spr_Prologue_Tileset_42,
	Spr_Prologue_Tileset_43,
	Spr_Prologue_Tileset_44,
	Spr_Prologue_Tileset_45,
	Spr_Prologue_Tileset_46,
	Spr_Prologue_Tileset_47,
	Spr_Prologue_Tileset_48,
	Spr_Prologue_Tileset_49,
	Spr_Prologue_Tileset_50,
	Spr_Prologue_Tileset_51,
	Spr_Prologue_Tileset_52,
	Spr_Prologue_Tileset_53,
	Spr_Prologue_Tileset_54,
	Spr_Prologue_Tileset_55,
	
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58,
	Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59,

	TILE_ID_END
};

STR_MACRO(TILE_START);
STR_MACRO(TILE_END);
//STR_MACRO(TILE_TEST_1);
//STR_MACRO(TILE_TEST_2);
STR_MACRO(Spr_Prologue_Tileset_0);
STR_MACRO(Spr_Prologue_Tileset_1);
STR_MACRO(Spr_Prologue_Tileset_2);
STR_MACRO(Spr_Prologue_Tileset_3);
STR_MACRO(Spr_Prologue_Tileset_4);
STR_MACRO(Spr_Prologue_Tileset_5);
STR_MACRO(Spr_Prologue_Tileset_6);
STR_MACRO(Spr_Prologue_Tileset_7);
STR_MACRO(Spr_Prologue_Tileset_8);
STR_MACRO(Spr_Prologue_Tileset_9);
STR_MACRO(Spr_Prologue_Tileset_10);
STR_MACRO(Spr_Prologue_Tileset_11);
STR_MACRO(Spr_Prologue_Tileset_12);
STR_MACRO(Spr_Prologue_Tileset_13);
STR_MACRO(Spr_Prologue_Tileset_14);
STR_MACRO(Spr_Prologue_Tileset_15);
STR_MACRO(Spr_Prologue_Tileset_16);
STR_MACRO(Spr_Prologue_Tileset_17);
STR_MACRO(Spr_Prologue_Tileset_18);
STR_MACRO(Spr_Prologue_Tileset_19);
STR_MACRO(Spr_Prologue_Tileset_20);
STR_MACRO(Spr_Prologue_Tileset_21);
STR_MACRO(Spr_Prologue_Tileset_22);
STR_MACRO(Spr_Prologue_Tileset_23);
STR_MACRO(Spr_Prologue_Tileset_24);
STR_MACRO(Spr_Prologue_Tileset_25);
STR_MACRO(Spr_Prologue_Tileset_26);
STR_MACRO(Spr_Prologue_Tileset_27);
STR_MACRO(Spr_Prologue_Tileset_28);
STR_MACRO(Spr_Prologue_Tileset_29);
STR_MACRO(Spr_Prologue_Tileset_30);
STR_MACRO(Spr_Prologue_Tileset_31);
STR_MACRO(Spr_Prologue_Tileset_32);
STR_MACRO(Spr_Prologue_Tileset_33);
STR_MACRO(Spr_Prologue_Tileset_34);
STR_MACRO(Spr_Prologue_Tileset_35);
STR_MACRO(Spr_Prologue_Tileset_36);
STR_MACRO(Spr_Prologue_Tileset_37);
STR_MACRO(Spr_Prologue_Tileset_38);
STR_MACRO(Spr_Prologue_Tileset_39);
STR_MACRO(Spr_Prologue_Tileset_40);
STR_MACRO(Spr_Prologue_Tileset_41);
STR_MACRO(Spr_Prologue_Tileset_42);
STR_MACRO(Spr_Prologue_Tileset_43);
STR_MACRO(Spr_Prologue_Tileset_44);
STR_MACRO(Spr_Prologue_Tileset_45);
STR_MACRO(Spr_Prologue_Tileset_46);
STR_MACRO(Spr_Prologue_Tileset_47);
STR_MACRO(Spr_Prologue_Tileset_48);
STR_MACRO(Spr_Prologue_Tileset_49);
STR_MACRO(Spr_Prologue_Tileset_50);
STR_MACRO(Spr_Prologue_Tileset_51);
STR_MACRO(Spr_Prologue_Tileset_52);
STR_MACRO(Spr_Prologue_Tileset_53);
STR_MACRO(Spr_Prologue_Tileset_54);
STR_MACRO(Spr_Prologue_Tileset_55);

STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58);
STR_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59);

STR_MACRO(TILE_ID_END);

inline const TCHAR* Tile_Id_To_Text(TILE_ID eID)
{
	switch (eID)
	{
			STR_CASE_MACRO(TILE_START)
			STR_CASE_MACRO(TILE_END)
			//STR_CASE_MACRO(TILE_TEST_1)
			//STR_CASE_MACRO(TILE_TEST_2)
			STR_CASE_MACRO(Spr_Prologue_Tileset_0)
			STR_CASE_MACRO(Spr_Prologue_Tileset_1)
			STR_CASE_MACRO(Spr_Prologue_Tileset_2)
			STR_CASE_MACRO(Spr_Prologue_Tileset_3)
			STR_CASE_MACRO(Spr_Prologue_Tileset_4)
			STR_CASE_MACRO(Spr_Prologue_Tileset_5)
			STR_CASE_MACRO(Spr_Prologue_Tileset_6)
			STR_CASE_MACRO(Spr_Prologue_Tileset_7)
			STR_CASE_MACRO(Spr_Prologue_Tileset_8)
			STR_CASE_MACRO(Spr_Prologue_Tileset_9)
			STR_CASE_MACRO(Spr_Prologue_Tileset_10)
			STR_CASE_MACRO(Spr_Prologue_Tileset_11)
			STR_CASE_MACRO(Spr_Prologue_Tileset_12)
			STR_CASE_MACRO(Spr_Prologue_Tileset_13)
			STR_CASE_MACRO(Spr_Prologue_Tileset_14)
			STR_CASE_MACRO(Spr_Prologue_Tileset_15)
			STR_CASE_MACRO(Spr_Prologue_Tileset_16)
			STR_CASE_MACRO(Spr_Prologue_Tileset_17)
			STR_CASE_MACRO(Spr_Prologue_Tileset_18)
			STR_CASE_MACRO(Spr_Prologue_Tileset_19)
			STR_CASE_MACRO(Spr_Prologue_Tileset_20)
			STR_CASE_MACRO(Spr_Prologue_Tileset_21)
			STR_CASE_MACRO(Spr_Prologue_Tileset_22)
			STR_CASE_MACRO(Spr_Prologue_Tileset_23)
			STR_CASE_MACRO(Spr_Prologue_Tileset_24)
			STR_CASE_MACRO(Spr_Prologue_Tileset_25)
			STR_CASE_MACRO(Spr_Prologue_Tileset_26)
			STR_CASE_MACRO(Spr_Prologue_Tileset_27)
			STR_CASE_MACRO(Spr_Prologue_Tileset_28)
			STR_CASE_MACRO(Spr_Prologue_Tileset_29)
			STR_CASE_MACRO(Spr_Prologue_Tileset_30)
			STR_CASE_MACRO(Spr_Prologue_Tileset_31)
			STR_CASE_MACRO(Spr_Prologue_Tileset_32)
			STR_CASE_MACRO(Spr_Prologue_Tileset_33)
			STR_CASE_MACRO(Spr_Prologue_Tileset_34)
			STR_CASE_MACRO(Spr_Prologue_Tileset_35)
			STR_CASE_MACRO(Spr_Prologue_Tileset_36)
			STR_CASE_MACRO(Spr_Prologue_Tileset_37)
			STR_CASE_MACRO(Spr_Prologue_Tileset_38)
			STR_CASE_MACRO(Spr_Prologue_Tileset_39)
			STR_CASE_MACRO(Spr_Prologue_Tileset_40)
			STR_CASE_MACRO(Spr_Prologue_Tileset_41)
			STR_CASE_MACRO(Spr_Prologue_Tileset_42)
			STR_CASE_MACRO(Spr_Prologue_Tileset_43)
			STR_CASE_MACRO(Spr_Prologue_Tileset_44)
			STR_CASE_MACRO(Spr_Prologue_Tileset_45)
			STR_CASE_MACRO(Spr_Prologue_Tileset_46)
			STR_CASE_MACRO(Spr_Prologue_Tileset_47)
			STR_CASE_MACRO(Spr_Prologue_Tileset_48)
			STR_CASE_MACRO(Spr_Prologue_Tileset_49)
			STR_CASE_MACRO(Spr_Prologue_Tileset_50)
			STR_CASE_MACRO(Spr_Prologue_Tileset_51)
			STR_CASE_MACRO(Spr_Prologue_Tileset_52)
			STR_CASE_MACRO(Spr_Prologue_Tileset_53)
			STR_CASE_MACRO(Spr_Prologue_Tileset_54)
			STR_CASE_MACRO(Spr_Prologue_Tileset_55)

			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58);
			STR_CASE_MACRO(Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59);


		STR_CASE_MACRO(TILE_ID_END)
	}
}

inline const TCHAR* Tile_Id_To_FrameKey(TILE_ID eID)
{
	switch (eID)
	{
	//case TILE_TEST_1:
	//case TILE_TEST_2:
	//	return STR_FKI_TILE_TEST;
	case Spr_Prologue_Tileset_0:
	case Spr_Prologue_Tileset_1:
	case Spr_Prologue_Tileset_2:
	case Spr_Prologue_Tileset_3:
	case Spr_Prologue_Tileset_4:
	case Spr_Prologue_Tileset_5:
	case Spr_Prologue_Tileset_6:
	case Spr_Prologue_Tileset_7:
	case Spr_Prologue_Tileset_8:
	case Spr_Prologue_Tileset_9:
	case Spr_Prologue_Tileset_10:
	case Spr_Prologue_Tileset_11:
	case Spr_Prologue_Tileset_12:
	case Spr_Prologue_Tileset_13:
	case Spr_Prologue_Tileset_14:
	case Spr_Prologue_Tileset_15:
	case Spr_Prologue_Tileset_16:
	case Spr_Prologue_Tileset_17:
	case Spr_Prologue_Tileset_18:
	case Spr_Prologue_Tileset_19:
	case Spr_Prologue_Tileset_20:
	case Spr_Prologue_Tileset_21:
	case Spr_Prologue_Tileset_22:
	case Spr_Prologue_Tileset_23:
	case Spr_Prologue_Tileset_24:
	case Spr_Prologue_Tileset_25:
	case Spr_Prologue_Tileset_26:
	case Spr_Prologue_Tileset_27:
	case Spr_Prologue_Tileset_28:
	case Spr_Prologue_Tileset_29:
	case Spr_Prologue_Tileset_30:
	case Spr_Prologue_Tileset_31:
	case Spr_Prologue_Tileset_32:
	case Spr_Prologue_Tileset_33:
	case Spr_Prologue_Tileset_34:
	case Spr_Prologue_Tileset_35:
	case Spr_Prologue_Tileset_36:
	case Spr_Prologue_Tileset_37:
	case Spr_Prologue_Tileset_38:
	case Spr_Prologue_Tileset_39:
	case Spr_Prologue_Tileset_40:
	case Spr_Prologue_Tileset_41:
	case Spr_Prologue_Tileset_42:
	case Spr_Prologue_Tileset_43:
	case Spr_Prologue_Tileset_44:
	case Spr_Prologue_Tileset_45:
	case Spr_Prologue_Tileset_46:
	case Spr_Prologue_Tileset_47:
	case Spr_Prologue_Tileset_48:
	case Spr_Prologue_Tileset_49:
	case Spr_Prologue_Tileset_50:
	case Spr_Prologue_Tileset_51:
	case Spr_Prologue_Tileset_52:
	case Spr_Prologue_Tileset_53:
	case Spr_Prologue_Tileset_54:
	case Spr_Prologue_Tileset_55:
		return STR_FKI_Spr_Prologue_Tileset;

	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59:
		return STR_FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60;

	case TILE_ID_END:
		return STR_FKI_END;
	}
}

inline const FRAME_KEY_ID Tile_Id_To_FrameKeyId(TILE_ID eID)
{
	switch (eID)
	{
	//case TILE_TEST_1:
	//case TILE_TEST_2:
	//	return FKI_TILE_TEST;
	case Spr_Prologue_Tileset_0:
	case Spr_Prologue_Tileset_1:
	case Spr_Prologue_Tileset_2:
	case Spr_Prologue_Tileset_3:
	case Spr_Prologue_Tileset_4:
	case Spr_Prologue_Tileset_5:
	case Spr_Prologue_Tileset_6:
	case Spr_Prologue_Tileset_7:
	case Spr_Prologue_Tileset_8:
	case Spr_Prologue_Tileset_9:
	case Spr_Prologue_Tileset_10:
	case Spr_Prologue_Tileset_11:
	case Spr_Prologue_Tileset_12:
	case Spr_Prologue_Tileset_13:
	case Spr_Prologue_Tileset_14:
	case Spr_Prologue_Tileset_15:
	case Spr_Prologue_Tileset_16:
	case Spr_Prologue_Tileset_17:
	case Spr_Prologue_Tileset_18:
	case Spr_Prologue_Tileset_19:
	case Spr_Prologue_Tileset_20:
	case Spr_Prologue_Tileset_21:
	case Spr_Prologue_Tileset_22:
	case Spr_Prologue_Tileset_23:
	case Spr_Prologue_Tileset_24:
	case Spr_Prologue_Tileset_25:
	case Spr_Prologue_Tileset_26:
	case Spr_Prologue_Tileset_27:
	case Spr_Prologue_Tileset_28:
	case Spr_Prologue_Tileset_29:
	case Spr_Prologue_Tileset_30:
	case Spr_Prologue_Tileset_31:
	case Spr_Prologue_Tileset_32:
	case Spr_Prologue_Tileset_33:
	case Spr_Prologue_Tileset_34:
	case Spr_Prologue_Tileset_35:
	case Spr_Prologue_Tileset_36:
	case Spr_Prologue_Tileset_37:
	case Spr_Prologue_Tileset_38:
	case Spr_Prologue_Tileset_39:
	case Spr_Prologue_Tileset_40:
	case Spr_Prologue_Tileset_41:
	case Spr_Prologue_Tileset_42:
	case Spr_Prologue_Tileset_43:
	case Spr_Prologue_Tileset_44:
	case Spr_Prologue_Tileset_45:
	case Spr_Prologue_Tileset_46:
	case Spr_Prologue_Tileset_47:
	case Spr_Prologue_Tileset_48:
	case Spr_Prologue_Tileset_49:
	case Spr_Prologue_Tileset_50:
	case Spr_Prologue_Tileset_51:
	case Spr_Prologue_Tileset_52:
	case Spr_Prologue_Tileset_53:
	case Spr_Prologue_Tileset_54:
	case Spr_Prologue_Tileset_55:
		return FKI_Spr_Prologue_Tileset;

	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58:
	case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59:
		return FKI_Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60;

	case TILE_ID_END:
		return FKI_END;
	}
}

typedef struct tagTileInfo
{
	int iX, iY;
	int iCX, iCY;
} TILE_INFO;

inline TILE_INFO Tile_Id_To_TileInfo(TILE_ID eID)
{
	switch (eID)
	{
		//case TILE_TEST_1: return {0, 0, 64, 64};
		//case TILE_TEST_2: return { 1, 0, 64, 64 };
		case Spr_Prologue_Tileset_0: return  { 0, 0, 16, 16 };
		case Spr_Prologue_Tileset_1: return  { 1, 0, 16, 16 };
		case Spr_Prologue_Tileset_2: return  { 2, 0, 16, 16 };
		case Spr_Prologue_Tileset_3: return  { 3, 0, 16, 16 };
		case Spr_Prologue_Tileset_4: return  { 0, 1, 16, 16 };
		case Spr_Prologue_Tileset_5: return  { 1, 1, 16, 16 };
		case Spr_Prologue_Tileset_6: return  { 2, 1, 16, 16 };
		case Spr_Prologue_Tileset_7: return  { 3, 1, 16, 16 };
		case Spr_Prologue_Tileset_8: return  { 0, 2, 16, 16 };
		case Spr_Prologue_Tileset_9: return  { 1, 2, 16, 16 };
		case Spr_Prologue_Tileset_10: return { 2, 2, 16, 16 };
		case Spr_Prologue_Tileset_11: return { 3, 2, 16, 16 };
		case Spr_Prologue_Tileset_12: return { 0, 3, 16, 16 };
		case Spr_Prologue_Tileset_13: return { 1, 3, 16, 16 };
		case Spr_Prologue_Tileset_14: return { 2, 3, 16, 16 };
		case Spr_Prologue_Tileset_15: return { 3, 3, 16, 16 };
		case Spr_Prologue_Tileset_16: return { 0, 4, 16, 16 };
		case Spr_Prologue_Tileset_17: return { 1, 4, 16, 16 };
		case Spr_Prologue_Tileset_18: return { 2, 4, 16, 16 };
		case Spr_Prologue_Tileset_19: return { 3, 4, 16, 16 };
		case Spr_Prologue_Tileset_20: return { 0, 5, 16, 16 };
		case Spr_Prologue_Tileset_21: return { 1, 5, 16, 16 };
		case Spr_Prologue_Tileset_22: return { 2, 5, 16, 16 };
		case Spr_Prologue_Tileset_23: return { 3, 5, 16, 16 };
		case Spr_Prologue_Tileset_24: return { 0, 6, 16, 16 };
		case Spr_Prologue_Tileset_25: return { 1, 6, 16, 16 };
		case Spr_Prologue_Tileset_26: return { 2, 6, 16, 16 };
		case Spr_Prologue_Tileset_27: return { 3, 6, 16, 16 };
		case Spr_Prologue_Tileset_28: return { 0, 7, 16, 16 };
		case Spr_Prologue_Tileset_29: return { 1, 7, 16, 16 };
		case Spr_Prologue_Tileset_30: return { 2, 7, 16, 16 };
		case Spr_Prologue_Tileset_31: return { 3, 7, 16, 16 };
		case Spr_Prologue_Tileset_32: return { 0, 8, 16, 16 };
		case Spr_Prologue_Tileset_33: return { 1, 8, 16, 16 };
		case Spr_Prologue_Tileset_34: return { 2, 8, 16, 16 };
		case Spr_Prologue_Tileset_35: return { 3, 8, 16, 16 };
		case Spr_Prologue_Tileset_36: return { 0, 9, 16, 16 };
		case Spr_Prologue_Tileset_37: return { 1, 9, 16, 16 };
		case Spr_Prologue_Tileset_38: return { 2, 9, 16, 16 };
		case Spr_Prologue_Tileset_39: return { 3, 9, 16, 16 };
		case Spr_Prologue_Tileset_40: return { 0, 10, 16, 16 };
		case Spr_Prologue_Tileset_41: return { 1, 10, 16, 16 };
		case Spr_Prologue_Tileset_42: return { 2, 10, 16, 16 };
		case Spr_Prologue_Tileset_43: return { 3, 10, 16, 16 };
		case Spr_Prologue_Tileset_44: return { 0, 11, 16, 16 };
		case Spr_Prologue_Tileset_45: return { 1, 11, 16, 16 };
		case Spr_Prologue_Tileset_46: return { 2, 11, 16, 16 };
		case Spr_Prologue_Tileset_47: return { 3, 11, 16, 16 };
		case Spr_Prologue_Tileset_48: return { 0, 12, 16, 16 };
		case Spr_Prologue_Tileset_49: return { 1, 12, 16, 16 };
		case Spr_Prologue_Tileset_50: return { 2, 12, 16, 16 };
		case Spr_Prologue_Tileset_51: return { 3, 12, 16, 16 };
		case Spr_Prologue_Tileset_52: return { 0, 13, 16, 16 };
		case Spr_Prologue_Tileset_53: return { 1, 13, 16, 16 };
		case Spr_Prologue_Tileset_54: return { 2, 13, 16, 16 };
		case Spr_Prologue_Tileset_55: return { 3, 13, 16, 16 };

		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_0: return  { 0, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_1: return  { 1, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_2: return  { 2, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_3: return  { 3, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_4: return  { 4, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_5: return  { 5, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_6: return  { 6, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_7: return  { 7, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_8: return  { 8, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_9: return  { 9, 0, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_10: return { 0, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_11: return { 1, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_12: return { 2, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_13: return { 3, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_14: return { 4, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_15: return { 5, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_16: return { 6, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_17: return { 7, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_18: return { 8, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_19: return { 9, 1, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_20: return { 0, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_21: return { 1, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_22: return { 2, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_23: return { 3, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_24: return { 4, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_25: return { 5, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_26: return { 6, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_27: return { 7, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_28: return { 8, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_29: return { 9, 2, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_30: return { 0, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_31: return { 1, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_32: return { 2, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_33: return { 3, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_34: return { 4, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_35: return { 5, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_36: return { 6, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_37: return { 7, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_38: return { 8, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_39: return { 9, 3, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_40: return { 0, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_41: return { 1, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_42: return { 2, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_43: return { 3, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_44: return { 4, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_45: return { 5, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_46: return { 6, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_47: return { 7, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_48: return { 8, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_49: return { 9, 4, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_50: return { 0, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_51: return { 1, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_52: return { 2, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_53: return { 3, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_54: return { 4, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_55: return { 5, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_56: return { 6, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_57: return { 7, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_58: return { 8, 5, 10, 32 };
		case Spr_Prop_Forest_Sheet1_tw10_th32_sw160_sh192_c60_59: return { 9, 5, 10, 32 };


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

enum EDIT_RECT_ID
{
	ERI_START,
	ERI_STOP,
	ERI_CLIMABLE,
	ERI_NO_CLIMABLE,
	ERI_END
};

STR_MACRO(ERI_START);
STR_MACRO(ERI_STOP);
STR_MACRO(ERI_CLIMABLE);
STR_MACRO(ERI_NO_CLIMABLE);
STR_MACRO(ERI_END);

inline const TCHAR* EditRectId_To_Text(EDIT_RECT_ID eID)
{
	switch (eID)
	{
		STR_CASE_MACRO(ERI_START)
		STR_CASE_MACRO(ERI_STOP)
		STR_CASE_MACRO(ERI_CLIMABLE)
		STR_CASE_MACRO(ERI_NO_CLIMABLE)
		STR_CASE_MACRO(ERI_END)
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

