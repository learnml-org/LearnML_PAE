#pragma once

#if !(defined(LML_PAE_X86) || defined(LML_PAE_X64) || defined(LML_PAE_ARM) || defined(LML_PAE_ARM64))
#	if		defined(i386) || defined(__i386) || defined(__i386__) || defined(__IA32__) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) ||\
			defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__) || defined(__386)
#				define LML_PAE_X86
#	elif	defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#				define LML_PAE_X64
#	elif	defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) ||\
			defined(_M_ARMT) || defined(__arm)
#				define LML_PAE_ARM
#	elif	defined(__aarch64__) || defined(_M_ARM64)
#				define LML_PAE_ARM64
#	else
#				error Not supported
#	endif
#endif

namespace lml_pae
{
	enum class architecture
	{
		x86,
		x64,
		arm,
		arm64,

		target =
#if		defined(LML_PAE_X86)
			x86
#elif	defined(LML_PAE_X64)
			x64
#elif	defined(LML_PAE_ARM)
			arm
#elif	defined(LML_PAE_ARM64)
			arm64
#endif
	};
}