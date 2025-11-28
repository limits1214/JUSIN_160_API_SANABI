#include "pch.h"
#include "CSceneMgr.h"
#include "CSceneLogo.h"
#include "CSceneMenu.h"
#include "CSceneStage.h"
#include "CSceneTestUI.h"
#include "CSceneTutorial.h"
#include "CSceneTileEdit.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_LOGO), m_bSkip(false)
{

}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CSceneLogo;
			break;
		case SC_MENU:
			m_pScene = new CSceneMenu;
			break;
		case SC_STAGE:
			m_pScene = new CSceneStage;
			break;
		case SC_TEST_UI:
			m_pScene = new CSceneTestUI;
			break;
		case SC_TUTORIAL:
			m_pScene = new CSceneTutorial;
			break;
		case SC_TILEEIDT:
			m_pScene = new CSceneTileEdit;
			break;
		}


		// 여기서 이니셜라이즈 하지말자
		// 왜냐면 씬체인지는 업데이트 시점에서 일어나는데
		// 다른 씬의 이니셜라이즈에 오브젝트매니저에 뭔가 넣는 작업이 존재한다면
		// 현재 업데이트중이기때문에 불필요한 업데이트가 발생해버릴수 있다.
		// 그러니 명확히 분리하기위해 이니셜라이즈는 씬전환 플래그 이후에 실행하도록 하자
		//m_pScene->Initialize();

		m_ePreScene = m_eCurScene;

		// initialize 이후 업데이트가 씹힐수 있으니
		// 한프레임 스킵해준다.
		// 마지막단계인 렌더에서 스킵해제한다.
		m_bSkip = true;
	}
}

void  CSceneMgr::Update()
{
	if (!m_bSkip)
		m_pScene->Update();
}

void  CSceneMgr::Late_Update()
{
	if (!m_bSkip)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if(!m_bSkip)
		m_pScene->Render(hDC);

	if (m_bSkip)
	{
		m_bSkip = false;
		m_pScene->Initialize();
	}

	
}

void  CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}