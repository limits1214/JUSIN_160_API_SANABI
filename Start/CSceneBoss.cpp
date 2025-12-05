#include "pch.h"
#include "CSceneBoss.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CObjBossFireBird.h"
#include "CObjBossFireBirdWing.h"
#include "CObjBg.h"
#include "CObjMonsterFloatingBomb.h"

#include "CObjUnstableKnockbackPlatformA.h"

#include "CObjBgBossBuilding.h"

#include "CObjBgBossCloud.h"

CSceneBoss::CSceneBoss()
    :m_pBgBuilding1(nullptr), m_pBgBuilding2(nullptr)
{
    ZeroMemory(m_pBgCloud, sizeof(CObjBgBossCloud*) * 7);
}

CSceneBoss::~CSceneBoss()
{
}

void CSceneBoss::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8.bmp", STR_FKI_Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8);
    /*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Gun_ShootEnd_Sheet_tw408_th58_sw11016_sh58_c27.bmp", STR_FKI_Spr_BOSS_Firebird_Gun_ShootEnd_Sheet_tw408_th58_sw11016_sh58_c27);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Gun_ShootLoop_Sheet_tw429_th82_sw1716_sh82_c4.bmp", STR_FKI_Spr_BOSS_Firebird_Gun_ShootLoop_Sheet_tw429_th82_sw1716_sh82_c4);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Gun_ShootReadyLoop_Sheet_tw408_th57_sw1632_sh57_c4.bmp", STR_FKI_Spr_BOSS_Firebird_Gun_ShootReadyLoop_Sheet_tw408_th57_sw1632_sh57_c4);*/
    /*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Wing_DownLoop01_Sheet_tw1308_th134_sw5232_sh268_c8.bmp", STR_FKI_Spr_BOSS_Firebird_Wing_DownLoop01_Sheet_tw1308_th134_sw5232_sh268_c8);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Wing_NeuLoop_Sheet_tw1308_th156_sw5232_sh312_c8.bmp", STR_FKI_Spr_BOSS_Firebird_Wing_NeuLoop_Sheet_tw1308_th156_sw5232_sh312_c8);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Wing_UpLoop01_Sheet_tw1308_th169_sw_5232_sh338_c8.bmp", STR_FKI_Spr_BOSS_Firebird_Wing_UpLoop01_Sheet_tw1308_th169_sw_5232_sh338_c8);*/
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdWing_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdWing_sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdGun_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdGun_sheet);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mat_Chap5_Heli_Sky.bmp", STR_FKI_Spr_BG_Mat_Chap5_Heli_Sky);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Chap5_Chap4_Building.bmp", STR_FKI_Spr_Chap5_Chap4_Building);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UnstableKnockbackPlatformA_Sheet.bmp", STR_FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sprsht_Chap5_Heli_Cloud_Sheet.bmp", STR_FKI_Spr_Chap5_Heli_Cloud_Sheet);
    
    CObjBg* pBg = new CObjBg;
    pBg->Initialize();
    pBg->Set_FrameKeyId(FKI_Spr_BG_Mat_Chap5_Heli_Sky);
    pBg->Set_Pos(WINCX >> 1, 220);
    pBg->Set_CX(832);
    pBg->Set_CY(448);
    //pBg->Set_UseMainScroll(true);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBg);

    for (int i = 0; i < 7; ++i)
    {
        CObjBgBossCloud* pBgCloud = new CObjBgBossCloud;
        pBgCloud->Initialize();
        pBgCloud->Set_Pos(rand() % WINCX, rand() % (WINCY / 2));
        pBgCloud->Set_Option(i);
        CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBgCloud);
        m_pBgCloud[i] = pBgCloud;
    }

    CObjBgBossBuilding* pBsBuilding1 = new CObjBgBossBuilding;
    pBsBuilding1->Initialize();
    pBsBuilding1->Set_Pos((1580 / 2), (WINCY >> 1) + 5);
    pBsBuilding1->Set_CX(1580);
    pBsBuilding1->Set_CY(1280);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBsBuilding1);
    m_pBgBuilding1 = pBsBuilding1;


    CObjBgBossBuilding* pBsBuilding2 = new CObjBgBossBuilding;
    pBsBuilding2->Initialize();
    pBsBuilding2->Set_Pos((1580 / 2) + 1580, (WINCY >> 1) + 5);
    pBsBuilding2->Set_CX(1580);
    pBsBuilding2->Set_CY(1280);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBsBuilding2);
    m_pBgBuilding2 = pBsBuilding2;



    CObjBossFireBird* pBoss = new CObjBossFireBird;
    pBoss->Initialize();
    pBoss->Set_Pos(WINCX >> 1, WINCY >> 1);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBoss);

    CObjMonsterFloatingBomb* pFltBomb = new CObjMonsterFloatingBomb;
    pFltBomb->Initialize();
    pFltBomb->Set_Pos(WINCX >> 1, WINCY >> 1);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFltBomb);

    CObjUnstableKnockbackPlatformA* pPlatform = new CObjUnstableKnockbackPlatformA;
    pPlatform->Initialize();
    pPlatform->Set_Pos(WINCX >> 1, (WINCY >> 1) + 200);
    //TODO: OBJ_PLATFORM
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pPlatform);

    CObjUnstableKnockbackPlatformA* pPlatform2 = new CObjUnstableKnockbackPlatformA;
    pPlatform2->Initialize();
    pPlatform2->Set_Pos((WINCX >> 1) + 260, (WINCY >> 1) + 200);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pPlatform2);

    CObjUnstableKnockbackPlatformA* pPlatform3 = new CObjUnstableKnockbackPlatformA;
    pPlatform3->Initialize();
    pPlatform3->Set_Pos((WINCX >> 1) - 260, (WINCY >> 1) + 200);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pPlatform3);


    
}

int CSceneBoss::Update()
{
    CObjMgr::Get_Instance()->Update();
    m_pBgBuilding1->Set_PosX(-1.f);
    m_pBgBuilding2->Set_PosX(-1.f);

    auto building1Rect = m_pBgBuilding1->Get_Rect();
    auto building2Rect = m_pBgBuilding2->Get_Rect();

    if (building1Rect->left <= -1580)
    {
        m_pBgBuilding1->Set_PosX((1580 ) + 1580);
       auto tmp = m_pBgBuilding1;
       m_pBgBuilding1 = m_pBgBuilding2;
       m_pBgBuilding2 = tmp;
    }


    for (int i = 0; i < 7; ++i)
    {
        m_pBgCloud[i]->Set_PosX(-0.5f);
        auto cloudRect = m_pBgCloud[i]->Get_Rect();
        if (cloudRect->right <= 0)
        {
            m_pBgCloud[i]->Set_PosX(WINCX + 200);
        }
    }
    
    return 0;
}

void CSceneBoss::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CSceneBoss::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneBoss::Release()
{
    CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE });
}
