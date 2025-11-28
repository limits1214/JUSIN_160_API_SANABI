#pragma once
#include "CScene.h"
class CSceneMgr
{
public:
	void Scene_Change(SCENEID eID);
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

private:
	CScene* m_pScene;
	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;
	bool m_bSkip;

// SINGLETON
private:
	CSceneMgr();
	CSceneMgr& operator=(CSceneMgr&) = delete;
	CSceneMgr(const CSceneMgr&) = delete;
	~CSceneMgr();

public:
	static CSceneMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
};

