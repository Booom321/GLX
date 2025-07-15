#pragma once

#include "GLX/Preprocessor.h"

#include <limits>

template<typename T>
class GlxNumericLimits
{
public:
	static GLX_CONSTEXPR T Max()
	{
		return std::numeric_limits<T>::max();
	}

	static GLX_CONSTEXPR T Min()
	{
		return std::numeric_limits<T>::min();
	}

	static GLX_CONSTEXPR T Lowest()
	{
		return std::numeric_limits<T>::lowest();
	}
};

template<typename T>
class GlxNumericLimits<const T> : public GlxNumericLimits<T>
{};

template<typename T>
class GlxNumericLimits<volatile T> : public GlxNumericLimits<T>
{};

template<typename T>
class GlxNumericLimits<const volatile T> : public GlxNumericLimits<T>
{};
