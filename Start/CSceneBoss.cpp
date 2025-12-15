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
#include "CObjPlayer2.h"
#include "CCollisionMgr.h"
#include "CObjBossClusterAim.h"
#include "CObjBossShootExplode.h"
#include "CObjBossBullet.h"
#include "CObjClusterBombExplode.h"
#include "CObjBossBodySlap.h"
#include "CObjBossBodySlapAlert.h"
#include "CObjMonsterFloatingBombHugeExplodeSprite.h"
#include "CObjBossBackHeli.h"
#include "CScrollMgr.h"
#include "CObjSprite.h"
#include "CGameStorageMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CObjGateSprite.h"

CSceneBoss::CSceneBoss()
    :m_pBgBuilding1(nullptr), m_pBgBuilding2(nullptr)
{
    ZeroMemory(m_pBgCloud, sizeof(CObjBgBossCloud*) * 7);
}

CSceneBoss::~CSceneBoss()
{
    Release();
}

void CSceneBoss::Initialize()
{
    CGameStorageMgr::Get_Instance()->Set_BossDeadEnd(false);
    //BOSS_Firebird_Body_Test
    // BOSS_Firebird_Body_Tes_Mask.bmp
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_Firebird_Body_Test.bmp", STR_FKI_Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_Firebird_Body_Tes_Mask.bmp", _T("BODY_MASK"));
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8.bmp", STR_FKI_Spr_BOSS_Firebird_Body_Idle_Sheet_tw688_th352_sw2752_sh704_c8);
    
    //BOSS_FirebirdWing3_Sheet.bmp
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdWing_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdWing_sheet);
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdWing3_Sheet.bmp", STR_FKI_Spr_BOSS_FirebirdWing_sheet);
    
    //BOSS_FirebirdGun_TEST.bmp
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdGun_sheet.bmp", STR_FKI_Spr_BOSS_FirebirdGun_sheet);
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_FirebirdGun_TEST.bmp", STR_FKI_Spr_BOSS_FirebirdGun_sheet);

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

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UnstableKnockbackPlatform_Booster_sheet.bmp", STR_FKI_Spr_UnstableKnockbackPlatform_Booster_sheet);
    
    
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BOSS_Firebird_Body_BodySlapLoop.bmp", STR_FKI_Spr_BOSS_Firebird_Body_BodySlapLoop);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BOSS_BodySlapAlert_sheet.bmp", STR_FKI_Spr_BOSS_BodySlapAlert_sheet);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Spr_BackHeliMove_Loop.bmp", STR_FKI_Spr_BackHeliMove_Loop);
    
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/FireBirdEnd_SHEET.bmp", STR_FKI_FIREBIRD_END_SHEET);


    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_NEW_Sheet.bmp", STR_FKI_Spr_SNB_SHEET_NEW);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SNB_GRAB_SHEET.bmp", STR_FKI_Spr_SNB_GRAB_SHEET);



   // CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PLG.bmp", _T("PLG"));
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RESET.bmp", _T("RESET"));
    //CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TMP.bmp", _T("TMP"));

  /*  CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PLG_BOSS_BODY.bmp", _T("PLG"));
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RESET_BOSS_BODY.bmp", _T("RESET"));*/

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


    

    //CObjMonsterFloatingBomb* pFloatingBomb = new CObjMonsterFloatingBomb;
    //pFloatingBomb->Initialize();
    //pFloatingBomb->Set_Pos((WINCX >> 1) + 150, (WINCY >> 1) - 150);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBomb);

    //CObjMonsterFloatingBombHugeExplodeSprite* pFloatingBombExplode = new CObjMonsterFloatingBombHugeExplodeSprite;
    //pFloatingBombExplode->Initialize();
    //pFloatingBombExplode->Set_Pos((WINCX >> 1) + 250, (WINCY >> 1) - 150);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pFloatingBombExplode);

    //CObjBossClusterAim* pBossClusterAim = new CObjBossClusterAim;
    //pBossClusterAim->Initialize();
    //pBossClusterAim->Set_Pos(WINCX >> 1, (WINCY >> 1) - 200);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBossClusterAim);



    //CObjBossBullet* pBossBullet = new CObjBossBullet;
    //pBossBullet->Set_Option(1);
    //pBossBullet->Initialize();
    //pBossBullet->Set_Pos((WINCX >> 1) + 100, (WINCY >> 1) - 200);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBossBullet);

    //CObjBossBodySlap* pBossBodySlap = new CObjBossBodySlap;
    //pBossBodySlap->Initialize();
    //pBossBodySlap->Set_Pos(WINCX >> 1, (WINCY >> 1) - 200);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBossBodySlap);

    //CObjBossBodySlapAlert* pAlert = new CObjBossBodySlapAlert;
    //pAlert->Initialize();
    //pAlert->Set_Pos(WINCX >> 1, WINCY >> 1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pAlert);

    //CObjBossBackHeli* pBackHeli = new CObjBossBackHeli;
    //pBackHeli->Initialize();
    //pBackHeli->Set_Pos((WINCX >> 1) + 200, (WINCY >> 1) + 200);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pBackHeli);

    {
        // 맵의 좌우 끝과 끝은 (WINCX >> 1) - 224 * 6, (WINCX >> 1) + 224 * 6
        // 으로 일단 생각


        CObjUnstableKnockbackPlatformA* pPlatform1 = new CObjUnstableKnockbackPlatformA;
        pPlatform1->Initialize();
        pPlatform1->Set_Pos((WINCX >> 1) - 224 * 4, (WINCY >> 1));
        pPlatform1->Set_Combackpos(pPlatform1->Get_Info()->fX, pPlatform1->Get_Info()->fY);
        //TODO: OBJ_PLATFORM
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform1);
        m_pPlatform[0] = pPlatform1;

        CObjUnstableKnockbackPlatformA* pPlatform2 = new CObjUnstableKnockbackPlatformA;
        pPlatform2->Initialize();
        pPlatform2->Set_Pos((WINCX >> 1) - 224 * 2, (WINCY >> 1) + 112 * 2);
        pPlatform2->Set_Combackpos(pPlatform2->Get_Info()->fX, pPlatform2->Get_Info()->fY);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform2);
        m_pPlatform[1] = pPlatform2;

        CObjUnstableKnockbackPlatformA* pPlatform3 = new CObjUnstableKnockbackPlatformA;
        pPlatform3->Initialize();
        pPlatform3->Set_Pos((WINCX >> 1) - 224 * 2, (WINCY >> 1) - 112 * 2);
        pPlatform3->Set_Combackpos(pPlatform3->Get_Info()->fX, pPlatform3->Get_Info()->fY);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform3);
        m_pPlatform[2] = pPlatform3;

        CObjUnstableKnockbackPlatformA* pPlatform4 = new CObjUnstableKnockbackPlatformA;
        pPlatform4->Initialize();
        pPlatform4->Set_Pos((WINCX >> 1) , (WINCY >> 1));
        pPlatform4->Set_Combackpos(pPlatform4->Get_Info()->fX, pPlatform4->Get_Info()->fY);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform4);
        m_pPlatform[3] = pPlatform4;

        CObjUnstableKnockbackPlatformA* pPlatform5 = new CObjUnstableKnockbackPlatformA;
        pPlatform5->Initialize();
        pPlatform5->Set_Pos((WINCX >> 1) + 224 * 2, (WINCY >> 1) + 112 * 2);
        pPlatform5->Set_Combackpos(pPlatform5->Get_Info()->fX, pPlatform5->Get_Info()->fY);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform5);
        m_pPlatform[4] = pPlatform5;

        CObjUnstableKnockbackPlatformA* pPlatform6 = new CObjUnstableKnockbackPlatformA;
        pPlatform6->Initialize();
        pPlatform6->Set_Pos((WINCX >> 1) + 224 * 2, (WINCY >> 1) - 112 * 2);
        pPlatform6->Set_Combackpos(pPlatform6->Get_Info()->fX, pPlatform6->Get_Info()->fY);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform6);
        m_pPlatform[5] = pPlatform6;

        CObjUnstableKnockbackPlatformA* pPlatform7 = new CObjUnstableKnockbackPlatformA;
        pPlatform7->Initialize();
        pPlatform7->Set_Pos((WINCX >> 1) + 224 * 4, (WINCY >> 1) );
        pPlatform7->Set_Combackpos(pPlatform7->Get_Info()->fX, pPlatform7->Get_Info()->fY);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLATFORM, pPlatform7);
        m_pPlatform[6] = pPlatform7;
    }


    CObjPlayer2* pPlayer = new CObjPlayer2;
    pPlayer->Initialize();
    pPlayer->Set_Pos((WINCX >> 1) , (WINCY >> 1) - 250);
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);



    //BGM_Chap4_Main_Intro.wav

    CSoundMgr::Get_Instance()->PlayBGM(_T("BGM_Chap4_Main_Intro.wav"), 1.f);
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

  
    if (CGameStorageMgr::Get_Instance()->Get_BossDeadEnd())
    {
        CGameStorageMgr::Get_Instance()->Set_Chap3Clear(true);



        dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateClose();

        CTimeMgr::Get_Instance()->Set_Timer([=]() {
            CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
            }, 1000);

        CTimeMgr::Get_Instance()->Set_Timer([=]() {
            dynamic_cast<CObjGateSprite*>(CObjMgr::Get_Instance()->Get_ObjectList(OBJ_GATE)->front())->GateOpen();
            }, 1500);
    }
    
    return 0;
}

void CSceneBoss::Late_Update()
{
    CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_RECT));
    CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLATFORM));
    
    
    CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_BULLET), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLATFORM));
   
    // TODO OBJ_BOSS만들어서 대체
    CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER));

    CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER));

    //  플로팅밤 튕기기
    CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_MONSTER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLATFORM));


    CCollisionMgr::Collision_Rect(*CObjMgr::Get_Instance()->Get_ObjectList(OBJ_PLAYER), *CObjMgr::Get_Instance()->Get_ObjectList(OBJ_BULLET));
    CObjMgr::Get_Instance()->Late_Update();
}

void CSceneBoss::Render(HDC hDC)
{
    CObjMgr::Get_Instance()->Render(hDC);
}

void CSceneBoss::Release()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
    CObjMgr::Get_Instance()->Dead_ID_Except({ OBJ_MOUSE, OBJ_GATE });
    CScrollMgr::Get_Instance()->Scroll_Reset();
}
