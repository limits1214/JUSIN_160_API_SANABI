#pragma once
#include "CObj.h"
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

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Motion_Change();
	void Test_Key_Input();

private:
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

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
};

