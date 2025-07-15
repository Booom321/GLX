#pragma once

#if !defined(NOMINMAX)
	#define NOMINMAX
#endif

#if !defined(FMT_HEADER_ONLY)
	#define FMT_HEADER_ONLY
#endif

#if !defined(XXH_INLINE_ALL)
	#define XXH_INLINE_ALL
#endif

#if defined(DEBUG)
	#define GLX_DEBUG
#endif

#if defined(RELEASE)
	#define GLX_RELEASE
#endif

#if !defined(GLX_LINE)
	#define GLX_LINE __LINE__
#endif

#if !defined(GLX_FILE)
	#define GLX_FILE __FILE__
#endif

#if !defined(GLX_STRINGIFY)
	#define GLX_STRINGIFY(X) #X
#endif

#if !defined(GLX_STRINGIFY_W)
	#define GLX_STRINGIFY_W(X) L#X
#endif

#if !defined(GLX_CONCATENATE)
	#define GLX_CONCATENATE(A, B) A##B
#endif

#if !defined(GLX_BIT)
	#define GLX_BIT(X) (1 << (X))
#endif

#if !defined(GLX_UNUSED)
	#define GLX_UNUSED(X) (void)(X)
#endif

#if defined(__has_cpp_attribute)
	#define GLX_HAS_CPP_ATTRIBUTE(...) __has_cpp_attribute(__VA_ARGS__)
#endif

#if defined(GLX_HAS_CPP_ATTRIBUTE)
	#if !defined(GLX_NODISCARD)
		#if GLX_HAS_CPP_ATTRIBUTE(nodiscard)
			#define GLX_NODISCARD [[nodiscard]]
		#else
			#define GLX_NODISCARD
		#endif
	#endif

	#if !defined(GLX_NORETURN)
		#if GLX_HAS_CPP_ATTRIBUTE(noreturn)
			#define GLX_NORETURN [[noreturn]]
		#else
			#define GLX_NORETURN
		#endif
	#endif

	#if !defined(GLX_DEPRECATED)
		#if GLX_HAS_CPP_ATTRIBUTE(deprecated)
			#define GLX_DEPRECATED [[deprecated]]
		#else
			#define GLX_DEPRECATED
		#endif
	#endif

	#if !defined(GLX_MAYBE_UNUSED)
		#if GLX_HAS_CPP_ATTRIBUTE(maybe_unused)
			#define GLX_MAYBE_UNUSED [[maybe_unused]]
		#else
			#define GLX_MAYBE_UNUSED
		#endif
	#endif

	#if !defined(GLX_FALLTHROUGH)
		#if GLX_HAS_CPP_ATTRIBUTE(fallthrough)
			#define GLX_FALLTHROUGH [[fallthrough]]
		#else
			#define GLX_FALLTHROUGH
		#endif
	#endif
#else
	#define GLX_NODISCARD
	#define GLX_NORETURN
	#define GLX_DEPRECATED
	#define GLX_MAYBE_UNUSED
	#define GLX_FALLTHROUGH
#endif

#if __cpp_constexpr
	#define GLX_CONSTEXPR constexpr
#else
	#define GLX_CONSTEXPR
#endif

#if __cpp_consteval
	#define GLX_CONSTEVAL consteval
#else
	#define GLX_CONSTEVAL
#endif

#if defined(_MSC_VER)
	#define GLX_COMPILER_MSVC
#elif defined(__clang__)
	#define GLX_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	#define GLX_COMPILER_GCC
#else
	#error "Unknown compiler"
#endif

#if defined(__MINGW32__)
	#define GLX_MINGW32
#elif defined(__MINGW64__)
	#define GLX_MINGW64
#endif

#if defined(GLX_COMPILER_MSVC)
	#define GLX_IMPORT __declspec(dllimport)
	#define GLX_EXPORT __declspec(dllexport)
#elif defined(GLX_COMPILER_CLANG) || defined(GLX_COMPILER_GCC)
	#define GLX_IMPORT
	#define GLX_EXPORT __attribute__((visibility("default")))
#else
	#define GLX_IMPORT
	#define GLX_EXPORT
#endif

#if defined(GLX_DLL_LIBRARY)
	#if defined(GLX_DLL_EXPORT)
		#define GLX_API GLX_EXPORT
	#else
		#define GLX_API GLX_IMPORT
	#endif
#else
	#define GLX_API
#endif

#if defined(GLX_COMPILER_MSVC)
	#define GLX_INLINE __inline
	#define GLX_FORCE_INLINE __forceinline
	#define GLX_NOINLINE __declspec(noinline)
#elif defined(GLX_COMPILER_CLANG) || defined(GLX_COMPILER_GCC)
	#define GLX_INLINE __attribute__((always_inline)) inline
	#define GLX_FORCE_INLINE __attribute__((always_inline)) inline
	#define GLX_NOINLINE __attribute__((noinline))
#else
	#define GLX_INLINE inline
	#define GLX_FORCE_INLINE inline
	#define GLX_NOINLINE
#endif

#if defined(GLX_COMPILER_MSVC)
	#define GLX_RESTRICT __restrict
#elif defined(GLX_COMPILER_CLANG) || defined(GLX_COMPILER_GCC)
	#define GLX_RESTRICT __restrict__
#else
	#define GLX_RESTRICT
#endif

#if defined(GLX_COMPILER_MSVC)
	#define GLX_WARNING_PUSH __pragma(warning(push))
	#define GLX_WARNING_POP __pragma(warning(pop))
	#define GLX_MSVC_DISABLE_WARNING(WarningNum) __pragma(warning(disable : WarningNum))
	#define GLX_CLANG_DISABLE_WARNING(Warning)
	#define GLX_GCC_DISABLE_WARNING(Warning)
#elif defined(GLX_COMPILER_CLANG)
	#define GLX_WARNING_PUSH _Pragma("clang diagnostic push")
	#define GLX_WARNING_POP _Pragma("clang diagnostic pop")
	#define GLX_CLANG_DISABLE_WARNING(Warning) _Pragma(GLX_STRINGIFY(clang diagnostic ignored Warning))
	#define GLX_MSVC_DISABLE_WARNING(WarningNum)
	#define GLX_GCC_DISABLE_WARNING(Warning)
#elif defined(GLX_COMPILER_GCC)
	#define GLX_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define GLX_WARNING_POP _Pragma("GCC diagnostic pop")
	#define GLX_GCC_DISABLE_WARNING(Warning) _Pragma(GLX_STRINGIFY(GCC diagnostic ignored Warning))
	#define GLX_MSVC_DISABLE_WARNING(WarningNum)
	#define GLX_CLANG_DISABLE_WARNING(Warning)
#else
	#define GLX_WARNING_PUSH
	#define GLX_WARNING_POP
	#define GLX_MSVC_DISABLE_WARNING(WarningNum)
	#define GLX_CLANG_DISABLE_WARNING(Warning)
	#define GLX_GCC_DISABLE_WARNING(Warning)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PLATFORM //////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
	#if defined(_WIN64)
		#define GLX_PLATFORM_WIN64
		#define GLX_PLATFORM_WINDOWS
	#else
		#error "Only supports 64-bit Windows"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#define GLX_PLATFORM_APPLE
	#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
		#define GLX_PLATFORM_IOS
	#else
		#define GLX_PLATFORM_MAC
	#endif
#elif defined(__ANDROID__)
	#define GLX_PLATFORM_ANDROID
#elif defined(__linux__) || defined(__gnu_linux__)
	#define GLX_PLATFORM_LINUX
#elif defined(__unix__) || defined(__unix)
	#define GLX_PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
	#define GLX_PLATFORM_POSIX
#else
	#error "Unknown platform"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// CPU ARCHITECTURE //////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(GLX_COMPILER_MSVC)
	#if defined(_M_X64) || defined(_M_IX86) || defined(_M_AMD64)
		#define GLX_CPU_ARCH_X86
	#elif defined(_M_ARM) || defined(_M_ARM64)
		#define GLX_CPU_ARCH_ARM
	#endif
#elif defined(GLX_COMPILER_CLANG) || defined(GLX_COMPILER_GCC)
	#if defined(__x86_64__) || defined(__i386__) || defined(__amd64__)
		#define GLX_CPU_ARCH_X86
	#elif defined(__arm__) || defined(__aarch64__)
		#define GLX_CPU_ARCH_ARM
	#endif
#else
	#error "Unknown compiler"
#endif

#if defined(GLX_DEBUG)
	#if defined(GLX_COMPILER_MSVC)
		#define GLX_DEBUG_BREAK __debugbreak()
	#elif defined(__x86_64__) || defined(__i386__)
		#define GLX_DEBUG_BREAK __asm__ volatile("int $0x03")
	#elif defined(__aarch64__) && defined(GLX_PLATFORM_APPLE)
		#define GLX_DEBUG_BREAK __builtin_debugtrap()
	#elif defined(__aarch64__)
		#define GLX_DEBUG_BREAK __asm__ volatile(".inst 0xd4200000")
	#elif defined(GLX_PLATFORM_LINUX)
		#include <signal.h>
		#if defined(SIGTRAP)
			#define GLX_DEBUG_BREAK raise(SIGTRAP)
		#else
			#define GLX_DEBUG_BREAK raise(SIGABRT)
		#endif
	#else
		#define GLX_DEBUG_BREAK
	#endif
#else
	#define GLX_DEBUG_BREAK
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(GLX_DEBUG) && !defined(GLX_DISABLE_ASSERTION_DEBUG)
	#define GLX_ENABLE_ASSERTION 1
#else
	#define GLX_ENABLE_ASSERTION 0
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HELPER ////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(GLX_MIN)
	#define GLX_MIN(InX, InY) (InX < InY) ? InX : InY
#endif

#if !defined(GLX_MAX)
	#define GLX_MAX(InX, InY) (InX > InY) ? InX : InY
#endif

#if !defined(GLX_CLAMP)
	#define GLX_CLAMP(InX, InMin, InMax) (InX < InMin ? InMin : (InMax < InX ? InMax : InX))
#endif

#if !defined(GLX_GET_ARRAY_COUNT)
	#define GLX_GET_ARRAY_COUNT(InArr) (sizeof(InArr) / sizeof((InArr)[0]))
#endif

#if !defined(GLX_INVALID_INDEX)
	#define GLX_INVALID_INDEX (-1)
#endif

#include <type_traits>

#if !defined(GLX_DEFINE_ENUM_CLASS_BITWISE_OPERATORS)
	#define GLX_DEFINE_ENUM_CLASS_BITWISE_OPERATORS(InEnum) \
		GLX_FORCE_INLINE InEnum& operator|=(InEnum& InA, InEnum InB) { return InA = static_cast<InEnum>(static_cast<std::underlying_type_t<InEnum>>(InA) | static_cast<std::underlying_type_t<InEnum>>(InB)); } \
		GLX_FORCE_INLINE InEnum& operator&=(InEnum& InA, InEnum InB) { return InA = static_cast<InEnum>(static_cast<std::underlying_type_t<InEnum>>(InA) & static_cast<std::underlying_type_t<InEnum>>(InB)); } \
		GLX_FORCE_INLINE InEnum& operator^=(InEnum& InA, InEnum InB) { return InA = static_cast<InEnum>(static_cast<std::underlying_type_t<InEnum>>(InA) ^ static_cast<std::underlying_type_t<InEnum>>(InB)); } \
		GLX_FORCE_INLINE GLX_CONSTEXPR InEnum operator|(InEnum InA, InEnum InB) { return static_cast<InEnum>(static_cast<std::underlying_type_t<InEnum>>(InA) | static_cast<std::underlying_type_t<InEnum>>(InB)); } \
		GLX_FORCE_INLINE GLX_CONSTEXPR InEnum operator&(InEnum InA, InEnum InB) { return static_cast<InEnum>(static_cast<std::underlying_type_t<InEnum>>(InA) & static_cast<std::underlying_type_t<InEnum>>(InB)); } \
		GLX_FORCE_INLINE GLX_CONSTEXPR InEnum operator^(InEnum InA, InEnum InB) { return static_cast<InEnum>(static_cast<std::underlying_type_t<InEnum>>(InA) ^ static_cast<std::underlying_type_t<InEnum>>(InB)); } \
		GLX_FORCE_INLINE GLX_CONSTEXPR InEnum operator~(InEnum InE) { return static_cast<InEnum>(~static_cast<std::underlying_type_t<InEnum>>(InE)); } \
		GLX_FORCE_INLINE GLX_CONSTEXPR bool operator!(InEnum InE) { return !static_cast<std::underlying_type_t<InEnum>>(InE); }
#endif

#if !defined(GLX_HAS_FLAGS)
	#define GLX_HAS_FLAGS(InFlags, InFlagsToCheck) (((InFlags) & (InFlagsToCheck)) == (InFlagsToCheck))
#endif

#if !defined(GLX_CASE_TO_STRING)
	#define GLX_CASE_TO_STRING(InCaseValue) case InCaseValue: return GLX_STRINGIFY(InCaseValue)
#endif

#if !defined(GLX_CASE_TO_STRING_W)
	#define GLX_CASE_TO_STRING_W(InCaseValue) case InCaseValue: return GLX_STRINGIFY_W(InCaseValue)
#endif
