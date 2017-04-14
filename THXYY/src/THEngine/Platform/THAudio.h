#ifndef THAUDIO_H
#define THAUDIO_H

#include <Common\THCommon.h>
#include <xaudio2.h>
#include "THSound.h"

namespace THEngine
{
	class Audio : public Object
	{
	private:
		static Audio* instance;

		IXAudio2* xaudio = nullptr;
		IXAudio2MasteringVoice* masterVoice = nullptr;

		ArrayList<Sound*> soundList;

		int volume = 20;    //Range from 0 to 100

	private:
		Audio();
		bool Init();

		Sound* LoadWav(String filePath);

	public:
		virtual ~Audio();

		static Audio* GetInstance();

		Sound* CreateSound(String filePath);

		inline void DestroySound(Sound* sound)
		{
			soundList.Remove(sound);
		}

		inline void SetVolume(int volume) { this->volume = volume; }

		void Update();
	};
}

#endif