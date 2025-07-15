#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename TLhs, typename TRhs>
class GlxIsSame : public GlxBoolConstant<std::is_same_v<TLhs, TRhs>>
{};

template<typename TBase, typename TDerived>
class GlxIsBaseOf : public GlxBoolConstant<std::is_base_of_v<TBase, TDerived>>
{};

template<typename TFrom, typename TTo>
class GlxIsConvertible : public GlxBoolConstant<std::is_convertible_v<TFrom, TTo>>
{};
