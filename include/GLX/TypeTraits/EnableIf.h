#pragma once

#include "GLX/Types/DataTypes.h"

template<GlxBool InVal, typename TResult = void>
class GlxEnableIf;

template<typename TResult>
class GlxEnableIf<true, TResult>
{
public:
	using Type = TResult;
};

template<typename TResult>
class GlxEnableIf<false, TResult>
{};
