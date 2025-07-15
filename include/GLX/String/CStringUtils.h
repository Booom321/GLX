#pragma once

#include "CharUtils.h"
#include "GLX/Memory/MemoryUtils.h"

#include <cstring>
#include <wchar.h>

#if !defined(GLX_WMEMCPY)
	#define GLX_WMEMCPY(...) wmemcpy(__VA_ARGS__)
#endif

#if !defined(GLX_WMEMSET)
	#define GLX_WMEMSET(...) wmemset(__VA_ARGS__)
#endif

#if !defined(GLX_WMEMMOVE)
	#define GLX_WMEMMOVE(...) wmemmove(__VA_ARGS__)
#endif

#if !defined(GLX_WMEMCMP)
	#define GLX_WMEMCMP(...) wmemcmp(__VA_ARGS__)
#endif

#if !defined(GLX_WMEMCHR)
	#define GLX_WMEMCHR(...) wmemchr(__VA_ARGS__)
#endif

template<typename TChar>
class GlxCStringUtils
{
public:
	using CharType = TChar;
	using SizeType = GlxSizeT;

	static GLX_CONSTEXPR GlxBool IsChar = GlxIsSame<CharType, GlxChar>::Value;
	static GLX_CONSTEXPR GlxBool IsWChar = GlxIsSame<CharType, GlxWChar>::Value;

	static_assert(IsChar || IsWChar, "GlxCStringUtils<TChar> is not implemented for this char type.");

	static GLX_FORCE_INLINE SizeType Strlen(const CharType* InStr)
	{
		if constexpr (IsChar)
		{
			return strlen(InStr);
		}
		else if constexpr (IsWChar)
		{
			return wcslen(InStr);
		}
	}

	static GLX_FORCE_INLINE GlxInt32 Strcmp(const CharType* InLhs, const CharType* InRhs)
	{
		if constexpr (IsChar)
		{
			return strcmp(InLhs, InRhs);
		}
		else if constexpr (IsWChar)
		{
			return wcscmp(InLhs, InRhs);
		}
	}

	static GlxInt32 Stricmp(const CharType* InLhs, const CharType* InRhs)
	{
		GlxInt32 Diff;
		while ((Diff = GlxCharUtils<CharType>::ToUpper(*InLhs) - GlxCharUtils<CharType>::ToUpper(*InRhs)) == 0)
		{
			if (*InLhs == static_cast<CharType>(0))
			{
				return 0;
			}
			++InLhs;
			++InRhs;
		}
		return Diff > 0 ? 1 : -1;
	}

	static GLX_FORCE_INLINE GlxInt32 Strncmp(const CharType* InLhs, const CharType* InRhs, SizeType InCount)
	{
		if constexpr (IsChar)
		{
			return GLX_MEMCMP(InLhs, InRhs, InCount);
		}
		else if constexpr (IsWChar)
		{
			return GLX_WMEMCMP(InLhs, InRhs, InCount);
		}
	}

	static GlxInt32 Strnicmp(const CharType* InLhs, const CharType* InRhs, SizeType InCount)
	{
		GlxInt32 Diff;
		while (InCount > 0)
		{
			if (Diff = GlxCharUtils<CharType>::ToUpper(*InLhs) - GlxCharUtils<CharType>::ToUpper(*InRhs))
			{
				return Diff > 0 ? 1 : -1;
			}

			if (*InLhs == static_cast<CharType>(0))
			{
				return 0;
			}

			--InCount;
			++InLhs;
			++InRhs;
		}

		return 0;
	}

	static GLX_FORCE_INLINE const CharType* Strchr(const CharType* InStr, CharType InCh)
	{
		if constexpr (IsChar)
		{
			return strchr(InStr, InCh);
		}
		else if constexpr (IsWChar)
		{
			return wcschr(InStr, InCh);
		}
	}

	static GLX_FORCE_INLINE const CharType* Strnchr(const CharType* InStr, CharType InCh, SizeType InCount)
	{
		if constexpr (IsChar)
		{
			return static_cast<const CharType*>(GLX_MEMCHR(InStr, InCh, InCount));
		}
		else if constexpr (IsWChar)
		{
			return GLX_WMEMCHR(InStr, InCh, InCount);
		}
	}

	static GLX_FORCE_INLINE const CharType* Strrchr(const CharType* InStr, CharType InCh)
	{
		if constexpr (IsChar)
		{
			return strrchr(InStr, InCh);
		}
		else if constexpr (IsWChar)
		{
			return wcsrchr(InStr, InCh);
		}
	}

	static GLX_FORCE_INLINE const CharType* Strstr(const CharType* InStr, const CharType* InSubstr)
	{
		if constexpr (IsChar)
		{
			return strstr(InStr, InSubstr);
		}
		else if constexpr (IsWChar)
		{
			return wcsstr(InStr, InSubstr);
		}
	}

	static const CharType* Stristr(const CharType* InStr, const CharType* InSubstr)
	{
		if (InStr == nullptr || InSubstr == nullptr)
		{
			return nullptr;
		}

		if (*InSubstr == static_cast<CharType>(0))
		{
			return InStr;
		}

		SizeType SubstrLen = Strlen(InSubstr);
		CharType FirstUpperSubstrChar = GlxCharUtils<CharType>::ToUpper(*InSubstr);

		while (*InStr != static_cast<CharType>(0))
		{
			if (GlxCharUtils<CharType>::ToUpper(*InStr) == FirstUpperSubstrChar)
			{
				if (!Strnicmp(InStr, InSubstr, SubstrLen))
				{
					return InStr;
				}
			}

			++InStr;
		}
		return nullptr;
	}

	static const CharType* Strrstr(const CharType* InStr, const CharType* InSubstr)
	{
		if (InStr == nullptr || InSubstr == nullptr)
		{
			return nullptr;
		}

		if (*InSubstr == static_cast<CharType>(0))
		{
			return InStr + Strlen(InStr);
		}

		SizeType StrLen = Strlen(InStr);
		SizeType SubstrLen = Strlen(InSubstr);

		if (StrLen >= SubstrLen)
		{
			for (const CharType* Tmp = InStr + (StrLen - SubstrLen); Tmp >= InStr; --Tmp)
			{
				if (*Tmp == *InSubstr)
				{
					if (!Strncmp(Tmp, InSubstr, SubstrLen))
					{
						return Tmp;
					}
				}
			}
		}

		return nullptr;
	}

	static const CharType* Strristr(const CharType* InStr, const CharType* InSubstr)
	{
		if (InStr == nullptr || InSubstr == nullptr)
		{
			return nullptr;
		}

		if (*InSubstr == static_cast<CharType>(0))
		{
			return InStr + Strlen(InStr);
		}

		SizeType StrLen = Strlen(InStr);
		SizeType SubstrLen = Strlen(InSubstr);

		if (StrLen >= SubstrLen)
		{
			CharType FirstUpperSubstrChar = GlxCharUtils<CharType>::ToUpper(*InSubstr);

			for (const CharType* Tmp = InStr + (StrLen - SubstrLen); Tmp >= InStr; --Tmp)
			{
				if (GlxCharUtils<CharType>::ToUpper(*Tmp) == FirstUpperSubstrChar)
				{
					if (!Strnicmp(Tmp, InSubstr, SubstrLen))
					{
						return Tmp;
					}
				}
			}
		}

		return nullptr;
	}

	static CharType* Strupr(CharType* InStr)
	{
		CharType* Tmp = InStr;
		while (*Tmp)
		{
			*Tmp = GlxCharUtils<CharType>::ToUpper(*Tmp);
			++Tmp;
		}
		return InStr;
	}

	static CharType* Strupr(CharType* InStr, SizeType InCount)
	{
		CharType* Tmp = InStr;
		while (*Tmp && InCount > 0)
		{
			*Tmp = GlxCharUtils<CharType>::ToUpper(*Tmp);
			++Tmp;
			--InCount;
		}
		return InStr;
	}

	static CharType* Strlwr(CharType* InStr)
	{
		CharType* Tmp = InStr;
		while (*Tmp)
		{
			*Tmp = GlxCharUtils<CharType>::ToLower(*Tmp);
			++Tmp;
		}
		return InStr;
	}

	static CharType* Strlwr(CharType* InStr, SizeType InCount)
	{
		CharType* Tmp = InStr;
		while (*Tmp && InCount > 0)
		{
			*Tmp = GlxCharUtils<CharType>::ToLower(*Tmp);
			++Tmp;
			--InCount;
		}
		return InStr;
	}
};
