#include <lml_pae/filesystem.hpp>

#include <lml_pae/errorcode.hpp>
#include <lml_pae/os.hpp>

#include <ctime>
#include <string>

#if	defined(LML_PAE_WINDOWS)
#	include <Windows.h>
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
#	include <sys/utsname.h>
#endif

namespace lml_pae
{
	extern string data_directory;
	extern string temp_directory;

	string get_data_file(const string& path)
	{
#if defined(LML_PAE_WINDOWS)
		return data_directory + STR('\\') + path;
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		return data_directory + STR('/') + path;
#endif
	}
	string get_temp_file()
	{
#if defined(LML_PAE_WINDOWS)
		character buffer[MAX_PATH];
		if (GetTempFileName(temp_directory.c_str(), STR("lml"), 0, buffer) == 0) throw LML_PAE_ERRORCODE_FAILED_TO_GET_TEMP_FILE;

		return buffer;
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		const std::time_t time = std::time(nullptr);
		const string time_str = std::to_string(time);

		return temp_directory + STR("/lml") + time_str;
#endif
	}
}