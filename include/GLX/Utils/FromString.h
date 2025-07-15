#pragma once

#include "GLX/String/String.h"
#include "GLX/String/CharUtils.h"
#include "GLX/String/CStringUtils.h"

#include <cstdlib>

template<typename TChar, typename TInt>
void AtoiImpl(const TChar* InStr, TInt* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	while (GlxCharUtils<TChar>::IsSpace(*InStr))
	{
		++InStr;
	}

	GlxBool IsNegative = (*InStr == static_cast<TChar>(45));

	if (IsNegative || *InStr == static_cast<TChar>(43))
	{
		++InStr;
	}

	TInt Value = 0;

	for (; (*InStr >= static_cast<TChar>(48) && *InStr <= static_cast<TChar>(58)); ++InStr)
	{
		Value = Value * 10 + (*InStr - static_cast<TChar>(48));
	}

	*InValue = (IsNegative) ? (-1 * Value) : Value;
}

void FromString(const GlxChar* InStr, GlxInt8* InValue)
{
	AtoiImpl<GlxChar, GlxInt8>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxUInt8* InValue)
{
	AtoiImpl<GlxChar, GlxUInt8>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxInt16* InValue)
{
	AtoiImpl<GlxChar, GlxInt16>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxUInt16* InValue)
{
	AtoiImpl<GlxChar, GlxUInt16>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxInt32* InValue)
{
	AtoiImpl<GlxChar, GlxInt32>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxUInt32* InValue)
{
	AtoiImpl<GlxChar, GlxUInt32>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxInt64* InValue)
{
	AtoiImpl<GlxChar, GlxInt64>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxUInt64* InValue)
{
	AtoiImpl<GlxChar, GlxUInt64>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxInt8* InValue)
{
	AtoiImpl<GlxWChar, GlxInt8>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxUInt8* InValue)
{
	AtoiImpl<GlxWChar, GlxUInt8>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxInt16* InValue)
{
	AtoiImpl<GlxWChar, GlxInt16>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxUInt16* InValue)
{
	AtoiImpl<GlxWChar, GlxUInt16>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxInt32* InValue)
{
	AtoiImpl<GlxWChar, GlxInt32>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxUInt32* InValue)
{
	AtoiImpl<GlxWChar, GlxUInt32>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxInt64* InValue)
{
	AtoiImpl<GlxWChar, GlxInt64>(InStr, InValue);
}

void FromString(const GlxWChar* InStr, GlxUInt64* InValue)
{
	AtoiImpl<GlxWChar, GlxUInt64>(InStr, InValue);
}

void FromString(const GlxChar* InStr, GlxBool* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = !GLX_MEMCMP(InStr, "1", 1) || !GlxCStringUtils<GlxChar>::Strnicmp(InStr, "TRUE", 4);
}

void FromString(const GlxWChar* InStr, GlxBool* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = !GLX_WMEMCMP(InStr, L"1", 1) || !GlxCStringUtils<GlxWChar>::Strnicmp(InStr, L"TRUE", 4);
}

void FromString(const GlxChar* InStr, GlxFloat* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = strtof(InStr, nullptr);
}

void FromString(const GlxWChar* InStr, GlxFloat* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = wcstof(InStr, nullptr);
}

void FromString(const GlxChar* InStr, GlxDouble* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = strtod(InStr, nullptr);
}

void FromString(const GlxWChar* InStr, GlxDouble* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = wcstod(InStr, nullptr);
}

void FromString(const GlxChar* InStr, GlxLongDouble* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = strtold(InStr, nullptr);
}

void FromString(const GlxWChar* InStr, GlxLongDouble* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = wcstold(InStr, nullptr);
}

void FromString(const GlxChar* InStr, GlxString* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = InStr;
}

void FromString(const GlxWChar* InStr, GlxWString* InValue)
{
	if (!InStr || !InValue)
	{
		return;
	}

	*InValue = InStr;
}
