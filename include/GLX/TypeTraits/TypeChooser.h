#pragma once

#include "GLX/Types/DataTypes.h"

template<GlxBool InVal, typename TTypeIfTrue, typename TTypeIfFalse>
class GlxTypeChooser
{
public:
	using Type = TTypeIfTrue;
};

template<typename TTypeIfTrue, typename TTypeIfFalse>
class GlxTypeChooser<false, TTypeIfTrue, TTypeIfFalse>
{
public:
	using Type = TTypeIfFalse;
};
