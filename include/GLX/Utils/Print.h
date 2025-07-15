#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/TypeTraits/RemoveReference.h"

#include "GLX/ThirdParty/fmt/core.h"
#include "GLX/ThirdParty/fmt/xchar.h"

template<typename... TArgs>
GLX_FORCE_INLINE void Print(std::FILE* InOutputFile, fmt::string_view InFmtString, TArgs&&... InArgs)
{
	const auto& FormatArgs = fmt::make_format_args(InArgs...);

	if constexpr (!fmt::detail::use_utf8)
	{
		fmt::detail::vprint_mojibake(InOutputFile, InFmtString, FormatArgs, false);
	}
	else
	{
		if constexpr (fmt::detail::is_locking<TArgs...>())
		{
			fmt::vprint_buffered(InOutputFile, InFmtString, FormatArgs);
		}
		else
		{
			fmt::vprint(InOutputFile, InFmtString, FormatArgs);
		}
	}
}

template<typename... TArgs>
GLX_FORCE_INLINE void Print(fmt::string_view InFmtString, TArgs&&... InArgs)
{
	const auto& FormatArgs = fmt::make_format_args(InArgs...);

	if constexpr (!fmt::detail::use_utf8)
	{
		fmt::detail::vprint_mojibake(stdout, InFmtString, FormatArgs, false);
	}
	else
	{
		if constexpr (fmt::detail::is_locking<TArgs...>())
		{
			fmt::vprint_buffered(stdout, InFmtString, FormatArgs);
		}
		else
		{
			fmt::vprint(stdout, InFmtString, FormatArgs);
		}
	}
}

template<typename... TArgs>
GLX_FORCE_INLINE void Print(std::FILE* InOutputFile, fmt::wstring_view InFmtString, TArgs&&... InArgs)
{
	auto MemoryBuffer = fmt::wmemory_buffer();
	auto FormatArgs = fmt::make_format_args<fmt::wformat_context>(InArgs...);

	fmt::detail::vformat_to(MemoryBuffer, InFmtString, FormatArgs);
	MemoryBuffer.push_back(L'\0');

	std::fputws(MemoryBuffer.data(), InOutputFile);
}

template<typename... TArgs>
GLX_FORCE_INLINE void Print(fmt::wstring_view InFmtString, TArgs&&... InArgs)
{
	auto MemoryBuffer = fmt::wmemory_buffer();
	auto FormatArgs = fmt::make_format_args<fmt::wformat_context>(InArgs...);

	fmt::detail::vformat_to(MemoryBuffer, InFmtString, FormatArgs);
	MemoryBuffer.push_back(L'\0');

	std::fputws(MemoryBuffer.data(), stdout);
}
