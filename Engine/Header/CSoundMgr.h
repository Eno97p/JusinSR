#pragma once

#include "Engine_Define.h"
#include "Base.h"

class CSound;

namespace Engine
{
	class ENGINE_DLL CSoundMgr :
		public CBase
	{
		DECLARE_SINGLETON(CSoundMgr)

	private:
		CSoundMgr();
		virtual ~CSoundMgr();
	public:
		void Initialize();
		void Release();

	public:
		void PlaySound(FMOD::Sound* pSoundKey, eCHANNELID eID, float fVolume);
		void PlayBGM(FMOD::Sound* pSoundKey, float fVolume);
		void StopSound(eCHANNELID eID);
		void StopAll();
		void SetChannelVolume(eCHANNELID eID, float fVolume);

	private:
		// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
		FMOD::Channel* m_pChannelArr[(int)eCHANNELID::MAXCHANNEL];

		// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
		FMOD::System* m_pSystem;
	private:
		virtual void Free();
	};


}
