#pragma once

#include "BoolConstant.h"

template<typename T>
class GlxIsLvalueReference : public GlxFalseType
{};

template<typename T>
class GlxIsLvalueReference<T&> : public GlxTrueType
{};
