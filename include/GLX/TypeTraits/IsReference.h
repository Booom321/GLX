#pragma once

#include "BoolConstant.h"

template<typename T>
class GlxIsReference : public GlxFalseType
{};

template<typename T>
class GlxIsReference<T&> : public GlxTrueType
{};

template<typename T>
class GlxIsReference<T&&> : public GlxTrueType
{};
