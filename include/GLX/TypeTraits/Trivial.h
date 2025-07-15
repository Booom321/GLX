#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename T>
class GlxIsTrivial : public GlxBoolConstant<std::is_trivial_v<T>>
{};

template<typename T>
class GlxIsTriviallyCopyable : public GlxBoolConstant<std::is_trivially_copyable_v<T>>
{};

template<typename T>
class GlxIsTriviallyDestructible : public GlxBoolConstant<std::is_trivially_destructible_v<T>>
{};

template<typename TTo, typename TFrom>
class GlxIsTriviallyAssignable : public GlxBoolConstant<std::is_trivially_assignable_v<TTo, TFrom>>
{};

template<typename T>
class GlxIsTriviallyConstructible : public GlxBoolConstant<std::is_trivially_constructible_v<T>>
{};

template<typename T>
class GlxIsTriviallyDefaultConstructible : public GlxBoolConstant<std::is_trivially_default_constructible_v<T>>
{};

template<typename T>
class GlxIsTriviallyCopyConstructible : public GlxBoolConstant<std::is_trivially_copy_constructible_v<T>>
{};

template<typename T>
class GlxIsTriviallyMoveConstructible : public GlxBoolConstant<std::is_trivially_move_constructible_v<T>>
{};

template<typename T>
class GlxIsTriviallyCopyAssignable : public GlxBoolConstant<std::is_trivially_copy_assignable_v<T>>
{};

template<typename T>
class GlxIsTriviallyMoveAssignable : public GlxBoolConstant<std::is_trivially_move_assignable_v<T>>
{};
