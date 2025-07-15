#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename T>
class GlxIsMoveAssignable : public GlxBoolConstant<std::is_move_assignable<T>::value>
{};
