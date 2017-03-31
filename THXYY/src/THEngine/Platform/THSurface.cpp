#include "THSurface.h"

namespace THEngine
{
	Surface::~Surface()
	{
		TH_SAFE_RELEASE(this->surface);
	}

	bool Surface::SaveToFile(const String& path)
	{
		D3DXIMAGE_FILEFORMAT format;
		String ext = path.SubString(path.LastIndexOf(TCHAR('.')) + 1, path.GetLength());
		if (ext == "png")
		{
			format = D3DXIFF_PNG;
		}
		else if (ext == "jpg")
		{
			format = D3DXIFF_JPG;
		}
		else if (ext == "bmp")
		{
			format = D3DXIFF_BMP;
		}
		else
		{
			THMessageBox((String)"�޷���surface�洢Ϊ�ļ�����֧�ֵ��ļ���ʽ��" + ext);
			return false;
		}

		if (FAILED(D3DXSaveSurfaceToFile(path.GetBuffer(), format, surface, nullptr, nullptr)))
		{
			return false;
		}
		return true;
	}
}