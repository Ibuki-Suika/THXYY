#ifndef THSHADER_H
#define THSHADER_H

#include "../Common/THCommon.h"
#include "THTexture.h"
#include "THCubeMap.h"
#include <Math\THMath.h>

namespace THEngine
{
	class AssetManager;

	class Shader : public Object
	{
	protected:
		ID3DXEffect* effect;
		UINT passNum;
		String path;
		int currentPass = -1;

	public:
		Shader();
		virtual ~Shader();

		void SetTechnique(char* technique);

		void Use();

		void End();

		inline void CommitChanges()
		{
			this->effect->CommitChanges();
		}

		void UsePass(unsigned int pass);

		void EndPass();

		inline UINT GetPassNum() { return passNum; }

		inline void SetTexture(char* textureName, Texture* texture)
		{
			effect->SetTexture(textureName, texture->texImpl->texture);
		}

		inline void SetCubeMap(char* textureName, CubeMap* cubeMap)
		{
			effect->SetTexture(textureName, cubeMap->impl->cubeTexture);
		}

		inline void SetInt(char* name, int value)
		{
			effect->SetInt(name, value);
		}

		inline void SetFloat(char* name, float value)
		{
			effect->SetFloat(name, value);
		}

		inline void SetBoolean(char* name, bool value)
		{
			effect->SetBool(name, value);
		}

		inline void SetFloatArray(char* name, float* value, int count)
		{
			effect->SetFloatArray(name, value, count);
		}

		inline void SetFloat4(char* name, const Vector4f vector)
		{
			effect->SetFloatArray(name, vector._data, 4);
		}

		inline void SetMatrix(char* name, const Matrix& value)
		{
			effect->SetMatrix(name, &value.matrix);
		}

		inline void SetValue(char* name, void* value, int size)
		{
			effect->SetValue(name, value, size);
		}

		void OnLostDevice();
		void OnResetDevice();

		friend class AssetManager;
	};
}

#endif