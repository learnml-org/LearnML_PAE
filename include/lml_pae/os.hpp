#pragma once

#include <string>

namespace lml_pae
{
#if !(defined(LML_PAE_WINDOWS) || defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX))
#	if		defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#				define LML_PAE_WINDOWS
#	elif	defined(macintosh) || defined(Macintosh) || (defined(__APPLE__ ) && defined(__MACH__))
#				define LML_PAE_MACOS
#	elif	defined(__gnu_linux__)
#				define LML_PAE_LINUX
#	else
#				error Not supported
#	endif
#endif

	enum class os
	{
		windows,
		macos,
		linux,

		target =
#if		defined(LML_PAE_WINDOWS)
			windows
#elif	defined(LML_PAE_MACOS)
			macos
#elif	defined(LML_PAE_LINUX)
			linux
#endif
	};

	std::string get_os_info();
}