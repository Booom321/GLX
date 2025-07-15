#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Types/DataTypes.h"

class GlxTrueType
{
public:
	static GLX_CONSTEXPR GlxBool Value = true;
};

class GlxFalseType
{
public:
	static GLX_CONSTEXPR GlxBool Value = false;
};

template<GlxBool InVal>
class GlxBoolConstant
{
public:
	static GLX_CONSTEXPR GlxBool Value = InVal;
};
