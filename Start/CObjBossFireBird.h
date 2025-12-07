#pragma once
#include "CObj.h"
#include "CObjBossClusterAim.h"
class CObjBossFireBird: public CObj
{
public:
	CObjBossFireBird();
	virtual ~CObjBossFireBird();

public:
	void Set_PlayerState(FRAME_STATE_ID eState)
	{
		m_eCurState = eState;
	}

	float Get_Angle()
	{
		return m_fAngle;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Motion_Change();
	void Test_Key_Input();

	void State_Update();
	void Move(float fAngle, float fSpeed);

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

private:
	float m_fAngle;

private:
	float m_fPlayerFollowAngle;
	DWORD m_dwBombingIntervalDelay1;
	DWORD m_dwBombingEndDelay;
	bool m_bBombingStart;

	DWORD m_dwShootingEndDelay;

	CObjBossClusterAim* m_pClusterAim;
	float m_fClusterAimSpeed;

	DWORD m_dwBodySlapAlertDelay;
	bool m_bShowBodySlapAlert;
	DWORD m_dwBodySlapEndDelay;
	float m_fBodySlapPlayerX;
	float m_fBodySlapPlayerY;

	bool m_bClusterAimTrace;
	DWORD m_dwClusterTraceOneDelay;
	DWORD m_dwClusterBombShootOneDelay;
	DWORD m_dwClusterShootEndDelay;

	bool m_bBossHideToDown;

public:
	
	/*
		IDLE: 평상시, 아무것도 안보임
		폭탄창 개방시
		OPENSTART 스테이트 줌
		OPENSTART를 받고 스테이트 OPENING 으로 전화
		OPENING 상태에서는 프레임 애니메이션 OPENING 재생
		OPENING 재생 끝나면 STATE OPENEND로 전환
		OPENEND 받으면 IDLE로 전환
	*/
	enum ANI_STATE_BOMBER
	{
		IDLE,
		OPENSTART,
		OPENING,
		OPENEND,
		OPENKEEP,
		CLOSESTART,
		CLOSING,
		CLOSEEND,
	};
	ANI_STATE_BOMBER m_eAniStateBomber;

	enum ANI_STATE_GUN
	{
		GUN_IDLE,

		GUNSHOOTSTART_START,
		GUNSHOOTSTART_ING,
		GUNSHOOTSTART_END,

		GUNSHOOTREADYLOOP_START,
		GUNSHOOTREADYLOOP_ING,
		GUNSHOOTREADYLOOP_END,

		GUNSHOOTLOOP_START,
		GUNSHOOTLOOP_ING,
		GUNSHOOTLOOP_END,

		GUNSHOOTLOOP_KEEP,

		GUNSHOOTEND_START,
		GUNSHOOTEND_ING,
		GUNSHOOTEND_END,
	};
	ANI_STATE_GUN m_eAniStateGun;

	enum ANI_STATE_BROKEN
	{
		NORMAL,
		BROKEN
	};
	ANI_STATE_BROKEN m_eAniStateBroken;

	enum ANI_STATE_WING
	{
		NEU,
		NEU_TO_UP_START,
		NEU_TO_UP_ING,
		NEU_TO_UP_END,
		UP_KEEP,
		UP_TO_NEU_START,
		UP_TO_NEU_ING,
		UP_TO_NEU_END,
		NEU_TO_DOWN_START,
		NEU_TO_DOWN_ING,
		NEU_TO_DOWN_END,
		DOWN_KEEP,
		DOWN_TO_NEU_START,
		DOWN_TO_NEU_ING,
		DOWN_TO_NEU_END,
	};
	ANI_STATE_WING m_eAniStateWing;


	enum STATE
	{
		ENTER_START,
		ENTER_ING,
		ENTER_END,

		PLAYER_FOLLOW_START,
		PLAYER_FOLLOW_ING,
		PLAYER_FOLLOW_END,

		PATTERN1_BOMBING_START,
		PATTERN1_BOMBING_ING,
		PATTERN1_BOMBING_END,


		PATTERN2_SHOOTING_START,
		PATTERN2_SHOOTING_ING,
		PATTERN2_SHOOTING_END,

		PATTERN3_BODYSLAP_START,
		PATTERN3_BODYSLAP_ING,
		PATTERN3_BODYSLAP_END,

		PATTERN4_CLUSTERBOMB_START,
		PATTERN4_CLUSTERBOMB_ING,
		PATTERN4_CLUSTERBOMB_END,

		EXIT_START,
		EXIT_ING,
		EXIT_END,
	};
	STATE m_eState;
};

