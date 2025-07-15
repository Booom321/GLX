#pragma once

#include "GLX/Types/DataTypes.h"

template<typename T>
class GlxRemoveExtent
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveExtent<T[]>
{
public:
	using Type = T;
};

template<typename T, GlxSizeT InN>
class GlxRemoveExtent<T[InN]>
{
public:
	using Type = T;
};
