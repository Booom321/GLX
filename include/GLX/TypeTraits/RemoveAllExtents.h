#pragma once

#include "GLX/Types/DataTypes.h"

template<typename T>
class GlxRemoveAllExtents
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveAllExtents<T[]>
{
public:
	using Type = typename GlxRemoveAllExtents<T>::Type;
};

template<typename T, GlxSizeT InN>
class GlxRemoveAllExtents<T[InN]>
{
public:
	using Type = typename GlxRemoveAllExtents<T>::Type;
};
