#include <lml_pae/engine.hpp>

#include <lml_pae/errorcode.hpp>
#include <lml_pae/os.hpp>
#include <lml_pae/string.hpp>

#if	defined(LML_PAE_WINDOWS)
#	include <ShlObj.h>
#	include <Shlwapi.h>
#	include <Windows.h>
#endif

namespace lml_pae
{
	string data_directory;
	string temp_directory;

	std::uint32_t initialize() noexcept
	{
#if defined(LML_PAE_WINDOWS)
		character appdata_buffer[MAX_PATH];
		if (SHGetFolderPath(nullptr, CSIDL_APPDATA, nullptr, 0, appdata_buffer) != S_OK) return LML_PAE_ERRORCODE_FAILED_TO_GET_APPDATA;
		data_directory = appdata_buffer;
		data_directory += STR("\\Staticom\\LearnML");

		character temp_buffer[MAX_PATH];
		if (GetTempPath(MAX_PATH, temp_buffer) == 0) return LML_PAE_ERRORCODE_FAILED_TO_GET_TEMP_DIRECTORY;
		temp_directory = temp_buffer;
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		data_directory = STR("~/.Staticom/LearnML");
		temp_directory = STR("/tmp");
#endif

		return 0;
	}
}