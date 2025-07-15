#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename T>
class GlxIsDefaultConstructible : public GlxBoolConstant<std::is_default_constructible<T>::value>
{};
