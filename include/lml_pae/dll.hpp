#pragma once

#include <lml_pae/string.hpp>

#include <string>

namespace lml_pae
{
	using dll_handle = void*;

	namespace details
	{
		void* get_function_address_from_dll(dll_handle handle, const std::string& name) noexcept;
	}

	dll_handle open_dll(const string& path) noexcept;
	void close_dll(dll_handle dll) noexcept;
	template<typename Result_, typename... Args_>
	auto get_function_from_dll(dll_handle dll, const std::string& name) noexcept
		-> Result_(*)(Args_...);
	template<typename Result_, typename... Args_>
	auto get_function_from_dll<Result_(Args_...)>(dll_handle dll, const std::string& name) noexcept
		-> Result_(*)(Args_...)
	{
		return reinterpret_cast<Result_(*)(Args_...)>(details::get_function_address_from_dll(dll, name));
	}
}