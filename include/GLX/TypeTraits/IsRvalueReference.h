#pragma once

#include "BoolConstant.h"

template<typename T>
class GlxIsRvalueReference : public GlxFalseType
{};

template<typename T>
class GlxIsRvalueReference<T&&> : public GlxTrueType
{};
