#pragma once

#include "BoolConstant.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... TRest>
class GlxAnd;

template<GlxBool InVal, typename... TRest>
class GlxAndValue : public GlxBoolConstant<GlxAnd<TRest...>::Value>
{};

template<typename... TRest>
class GlxAndValue<false, TRest...> : public GlxFalseType
{};

template<typename TFirst, typename... TRest>
class GlxAnd<TFirst, TRest...> : public GlxAndValue<TFirst::Value, TRest...>
{};

template<>
class GlxAnd<> : public GlxTrueType
{};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... TRest>
class GlxOr;

template<GlxBool InVal, typename... TRest>
class GlxOrValue : public GlxBoolConstant<GlxOr<TRest...>::Value>
{};

template<typename... TRest>
class GlxOrValue<true, TRest...> : public GlxTrueType
{};

template<typename TFirst, typename... TRest>
class GlxOr<TFirst, TRest...> : public GlxOrValue<TFirst::Value, TRest...>
{};

template<>
class GlxOr<> : public GlxFalseType
{};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TType>
class GlxNot : public GlxBoolConstant<!TType::Value>
{};
