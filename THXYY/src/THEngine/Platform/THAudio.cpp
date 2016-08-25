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
		//soundList.Clear();
		TH_SAFE_RELEASE(dsound);
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

		if (FAILED(hr = DirectSoundCreate(NULL, &dsound, NULL)))
			return false;

		if (FAILED(hr = dsound->SetCooperativeLevel(Application::GetInstance()->hWnd, DSSCL_PRIORITY)))
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

		DSBUFFERDESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.dwBufferBytes = wave.GetSize();
		desc.dwSize = sizeof(DSBUFFERDESC);
		desc.lpwfxFormat = wave.GetFormat();
		desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME;

		if (FAILED(dsound->CreateSoundBuffer(&desc, &sound->buffer, NULL)))
		{
			Exception* exception = new Exception("�޷�������Ƶ���档");
			exceptionManager->PushException(exception);
			delete sound;
			return nullptr;
		}

		IDirectSoundBuffer* buffer = sound->buffer;
		VOID* lockedBuffer;
		DWORD lockedBufferSize;
		if (FAILED(buffer->Lock(0, wave.GetSize(), &lockedBuffer, &lockedBufferSize, NULL, NULL, 0)))
		{
			Exception* exception = new Exception("�޷�����Ƶ����д�����ݡ�");
			exceptionManager->PushException(exception);
			delete sound;
			return nullptr;
		}

		DWORD readSize;
		if (FAILED(wave.Read((BYTE*)lockedBuffer, lockedBufferSize, &readSize)))
		{
			Exception* exception = new Exception("�޷������ļ����ļ��������𻵡�");
			exceptionManager->PushException(exception);
			delete sound;
			return nullptr;
		}

		return sound;
	}
}

