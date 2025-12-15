#include "pch.h"
#include "CObjMonsterWarrior.h"
#include "CObjMonsterWarriorSprite.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CObjPlayer2.h"
#include "CSoundMgr.h"

CObjMonsterWarrior::CObjMonsterWarrior()
{
}

CObjMonsterWarrior::~CObjMonsterWarrior()
{
	Release();
}

void CObjMonsterWarrior::Initialize()
{
	Set_UseMainScroll(true);
	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;

	m_bExcuted = false;
	m_bAirMonster = true;

	m_eAniState = AST_RIGHT_SPAWN_START;

	CObjMonsterWarriorSprite* pSprite = new CObjMonsterWarriorSprite;
	pSprite->Initialize();
	pSprite->Set_Parent(this);
	pSprite->Set_Pos(0, 0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pSprite);


	m_dwTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	m_fLemnisDeltaSum = 0;
	m_bOriginSet = false;

	m_bTracing = true;

	m_bHovering = false;

	m_bGrabbed = false;

	CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_SPAWN_WARNING);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_Chap2_SpawnWarning.wav", SOUND_SFX_SPAWN_WARNING, 1.f);
}

int CObjMonsterWarrior::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eAniState == AST_RIGHT_DEAD_END)
	{
		Set_Dead_Cascade();
	}

	if (m_eAniState == AST_RIGHT_SPAWN_START
		|| m_eAniState == AST_RIGHT_SPAWN_ING
		|| m_eAniState == AST_RIGHT_SPAWN_END
		||
		m_eAniState == AST_LEFT_SPAWN_START
		|| m_eAniState == AST_LEFT_SPAWN_ING
		|| m_eAniState == AST_LEFT_SPAWN_END
		||
		m_eAniState == AST_RIGHT_DEAD_START
		|| m_eAniState == AST_RIGHT_DEAD_ING
		||
		m_eAniState == AST_RIGHT_EXCHOLDSTART_START
		|| m_eAniState == AST_RIGHT_EXCHOLDSTART_ING
		|| m_eAniState == AST_RIGHT_EXCHOLDSTART_END
		||
		m_eAniState == AST_LEFT_EXCHOLDSTART_START
		|| m_eAniState == AST_LEFT_EXCHOLDSTART_ING
		|| m_eAniState == AST_LEFT_EXCHOLDSTART_END
		||
		m_eAniState == AST_RIGHT_EXCHOLDBACK_START
		|| m_eAniState == AST_RIGHT_EXCHOLDBACK_ING
		|| m_eAniState == AST_RIGHT_EXCHOLDBACK_END
		||
		m_eAniState == AST_LEFT_EXCHOLDBACK_START
		|| m_eAniState == AST_LEFT_EXCHOLDBACK_ING
		|| m_eAniState == AST_LEFT_EXCHOLDBACK_END
		)
	{
		return OBJ_NOEVENT;
	}

	if (!m_bOriginSet)
	{
		m_bOriginSet = true;
		m_fOriginX = m_tInfo.fX;
		m_fOriginY = m_tInfo.fY;
	}

	DeltaUpdate();
	CObjPlayer2* pPlayer = nullptr;
	if (m_pTarget != nullptr)
	{
		CObjPlayer2* _pPlayer = dynamic_cast<CObjPlayer2*>(m_pTarget);
		if (_pPlayer != nullptr)
		{
			pPlayer = _pPlayer;
		}
	}

	float traceX = 0;
	float traceY = 0;
	if (pPlayer != nullptr)
	{
		auto playerX = pPlayer->Get_Info()->fX;
		auto playerY = pPlayer->Get_Info()->fY;

		auto len = 1.f;

		auto tmpWidth = playerX - m_fOriginX;
		auto tmpHeight = (playerY - 40) - m_fOriginY;

		auto distance = sqrtf(tmpWidth * tmpWidth + tmpHeight * tmpHeight);

		// 쫒을때는 Min 까지
		float fTracingMinLen = 50;
		// 호버링중에는 Max까지 견딤
		float fTracingMaxLen = 200;

		if (m_bHovering)
		{
			if (distance > fTracingMaxLen)
			{
				auto rad = atan2f(tmpHeight, tmpWidth);
				traceX = cosf(rad) * len;
				traceY = sinf(rad) * len;

				m_bTracing = true;
				m_bHovering = false;
			}
			else
			{
			}
		}
		else
		{
			if (distance > fTracingMinLen)
			{
				auto rad = atan2f(tmpHeight, tmpWidth);
				traceX = cosf(rad) * len;
				traceY = sinf(rad) * len;

				m_bTracing = true;
				m_bHovering = false;
			}
			else
			{
				m_bTracing = false;
				m_bHovering = true;
			}
		}

		auto isRight = tmpWidth > 0;

		if (m_bTracing)
		{
			if (isRight)
			{
				if (m_eAniState == AST_LEFT_MOVING_ING)
				{
					m_eAniState = AST_RIGHT_MOVING_START;
				}
				else if (
					!(m_eAniState == AST_RIGHT_MOVESTART_START
						|| m_eAniState == AST_RIGHT_MOVESTART_ING
						|| m_eAniState == AST_RIGHT_MOVESTART_END
						||
						m_eAniState == AST_RIGHT_MOVING_START
						|| m_eAniState == AST_RIGHT_MOVING_ING
						|| m_eAniState == AST_RIGHT_MOVING_END)
					)
				{
					m_eAniState = AST_RIGHT_MOVESTART_START;
				}
			}
			else
			{
				if (m_eAniState == AST_RIGHT_MOVING_ING)
				{
					m_eAniState = AST_LEFT_MOVING_START;
				}
				else if (
					!(m_eAniState == AST_LEFT_MOVESTART_START
						|| m_eAniState == AST_LEFT_MOVESTART_ING
						|| m_eAniState == AST_LEFT_MOVESTART_END
						||
						m_eAniState == AST_LEFT_MOVING_START
						|| m_eAniState == AST_LEFT_MOVING_ING
						|| m_eAniState == AST_LEFT_MOVING_END)
					)
				{
					m_eAniState = AST_LEFT_MOVESTART_START;
				}
			}
		}
		else if (m_bHovering)
		{
			if (isRight)
			{
				if (
					!(m_eAniState == AST_RIGHT_ATTACKREADY_START
						|| m_eAniState == AST_RIGHT_ATTACKREADY_ING
						|| m_eAniState == AST_RIGHT_ATTACKREADY_END
						||
						m_eAniState == AST_RIGHT_ATTACK_START
						|| m_eAniState == AST_RIGHT_ATTACK_ING
						|| m_eAniState == AST_RIGHT_ATTACK_END)
					)
				{
					m_eAniState = AST_RIGHT_ATTACKREADY_START;
					//Sfx_Chap2_Warrior_Slash.wav
					CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_WARRIOR_SLASH);
					CSoundMgr::Get_Instance()->PlaySound(L"Sfx_Chap2_Warrior_Slash.wav", SOUND_SFX_WARRIOR_SLASH, 1.f);
				}
			}
			else
			{
				
				if (
					!(m_eAniState == AST_LEFT_ATTACKREADY_START
						|| m_eAniState == AST_LEFT_ATTACKREADY_ING
						|| m_eAniState == AST_LEFT_ATTACKREADY_END
						||
						m_eAniState == AST_LEFT_ATTACK_START
						|| m_eAniState == AST_LEFT_ATTACK_ING
						|| m_eAniState == AST_LEFT_ATTACK_END)
					)
				{
					m_eAniState = AST_LEFT_ATTACKREADY_START;

					CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_WARRIOR_SLASH);
					CSoundMgr::Get_Instance()->PlaySound(L"Sfx_Chap2_Warrior_Slash.wav", SOUND_SFX_WARRIOR_SLASH, 1.f);
				}
			}
		}


		// 좌우
		if (isRight)
		{
			if (m_bHovering)
			{
					
			}
			else
			{
				if (m_eAniState != AST_RIGHT_MOVING_ING)
				{
					//m_eAniState = AST_RIGHT_MOVESTART_START;
				}
			}

		}
		else
		{

			if (m_bHovering)
			{
					
			}
			else
			{
				if (m_eAniState != AST_LEFT_MOVING_ING)
				{
					//m_eAniState = AST_LEFT_MOVESTART_START;
				}
			}

		}




		if (m_eAniState == AST_LEFT_ATTACK_ING || m_eAniState == AST_RIGHT_ATTACK_ING)
		{
			if (distance < 150)
			{
				pPlayer->Damage();
			}
		}
	}

	float lemnisX = 0;
	float lemnisY = 0;

	float a = 20;
	float t = m_fLemnisDeltaSum;
	lemnisX = a * cosf(t) / (1.0f + sinf(t) * sinf(t));
	lemnisY = a * sinf(t) * cosf(t) / (1.0f + sinf(t) * sinf(t));


	m_fOriginX += traceX;
	m_fOriginY += traceY;


	if (!m_bGrabbed)
	{
		m_tInfo.fX = m_fOriginX + lemnisX + traceX;
		m_tInfo.fY = m_fOriginY + lemnisY + traceY;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CObjMonsterWarrior::Late_Update()
{
}

void CObjMonsterWarrior::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CObjMonsterWarrior::Release()
{
}

void CObjMonsterWarrior::On_Collision(CObj* pObj, COLLISIONID eCollID, void*)
{
}

void CObjMonsterWarrior::Excuted(CObj* pPlayer, float fRad)
{
	m_bExcuted = true;
	m_eAniState = AST_RIGHT_DEAD_START;
	//CObjExplosionSprite* pExplosionSprite = new CObjExplosionSprite;
	//pExplosionSprite->Set_Option(0);
	//pExplosionSprite->Initialize();
	//pExplosionSprite->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pExplosionSprite);


	//SFX_EventWarrior_Explosion.wav
	CSoundMgr::Get_Instance()->StopSound(SOUND_SFX_ENE_WARRIOR_EXPLOSION);
	CSoundMgr::Get_Instance()->PlaySound(L"SFX_EventWarrior_Explosion.wav", SOUND_SFX_ENE_WARRIOR_EXPLOSION, 1.f);
}

void CObjMonsterWarrior::Grabbed(CObj* pPlayer)
{
	m_eAniState = AST_RIGHT_EXCHOLDSTART_START;
	m_bGrabbed = true;
}

void CObjMonsterWarrior::DeltaUpdate()
{
	DWORD dwNowTime = CTimeMgr::Get_Instance()->Get_Tick_Count();
	float dwDelta = (float)(dwNowTime - m_dwTime) / 1000.f;
	m_dwTime = dwNowTime;

	m_fLemnisDeltaSum += dwDelta;
}