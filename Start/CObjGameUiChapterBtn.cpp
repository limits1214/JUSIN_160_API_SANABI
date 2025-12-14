#include "pch.h"
#include "CObjGameUiChapterBtn.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMouse.h"
#include "CSceneMgr.h"

CObjGameUiChapterBtn::CObjGameUiChapterBtn()
    : m_iOption(0), m_ePreState(FSI_END), m_eCurState(FSI_END)
{
  //  Set_DbgName(_T("CObjGameUiChapterBtn"));
}

CObjGameUiChapterBtn::~CObjGameUiChapterBtn()
{
    Release();
}

void CObjGameUiChapterBtn::Initialize()
{
    //CBmpMgr::Get_Instance()->Insert_Bmp(_T(""), )
    m_tInfo.fCX = 186;
    m_tInfo.fCY = 243;

}

int CObjGameUiChapterBtn::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    
    if (m_eCurState == FSI_END)
    {
        DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
      
        if (m_iOption == 0)
        {
            m_ePreState = m_eCurState;
            m_eCurState = FSI_UI_CHAPTER1_BTN_UN_SELECT;
            m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        }
        else if (m_iOption == 1)
        {
            m_ePreState = m_eCurState;
            m_eCurState = FSI_UI_CHAPTER2_BTN_UN_SELECT;
            m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        }
        else if (m_iOption == 2)
        {
            m_ePreState = m_eCurState;
            m_eCurState = FSI_UI_CHAPTER3_BTN_UN_SELECT;
            m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        }

    }
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CObjGameUiChapterBtn::Late_Update()
{
}

void CObjGameUiChapterBtn::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(STR_FKI_UI_ChapterSelect_Sheet_tw186_th243_sw1116_sh243_c6);
    BmpRender(
        hDC,
        m_tRect.left, m_tRect.top,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        hMemDC,
        m_tFrame.iStart * (int)m_tInfo.fCX, m_tFrame.iMotion * (int)m_tInfo.fCY,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY
    );
}

void CObjGameUiChapterBtn::Release()
{
   
}

void CObjGameUiChapterBtn::On_Mouse_Key_Down(CObj* pObj)
{
    CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
    if (pMouse != nullptr)
    {
        POINT ptCurr = pMouse->Get_Pt_Curr();
        if (PtInRect(&m_tRect, ptCurr))
        {
            if (m_iOption == 0)
            {
                CSceneMgr::Get_Instance()->Scene_Change(SC_LAB);
                //CSceneMgr::Get_Instance()->Scene_Change(SC_TUTORIAL);
                //CSceneMgr::Get_Instance()->Scene_Change(SC_MONSTER);
            }
            else if (m_iOption == 1)
            {
                CSceneMgr::Get_Instance()->Scene_Change(SC_TILEEIDT);
            }
            else if (m_iOption == 2)
            {
                CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
            }
            pMouse->Mouse_PreventEvent();
        }
    }
}

void CObjGameUiChapterBtn::On_Mouse_Key_Up(CObj* pMouse)
{
}

void CObjGameUiChapterBtn::On_Mouse_Key_Pressing(CObj* pMouse)
{
}

void CObjGameUiChapterBtn::On_Mouse_Pos(CObj* pObj)
{
    CObjMouse* pMouse = dynamic_cast<CObjMouse*>(pObj);
    if (pMouse != nullptr)
    {
        POINT ptCurr = pMouse->Get_Pt_Curr();
        if (PtInRect(&m_tRect, ptCurr))
        {
            DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
            if (m_iOption == 0)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UI_CHAPTER1_BTN_SELECT;
                m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
            else if (m_iOption == 1)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UI_CHAPTER2_BTN_SELECT;
                m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
            else if (m_iOption == 2)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UI_CHAPTER3_BTN_SELECT;
                m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
        }
        else
        {
            DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
            if (m_iOption == 0)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UI_CHAPTER1_BTN_UN_SELECT;
                m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
            else if (m_iOption == 1)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UI_CHAPTER2_BTN_UN_SELECT;
                m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
            else if (m_iOption == 2)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UI_CHAPTER3_BTN_UN_SELECT;
                m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
        }
    }
}
