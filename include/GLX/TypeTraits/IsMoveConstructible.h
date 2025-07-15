#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename T>
class GlxIsMoveConstructible : public GlxBoolConstant<std::is_move_constructible<T>::value>
{};
