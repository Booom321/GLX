#pragma once

#include "GLX/String/String.h"
#include <wchar.h>

static GlxInt32 Precision = 6;

void SetPrecision(GlxInt32 InPrecision)
{
	Precision = InPrecision;
}

template<typename TInt, typename TChar>
TChar* IntegerToCharBuffer(TInt InNum, TChar* InEndPtr, GlxInt64& InLength)
{
	const TChar* EndPtr = InEndPtr;
	const TInt Temp = InNum;

	if constexpr (std::is_signed<TInt>::value)
	{
		InNum = (InNum < 0) ? -InNum : InNum;
	}

	do
	{
		*--InEndPtr = static_cast<TChar>(InNum % 10 + 48);
		InNum /= 10;
	} while (InNum != 0);

	if constexpr (std::is_signed<TInt>::value)
	{
		if (Temp < 0)
		{
			*--InEndPtr = static_cast<TChar>(45);
		}
	}

	InLength = static_cast<GlxInt64>(EndPtr - InEndPtr);
	return InEndPtr;
}

template<typename TFloat, typename TChar>
void FloatToString(TFloat InValue, GlxBasicString<TChar>& InStr)
{
	InStr.Resize(128);

	if constexpr (GlxIsSame<TChar, GlxChar>::Value)
	{
		sprintf(InStr.GetData(), "%.*Lf", Precision, static_cast<GlxLongDouble>(InValue));
	}
	else if constexpr (GlxIsSame<TChar, GlxWChar>::Value)
	{
		swprintf(InStr.GetData(), InStr.GetElementCount(), L"%.*Lf", Precision, static_cast<GlxLongDouble>(InValue));
	}
}

#define GLX_TO_STRING(InCharType, InValue, InStr, InBufferSize)                                   \
	InCharType Buffer[InBufferSize];                                                              \
	GlxInt64 Length;                                                                              \
	InCharType* Ptr = IntegerToCharBuffer(InValue, Buffer + GLX_GET_ARRAY_COUNT(Buffer), Length); \
	InStr.Assign(Ptr, Length)

void ToString(GlxInt8 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 5);
}

void ToString(GlxUInt8 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 5);
}

void ToString(GlxInt16 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 7);
}

void ToString(GlxUInt16 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 7);
}

void ToString(GlxInt32 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 12);
}

void ToString(GlxUInt32 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 12);
}

void ToString(GlxInt64 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 21);
}

void ToString(GlxUInt64 InValue, GlxString& InStr)
{
	GLX_TO_STRING(GlxChar, InValue, InStr, 21);
}

void ToString(GlxInt8 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 5);
}

void ToString(GlxUInt8 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 5);
}

void ToString(GlxInt16 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 7);
}

void ToString(GlxUInt16 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 7);
}

void ToString(GlxInt32 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 12);
}

void ToString(GlxUInt32 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 12);
}

void ToString(GlxInt64 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 21);
}

void ToString(GlxUInt64 InValue, GlxWString& InStr)
{
	GLX_TO_STRING(GlxWChar, InValue, InStr, 21);
}

void ToString(GlxBool InValue, GlxString& InStr)
{
	InValue ? InStr.Assign("1", 1) : InStr.Assign("0", 1);
}

void ToString(GlxBool InValue, GlxWString& InStr)
{
	InValue ? InStr.Assign(L"1", 1) : InStr.Assign(L"0", 1);
}

void ToString(GlxFloat InValue, GlxString& InStr)
{
	FloatToString(InValue, InStr);
}

void ToString(GlxDouble InValue, GlxString& InStr)
{
	FloatToString(InValue, InStr);
}

void ToString(GlxLongDouble InValue, GlxString& InStr)
{
	FloatToString(InValue, InStr);
}

void ToString(GlxFloat InValue, GlxWString& InStr)
{
	FloatToString(InValue, InStr);
}

void ToString(GlxDouble InValue, GlxWString& InStr)
{
	FloatToString(InValue, InStr);
}

void ToString(GlxLongDouble InValue, GlxWString& InStr)
{
	FloatToString(InValue, InStr);
}

void ToString(const GlxChar* InValue, GlxString& InStr)
{
	InStr = InValue;
}

void ToString(const GlxWChar* InValue, GlxWString& InStr)
{
	InStr = InValue;
}

void ToString(const GlxString& InValue, GlxString& InStr)
{
	InStr = InValue;
}

void ToString(const GlxWString& InValue, GlxWString& InStr)
{
	InStr = InValue;
}

