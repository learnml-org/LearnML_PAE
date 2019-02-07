#pragma once

#include <lml_pae/os.hpp>

#include <string>

namespace lml_pae
{
#ifdef LML_PAE_WINDOWS
#	define LML_PAE_INTERNAL_WSTR(prefix, string) prefix##string

#	if defined(UNICODE) || defined(_UNICODE)
	using character = wchar_t;
#	define STR(string) LML_PAE_INTERNAL_WSTR(L, string)
#	else
	using character = char;
#	define STR(string) string
#	endif
#else
	using character = char;
#	define STR(string) string
#endif

	using string = std::basic_string<character>;
}