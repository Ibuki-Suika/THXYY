#ifndef TH_CORE_DUMPER_H
#define TH_CORE_DUMPER_H

#include <Common\THCommon.h>

namespace THEngine
{
	class CoreDumper
	{
	private:
		static CoreDumper* instance;

		CRITICAL_SECTION section;

		static LONG WINAPI  UnhandledExceptionFilter(_EXCEPTION_POINTERS* exception);

		bool Dump(_EXCEPTION_POINTERS* exception, WCHAR* fileName);

	public:
		CoreDumper();
		~CoreDumper();
	};
}

#endif