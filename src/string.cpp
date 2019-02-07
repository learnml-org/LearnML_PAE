#include <lml_pae/string.hpp>

#include <lml_pae/errorcode.hpp>

#if	defined(LML_PAE_WINDOWS)
#	include <Windows.h>
#endif

namespace lml_pae
{
	std::string to_utf8(const string& sys_enc)
	{
#if defined(LML_PAE_WINDOWS)
#	if defined(UNICODE) || defined(_UNICODE)
		if (sys_enc.empty()) return {};

		const int size = WideCharToMultiByte(CP_UTF8, 0, sys_enc.c_str(), static_cast<int>(sys_enc.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);
		WideCharToMultiByte(CP_UTF8, 0, sys_enc.c_str(), static_cast<int>(sys_enc.size()), result.data(), size, nullptr, nullptr);

		return result;
#	else
		if (sys_enc.empty()) return {};

		const int utf16_size = MultiByteToWideChar(CP_ACP, 0, sys_enc.c_str(), static_cast<int>(sys_enc.size()), nullptr, 0);
		std::wstring utf16(static_cast<std::size_t>(utf16_size), 0);
		MultiByteToWideChar(CP_ACP, 0, sys_enc.c_str(), static_cast<int>(sys_enc.size()), utf16.data(), utf16_size);

		const int size = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), static_cast<int>(utf16.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);
		WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), static_cast<int>(utf16.size()), result.data(), size, nullptr, nullptr);

		return result;
#	endif
#else
		return sys_enc;
#endif
	}
	string from_utf8(const std::string& utf8)
	{
#if defined(LML_PAE_WINDOWS)
#	if defined(UNICODE) || defined(_UNICODE)
		if (utf8.empty()) return {};

		const int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), nullptr, 0);
		std::wstring result(static_cast<std::size_t>(size), 0);
		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), result.data(), size);

		return result;
#	else
		if (utf8.empty()) return {};

		const int utf16_size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), nullptr, 0);
		std::wstring utf16(static_cast<std::size_t>(utf16_size), 0);
		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), utf16.data(), utf16_size);

		const int size = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), static_cast<int>(utf16.size()), nullptr, 0, nullptr, nullptr);
		std::string result(static_cast<std::size_t>(size), 0);
		if (WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), static_cast<int>(utf16.size()), result.data(), size, nullptr, nullptr) == 0 &&
			GetLastError() == ERROR_NO_UNICODE_TRANSLATION) throw LML_PAE_ERRORCODE_FAILED_TO_ENCODE_TO_SYSE;

		return result;
#	endif
#else
		return utf8;
#endif
	}
}