#include "pch.h"
#include "CObjGameUiChapterBtn.h"
#include "CBmpMgr.h"
#include "CTimeMgr.h"
#include "CObjMouse.h"
#include "CSceneMgr.h"
#include "CGameStorageMgr.h"
#include "CObjGateSprite.h"
#include "CObjMgr.h"
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
    m_tInfo.fCX = 182;
    m_tInfo.fCY = 239;
    DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
    m_tFrame = FrameStateId_To_Frame(FSI_UIBUTTON_LOCKED, dwNow);

}

int CObjGameUiChapterBtn::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    
    if (m_eCurState == FSI_END)
    {
        DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
      
        //if (m_iOption == 0)
        //{
        //    m_ePreState = m_eCurState;
        //    m_eCurState = FSI_UIBUTTON_C1_NOSELECT;
        //    m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        //}
        //else if (m_iOption == 1)
        //{
        //    m_ePreState = m_eCurState;
        //    m_eCurState = FSI_UIBUTTON_C2_NOSELECT;
        //    m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        //}
        //else if (m_iOption == 2)
        //{
        //    m_ePreState = m_eCurState;
        //    m_eCurState = FSI_UIBUTTON_C3_NOSELECT;
        //    m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        //}
        if (m_iOption == 3)
        {
            
        }

    }
    Move_Frame();

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CObjGameUiChapterBtn::Late_Update()
{
    Motion_Change();
}

void CObjGameUiChapterBtn::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(STR_FKI_UIBUTTON_SHEET);
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
        if (m_eCurState == FSI_UIBUTTON_LOCKED)
        {
            return;
        }
        POINT ptCurr = pMouse->Get_Pt_Curr();
        if (PtInRect(&m_tRect, ptCurr))
        {
            if (m_iOption == 0)
            {
                
                dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateClose();

                CTimeMgr::Get_Instance()->Set_Timer([=]() {
                    CSceneMgr::Get_Instance()->Scene_Change(SC_TUTORIAL);
                    }, 1000);

                CTimeMgr::Get_Instance()->Set_Timer([=]() {
                    dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateOpen();
                    }, 1500);
               
                //CSceneMgr::Get_Instance()->Scene_Change(SC_MONSTER);
            }
            else if (m_iOption == 1)
            {
                //CSceneMgr::Get_Instance()->Scene_Change(SC_TILEEIDT);
                //CSceneMgr::Get_Instance()->Scene_Change(SC_MONSTER);

                dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateClose();

                CTimeMgr::Get_Instance()->Set_Timer([=]() {
                    CSceneMgr::Get_Instance()->Scene_Change(SC_MONSTER);
                    }, 1000);

                CTimeMgr::Get_Instance()->Set_Timer([=]() {
                    dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateOpen();
                    }, 1500);
            }
            else if (m_iOption == 2)
            {
                //CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);

                dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateClose();

                CTimeMgr::Get_Instance()->Set_Timer([=]() {
                    CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
                    }, 1000);

                CTimeMgr::Get_Instance()->Set_Timer([=]() {
                    dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateOpen();
                    }, 1500);
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
        DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
        bool bC1Clear = CGameStorageMgr::Get_Instance()->IsChap1Clear();
        bool bC2Clear = CGameStorageMgr::Get_Instance()->IsChap2Clear();
        if (PtInRect(&m_tRect, ptCurr))
        {
            if (m_iOption == 0)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UIBUTTON_C1_SELECT;
                //m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
            else if (m_iOption == 1)
            {
                if (bC1Clear)
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_C2_SELECT;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
                else
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_LOCKED;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
            }
            else if (m_iOption == 2)
            {
                if (bC2Clear)
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_C3_SELECT;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
                else
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_LOCKED;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
            }

           
        }
        else
        {
           
            if (m_iOption == 0)
            {
                m_ePreState = m_eCurState;
                m_eCurState = FSI_UIBUTTON_C1_NOSELECT;
                //m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
            }
            else if (m_iOption == 1)
            {
                if (bC1Clear)
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_C2_NOSELECT;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
                else
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_LOCKED;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
            }
            else if (m_iOption == 2)
            {
                if (bC2Clear)
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_C3_NOSELECT;
                    //m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
                else
                {
                    m_ePreState = m_eCurState;
                    m_eCurState = FSI_UIBUTTON_LOCKED;
                   // m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
                }
            }
        }
    }
}
void CObjGameUiChapterBtn::Motion_Change()
{
    DWORD dwNow = CTimeMgr::Get_Instance()->Get_Tick_Count();
    if (m_ePreState != m_eCurState)
    {
        m_tFrame = FrameStateId_To_Frame(m_eCurState, dwNow);
        m_ePreState = m_eCurState;
    }
}
