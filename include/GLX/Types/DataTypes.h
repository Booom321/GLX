#pragma once

#include <cstddef>

using GlxByte = unsigned char;

// Unsigned int types
using GlxUInt8 = unsigned char;
using GlxUInt16 = unsigned short;
using GlxUInt32 = unsigned int;
using GlxUInt64 = unsigned long long;

// Signed int types
using GlxInt8 = signed char;
using GlxInt16 = signed short;
using GlxInt32 = signed int;
using GlxInt64 = signed long long;

using GlxSizeT = std::size_t;

// Floating point types
using GlxFloat = float;
using GlxDouble = double;
using GlxLongDouble = long double;

// Boolean type
using GlxBool = bool;

// Char types
using GlxChar = char;
using GlxWChar = wchar_t;
#if defined(__cpp_char8_t)
using GlxChar8 = char8_t;
#endif
using GlxChar16 = char16_t;
using GlxChar32 = char32_t;

// nullptr
using GlxNullPtr = std::nullptr_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(GlxByte) == 1, "The size of GlxByte must be equal to 1.");

static_assert(sizeof(GlxUInt8) == 1, "The size of GlxUInt8 must be equal to 1.");
static_assert(sizeof(GlxUInt16) == 2, "The size of GlxUInt16 must be equal to 2.");
static_assert(sizeof(GlxUInt32) == 4, "The size of GlxUInt32 must be equal to 4.");
static_assert(sizeof(GlxUInt64) == 8, "The size of GlxUInt64 must be equal to 8.");

static_assert(sizeof(GlxInt8) == 1, "The size of GlxInt8 must be equal to 1.");
static_assert(sizeof(GlxInt16) == 2, "The size of GlxInt16 must be equal to 2.");
static_assert(sizeof(GlxInt32) == 4, "The size of GlxInt32 must be equal to 4.");
static_assert(sizeof(GlxInt64) == 8, "The size of GlxInt64 must be equal to 8.");

static_assert(sizeof(GlxFloat) == 4, "The size of GlxFloat must be equal to 4.");
static_assert(sizeof(GlxDouble) == 8, "The size of GlxDouble must be equal to 8.");

static_assert(sizeof(GlxBool) == 1, "The size of GlxBool must be equal to 1.");

static_assert(sizeof(GlxChar) == 1, "The size of GlxChar must be equal to 1.");
static_assert(sizeof(GlxWChar) == 2 || sizeof(GlxWChar) == 4, "The size of GlxWChar must be equal to 2 or 4.");
