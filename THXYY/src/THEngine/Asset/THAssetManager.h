#ifndef THASSETMANAGER
#define THASSETMANAGER

#include "../Common/THCommon.h"
#include "THShader.h"
#include "THTexture.h"
#include "THRenderTexture.h"
#include "THFloatTexture.h"
#include "THCubeMap.h"

namespace THEngine
{
	class AssetManager : public Object
	{
	private:
		IDirect3DDevice9* device;

		ArrayList<Shader*> shaderList;
		ArrayList<TextureImpl*> textureList;
		ArrayList<CubeMapImpl*> cubeMapList;
	
	private:
		AssetManager();

		void CopyImageToSurface(Image* image, IDirect3DSurface9* surface);
		
	public:
		static AssetManager* instance;

		static AssetManager* Create(Application* app);

		static AssetManager* GetInstance();

		Shader* CreateShaderFromFile(String filePath);
		void DestroyShader(Shader* shader);

		Texture* CreateTextureFromFile(String filePath);
		CubeMap* CreateCubeMapFromFile(const String& front, const String& back,
			const String& left, const String& right, const String& top, const String& bottom);
		RenderTexture* CreateRenderTexture(int width, int height);
		FloatTexture* CreateFloatTexture(int width, int height);

		void DestroyTexture(Texture* texture);
		void DestroyCubeMap(CubeMap* cubeMap);

		void OnLostDevice();
		void OnResetDevice();
	};
}

#endif