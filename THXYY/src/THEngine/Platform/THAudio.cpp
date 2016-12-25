#include "THAudio.h"
#include "THApplication.h"
#include "External\CWaveFile.h"

namespace THEngine
{
	Audio* Audio::instance = nullptr;

	Audio::Audio()
	{

	}

	Audio::~Audio()
	{
		soundList.Clear();
		if (masterVoice)
		{
			masterVoice->DestroyVoice();
		}
		TH_SAFE_RELEASE(xaudio);

		CoUninitialize();
	}

	Audio* Audio::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Audio();
			if (!instance->Init())
			{
				delete instance;
				instance = nullptr;
			}
		}
		return instance;
	}

	bool Audio::Init()
	{
		HRESULT hr;

		if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		{
			return false;
		}

		if (FAILED(hr = XAudio2Create(&xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR)))
			return false;

		if (FAILED(hr = xaudio->CreateMasteringVoice(&masterVoice)))
			return false;

		return true;
	}

	Sound* Audio::CreateSound(String filePath)
	{
		auto exceptionManager = ExceptionManager::GetInstance();
		Sound* sound = nullptr;

		String ext = filePath.SubString(filePath.LastIndexOf(TCHAR('.')) + 1, filePath.GetLength());
		if (ext == "wav")
		{
			sound = LoadWav(filePath);
		}
		else
		{
			Exception* exception = new Exception("��֧�ֵ��ļ���ʽ��");
			exceptionManager->PushException(exception);
		}

		if (sound)
		{
			sound->SetVolume(volume);
			soundList.Add(sound);
		}
		else
		{
			auto exception = exceptionManager->GetException();
			if (exception)
			{
				THMessageBox((String)"�޷�������Ƶ�ļ���" + filePath + "ԭ���ǣ�\n" + exception->GetInfo());
				exceptionManager->SetHandled();
			}
		}
		return sound;
	}

	Sound* Audio::LoadWav(String filePath)
	{
		Sound* sound = new Sound();
		auto exceptionManager = ExceptionManager::GetInstance();

		CWaveFile wave;
		WAVEFORMATEX wf;
		if (FAILED(wave.Open(filePath.GetBuffer(), &wf, WAVEFILE_READ)))
		{
			Exception* exception = new Exception("�޷����ļ����ļ�·�����ܲ���ȷ�����ļ��������𻵡�");
			exceptionManager->PushException(exception);
			delete sound;
			return nullptr;
		}

		sound->callback = new Sound::SoundCallback(sound);

		if (FAILED(xaudio->CreateSourceVoice(&sound->sourceVoice, wave.GetFormat(), 0, 2.0f, sound->callback)))
		{
			Exception* exception = new Exception("�޷�������Ƶ���档");
			exceptionManager->PushException(exception);
			delete sound;
			return nullptr;
		}

		XAUDIO2_BUFFER* buffer = &sound->buffer;
		ZeroMemory(buffer, sizeof(XAUDIO2_BUFFER));
		buffer->Flags = XAUDIO2_END_OF_STREAM;
		buffer->pAudioData = new BYTE[wave.GetSize()];

		DWORD readSize;
		if (FAILED(wave.Read((BYTE*)buffer->pAudioData, wave.GetSize(), &readSize)))
		{
			Exception* exception = new Exception("�޷������ļ����ļ��������𻵡�");
			exceptionManager->PushException(exception);
			delete sound;
			return nullptr;
		}

		buffer->AudioBytes = readSize;

		return sound;
	}

	void Audio::Play(Sound* sound)
	{
		auto iter = playList.GetIterator();
		while (iter->HasNext())
		{
			auto soundPlaying = iter->Next();
			if (soundPlaying == sound)
			{
				return;
			}
		}
		playList.Add(sound);
	}

	void Audio::Update()
	{
		auto iter = playList.GetIterator();
		while (iter->HasNext())
		{
			auto sound = iter->Next();
			sound->Play();
			iter->Remove();
		}
	}
}

