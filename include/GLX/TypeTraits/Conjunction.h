#pragma once

#include "BoolConstant.h"
#include "TypeChooser.h"

template<typename...>
class GlxConjunction : public GlxTrueType
{};

template<typename TType>
class GlxConjunction<TType> : public TType
{};

template<typename TFirst, typename... TRest>
class GlxConjunction<TFirst, TRest...> : public GlxTypeChooser<TFirst::Value, GlxConjunction<TRest...>, TFirst>::Type
{};
