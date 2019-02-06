#include <lml_pae/os.hpp>

#include <lml_pae/errorcode.hpp>
#include <lml_pae/string.hpp>

#include <cstddef>
#include <sstream>

#if	defined(LML_PAE_WINDOWS)
#	include <Windows.h>
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
#	include <sys/utsname.h>
#endif

namespace lml_pae
{
	std::string get_os_info()
	{
#if	defined(LML_PAE_WINDOWS)
		BOOL is_wow64 = FALSE;
		IsWow64Process(GetCurrentProcess(), &is_wow64);
		const REGSAM sam = KEY_QUERY_VALUE | (is_wow64 ? KEY_WOW64_64KEY : 0);

		HKEY version;
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, STR("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"), 0, sam, &version) != ERROR_SUCCESS) throw LML_PAE_ERRORCODE_FAILED_TO_GET_OS_INFO;

		DWORD string_size;
		if (RegQueryValueExA(version, "ProductName", nullptr, nullptr, nullptr, &string_size) != ERROR_SUCCESS) throw LML_PAE_ERRORCODE_FAILED_TO_GET_OS_INFO;
		std::string result(static_cast<std::size_t>(string_size), 0);
		if (RegQueryValueExA(version, "ProductName", nullptr, nullptr, reinterpret_cast<LPBYTE>(result.data()), &string_size) != ERROR_SUCCESS) throw LML_PAE_ERRORCODE_FAILED_TO_GET_OS_INFO;
		result.erase(result.end() - 1);

		return result;
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		struct utsname un;
		uname(&un);

		std::ostringstream oss;
		oss << un.nodename << '(' << un.sysname << ") " << un.version;
		return oss.str();
#endif
	}
}