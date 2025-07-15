#pragma once

#include "BoolConstant.h"
#include <type_traits>

template<typename T>
class GlxIsScalar : public GlxBoolConstant<std::is_scalar_v<T>>
{};
