#pragma once

#include "IsLvalueReference.h"

template<typename T>
class GlxRemoveReference
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveReference<T&>
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveReference<T&&>
{
public:
	using Type = T;
};

template<typename T>
GLX_CONSTEXPR typename GlxRemoveReference<T>::Type&& Move(T&& InObj) noexcept
{
	return static_cast<typename GlxRemoveReference<T>::Type&&>(InObj);
}

template<typename T>
GLX_CONSTEXPR T&& Forward(typename GlxRemoveReference<T>::Type& InObj) noexcept
{
	return static_cast<T&&>(InObj);
}

template<typename T>
GLX_CONSTEXPR T&& Forward(typename GlxRemoveReference<T>::Type&& InObj) noexcept
{
	static_assert(!GlxIsLvalueReference<T>::Value, "Can not forward an rvalue as an lvalue.");
	return static_cast<T&&>(InObj);
}
