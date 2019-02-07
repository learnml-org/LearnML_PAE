#include <lml_pae/dll.hpp>

#include <lml_pae/os.hpp>

#if	defined(LML_PAE_WINDOWS)
#	include <Windows.h>
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
#	include <dlfcn.h>
#endif

namespace lml_pae::details
{
	void* get_function_address_from_dll(dll_handle handle, const std::string& name) noexcept
	{
#if	defined(LML_PAE_WINDOWS)
		return GetProcAddress(reinterpret_cast<HMODULE>(handle), name.c_str());
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		return dlsym(handle, name.c_str());
#endif
	}
}

namespace lml_pae
{
	dll_handle open_dll(const string& path) noexcept
	{
#if	defined(LML_PAE_WINDOWS)
		return reinterpret_cast<dll_handle>(LoadLibrary(path.c_str()));
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		return dlopen(path.c_str(), RTLD_LAZY);
#endif
	}
	void close_dll(dll_handle dll) noexcept
	{
#if	defined(LML_PAE_WINDOWS)
		FreeLibrary(reinterpret_cast<HMODULE>(dll));
#elif defined(LML_PAE_MACOS) || defined(LML_PAE_LINUX)
		dlclose(dll);
#endif
	}
}