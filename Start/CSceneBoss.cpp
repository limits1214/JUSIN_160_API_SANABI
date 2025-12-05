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
#include "CObjPlayer.h"
#include "CCollisionMgr.h"

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
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdWing_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdWing_sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdGun_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdGun_sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdBomber_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdBomber_sheet);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FloatingBombExplodeHude_Sheet_tw512_th512.bmp", STR_FKI_Spr_MOB_FLTBOMB_FloatingBombExplodeHude_Sheet_tw512_th512);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_FloatingBombSheet_th150_tw150.bmp", STR_FKI_Spr_MOB_FLTBOMB_SHEET_th150_tw150);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mat_Chap5_Heli_Sky.bmp", STR_FKI_Spr_BG_Mat_Chap5_Heli_Sky);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_Chap5_Chap4_Building.bmp", STR_FKI_Spr_Chap5_Chap4_Building);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UnstableKnockbackPlatformA_Sheet.bmp", STR_FKI_Spr_UNSTABLE_KNOCKBACK_PLATFORM_A_SHEET);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Sprsht_Chap5_Heli_Cloud_Sheet.bmp", STR_FKI_Spr_Chap5_Heli_Cloud_Sheet);

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_ClusterBombExplode_Sheet.bmp", STR_FKI_Spr_BOSS_ClusterBombExplode_Sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_ClusterBulletExplode_Sheet.bmp", STR_FKI_Spr_BOSS_ClusterBulletExplode_Sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_Firebird_ShootExplode_Sheet.bmp", STR_FKI_Spr_BOSS_ShootExplode_Sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdBullet_Sheet.bmp", STR_FKI_Spr_BOSS_Bullet_Sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdClusterAim_Sheet.bmp", STR_FKI_Spr_BOSS_Cluster_Aim_Sheet);
    
    CObjBg* pBg = new CObjBg;
    pBg->Initialize();
    pBg->Set_FrameKeyId(FKI_Spr_BG_Mat_Chap5_Heli_Sky);
    pBg->Set_Pos(WINCX >> 1, 220);
    pBg->Set_CX(832);
    pBg->Set_CY(448);
    //pBg->Set_UseMainScroll(true);
    CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBg);

    for (int i = 0; i < 7; ++i)
    {
        CObjBgBossCloud* pBgCloud = new CObjBgBossCloud;
        pBgCloud->Initialize();
        pBgCloud->Set_Pos(rand() % WINCX, rand() % (WINCY / 2));
        pBgCloud->Set_Option(i);
        CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBgCloud);
        m_pBgCloud[i] = pBgCloud;
    }

    CObjBgBossBuilding* pBsBuilding1 = new CObjBgBossBuilding;
    pBsBuilding1->Initialize();
    pBsBuilding1->Set_Pos((1580 / 2), (WINCY >> 1) + 5);
    pBsBuilding1->Set_CX(1580);
    pBsBuilding1->Set_CY(1280);
    CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBsBuilding1);
    m_pBgBuilding1 = pBsBuilding1;

    CObjBgBossBuilding* pBsBuilding2 = new CObjBgBossBuilding;
    pBsBuilding2->Initialize();
    pBsBuilding2->Set_Pos((1580 / 2) + 1580, (WINCY >> 1) + 5);
    pBsBuilding2->Set_CX(1580);
    pBsBuilding2->Set_CY(1280);
    CObjMgr::Get_Instance()->Add_Object(OBJ_BG, pBsBuilding2);
    m_pBgBuilding2 = pBsBuilding2;

    CObjBossFireBird* pBoss = new CObjBossFireBird;
    pBoss->Initialize();
    pBoss->Set_Pos(WINCX >> 1, (WINCY >> 1) - 300);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBoss);

    {
        CObjUnstableKnockbackPlatformA* pPlatform1 = new CObjUnstableKnockbackPlatformA;
        pPlatform1->Initialize();
        pPlatform1->Set_Pos((WINCX >> 1) - 224 * 4, (WINCY >> 1));
        //TODO: OBJ_PLATFORM
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform1);

        CObjUnstableKnockbackPlatformA* pPlatform2 = new CObjUnstableKnockbackPlatformA;
        pPlatform2->Initialize();
        pPlatform2->Set_Pos((WINCX >> 1) - 224 * 2, (WINCY >> 1) + 112 * 2);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform2);

        CObjUnstableKnockbackPlatformA* pPlatform3 = new CObjUnstableKnockbackPlatformA;
        pPlatform3->Initialize();
        pPlatform3->Set_Pos((WINCX >> 1) - 224 * 2, (WINCY >> 1) - 112 * 2);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform3);

        CObjUnstableKnockbackPlatformA* pPlatform4 = new CObjUnstableKnockbackPlatformA;
        pPlatform4->Initialize();
        pPlatform4->Set_Pos((WINCX >> 1) , (WINCY >> 1));
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform4);

        CObjUnstableKnockbackPlatformA* pPlatform5 = new CObjUnstableKnockbackPlatformA;
        pPlatform5->Initialize();
        pPlatform5->Set_Pos((WINCX >> 1) + 224 * 2, (WINCY >> 1) + 112 * 2);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform5);

        CObjUnstableKnockbackPlatformA* pPlatform6 = new CObjUnstableKnockbackPlatformA;
        pPlatform6->Initialize();
        pPlatform6->Set_Pos((WINCX >> 1) + 224 * 2, (WINCY >> 1) - 112 * 2);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform6);

        CObjUnstableKnockbackPlatformA* pPlatform7 = new CObjUnstableKnockbackPlatformA;
        pPlatform7->Initialize();
        pPlatform7->Set_Pos((WINCX >> 1) + 224 * 4, (WINCY >> 1) );
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform7);
    }


    CObjPlayer* pPlayer = new CObjPlayer;
    pPlayer->Initialize();
    pPlayer->Set_Pos((WINCX >> 1) , (WINCY >> 1) - 100);
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
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
    CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
    CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLATFORM));

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
