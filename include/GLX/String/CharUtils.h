#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Types/DataTypes.h"
#include "GLX/TypeTraits/TypeRelationships.h"

#include <ctype.h>
#include <wctype.h>

template<typename TChar>
class GlxCharUtils
{
public:
	using CharType = TChar;

	static GLX_CONSTEXPR GlxBool IsChar = GlxIsSame<CharType, GlxChar>::Value;
	static GLX_CONSTEXPR GlxBool IsWChar = GlxIsSame<CharType, GlxWChar>::Value;

	static_assert(IsChar || IsWChar, "GlxCharUtils<TChar> is not implemented for this char type.");

	static GLX_FORCE_INLINE CharType ToLower(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return static_cast<CharType>(tolower(static_cast<GlxInt32>(InCh)));
		}
		else if constexpr (IsWChar)
		{
			return static_cast<CharType>(towlower(static_cast<wint_t>(InCh)));
		}
	}

	static GLX_FORCE_INLINE CharType ToUpper(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return static_cast<CharType>(toupper(static_cast<GlxInt32>(InCh)));
		}
		else if constexpr (IsWChar)
		{
			return static_cast<CharType>(towupper(static_cast<wint_t>(InCh)));
		}
	}

	static GLX_FORCE_INLINE GlxBool IsLower(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return islower(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswlower(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsUpper(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isupper(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswupper(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsAlpha(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isalpha(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswalpha(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsGraph(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isgraph(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswgraph(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsPrint(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isprint(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswprint(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsPunct(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return ispunct(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswpunct(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsAlnum(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isalnum(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswalnum(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsDigit(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isdigit(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswdigit(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsHexDigit(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isxdigit(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswxdigit(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsControl(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return iscntrl(static_cast<GlxInt32>(InCh)) != 0;
		}
		else if constexpr (IsWChar)
		{
			return iswcntrl(static_cast<wint_t>(InCh)) != 0;
		}
	}

	static GLX_FORCE_INLINE GlxBool IsBlank(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isblank(static_cast<GlxInt32>(InCh));
		}
		else if constexpr (IsWChar)
		{
			return iswblank(static_cast<wint_t>(InCh));
		}
	}

	static GLX_FORCE_INLINE GlxBool IsSpace(CharType InCh)
	{
		if constexpr (IsChar)
		{
			return isspace(static_cast<GlxInt32>(InCh));
		}
		else if constexpr (IsWChar)
		{
			return iswspace(static_cast<wint_t>(InCh));
		}
	}
};
