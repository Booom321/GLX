#pragma once

#include "PrimaryTypes.h"
#include "Trivial.h"
#include "IsScalar.h"

template<typename T>
class GlxIsMemcpyCompatible : public GlxBoolConstant<GlxIsTriviallyCopyable<T>::Value>
{};

template<typename T>
class GlxIsMemmoveCompatible : public GlxBoolConstant<GlxIsTriviallyCopyable<T>::Value>
{};

template<typename T>
class GlxIsMemcmpCompatible : public GlxBoolConstant<GlxIsScalar<T>::Value>
{};

template<typename T>
class GlxIsMemsetCompatible : public GlxBoolConstant<GlxIsScalar<T>::Value>
{};
