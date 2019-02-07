#pragma once

#include <cstdint>

#define LML_PAE_ERRORCODE_FAILED_TO_GET_APPDATA					static_cast<std::uint32_t>(0x00030000)
#define LML_PAE_ERRORCODE_FAILED_TO_GET_TEMP_DIRECTORY			static_cast<std::uint32_t>(0x00030001)
#define LML_PAE_ERRORCODE_FAILED_TO_GET_OS_INFO					static_cast<std::uint32_t>(0x00030002)

#define LML_PAE_ERRORCODE_FAILED_TO_GET_TEMP_FILE				static_cast<std::uint32_t>(0x00030010)

#define LML_PAE_ERRORCODE_FAILED_TO_ENCODE_TO_SYSE				static_cast<std::uint32_t>(0x00030020)