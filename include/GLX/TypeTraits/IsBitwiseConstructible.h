#pragma once

#include "GLX/Types/DataTypes.h"
#include "IsReference.h"
#include "RemoveCV.h"
#include "Trivial.h"
#include "TypeRelationships.h"

template<typename T, typename TArg>
class GlxIsBitwiseConstructible : public GlxFalseType
{
	static_assert(
		!GlxIsReference<T>::Value &&
		!GlxIsReference<TArg>::Value &&
		GlxIsSame<T, typename GlxRemoveCV<T>::Type>::Value &&
		GlxIsSame<TArg, typename GlxRemoveCV<TArg>::Type>::Value);
};

template<typename T>
class GlxIsBitwiseConstructible<T, T> : public GlxBoolConstant<GlxIsTriviallyConstructible<T>::Value || GlxIsTriviallyCopyable<T>::Value>
{};

template<typename TLhs, typename TRhs>
class GlxIsBitwiseConstructible<const TLhs, TRhs> : public GlxIsBitwiseConstructible<TLhs, TRhs>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class GlxIsBitwiseConstructible<const T*, T*> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxUInt8, GlxInt8> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxInt8, GlxUInt8> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxUInt16, GlxInt16> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxInt16, GlxUInt16> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxUInt32, GlxInt32> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxInt32, GlxUInt32> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxUInt64, GlxInt64> : public GlxTrueType
{};

template<>
class GlxIsBitwiseConstructible<GlxInt64, GlxUInt64> : public GlxTrueType
{};
