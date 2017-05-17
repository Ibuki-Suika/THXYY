#ifndef THGAME_H
#define THGAME_H

#include <Common\THCommon.h>
#include <Platform\THCoreDumper.h>

namespace THEngine
{
	class Application;
	class Input;
	class Audio;
	class Scene;
	class Font;
	class Sprite;
	class DataStack;
	class RenderPipeline;
	class AssetManager;
	class EventSystem;
	class Font;
	class ShaderStock;
	class RenderPipeline;
	class AsyncInfo;
	struct Config;

	class Game : public EngineObject
	{
	private:
		static Game* instance;
		Config* config = nullptr;

		bool enterBackground = false;

		float fps;
		int frameCount;
		bool showFPS;

		unsigned int lastTime, currentTime;

		CoreDumper coreDumper;

		Application* app;

		Scene* scene;
		Scene* nextScene;

		RenderPipeline* pipeline = nullptr;

		AssetManager* assetManager;
		ShaderStock* shaderStock;

		EventSystem* eventSystem;

		Font* defaultFont;

		Input* input;

		Audio* audio = nullptr;

		ExceptionManager* exceptionManager = nullptr;

		DataStack* dataStack = nullptr;

	private:
		void CalcFPS();
		void DrawFPS();

	public:
		Game();
		virtual ~Game();

		virtual void Update() override;
		virtual void Draw() override;
		virtual void OnShutdown();
		virtual void OnEnterBackground();
		virtual void OnReturnToForeground();

		int Run();

		void Shutdown();

		void Quit();

		static Game* GetInstance();

		bool CreateGame(int width, int height, bool fullScreen, const String& title, int bigIcon, int smallIcon);

		bool CreateGame(const Config& config, int bigIcon, int smallIcon);

		void SetScene(Scene* scene);

		void LoadScene(Scene* scene);

		void LoadSceneAsync(Scene* scene);

		void LoadSceneAsync(Scene* scene, int delay, const std::function<void()>& onLoadCompleted);

		AsyncInfo* LoadSceneAsyncWithInfo(Scene* scene, bool autoChange);

		inline Application* GetApplication() const { return app; }

		inline RenderPipeline* GetRenderPipeline() const { return pipeline; }

		inline AssetManager* GetAssetManager() const
		{
			return assetManager;
		}

		int GetWidth() const;
		int GetHeight() const;

		inline Scene* GetScene() const { return scene; }

		const String& GetTitle() const;
	};
}

#endif