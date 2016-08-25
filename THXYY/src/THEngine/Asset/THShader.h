#ifndef THSHADER_H
#define THSHADER_H

#include "../Common/THCommon.h"
#include "THTexture.h"

namespace THEngine
{
	class AssetManager;

	class Shader : public Object
	{
	protected:
		ID3DXEffect* effect;
		UINT passNum;

	public:
		Shader();
		virtual ~Shader();

		inline void SetTechnique(char* technique)
		{
			effect->SetTechnique(technique);
		}

		inline void Begin() { effect->Begin(&passNum, 0); }
		inline void End() { effect->End();}

		inline void BeginPass(unsigned int pass) { effect->BeginPass(pass); }
		inline void EndPass() { effect->EndPass(); }

		inline UINT GetPassNum() { return passNum; }

		inline void SetTexture(char* textureName, Texture* texture)
		{
			effect->SetTexture(textureName, texture->texture);
		}

		inline void SetInt(char* name, int value)
		{
			effect->SetInt(name, value);
		}

		inline void SetFloatArray(char* name, float* value, int count)
		{
			effect->SetFloatArray(name, value, count);
		}

		inline void SetMatrix(char* name, D3DXMATRIX* value)
		{
			effect->SetMatrix(name, value);
		}

		friend class AssetManager;
	};
}

#endif