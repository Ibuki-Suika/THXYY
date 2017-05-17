#ifndef TH_CONFIG_H
#define TH_CONFIG_H

#include <Common\THCommon.h>

namespace THEngine
{
	struct Config
	{
		int width = 640;
		int height = 480;
		bool fullScreen = false;
		String title = "THEngine";
		bool useMultiSample = true;
		bool useVerticalAsync = true;
		bool useShadow = true;
		bool useLighting = true;
	};
}

#endif
