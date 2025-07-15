#pragma once

#include "BoolConstant.h"
#include <type_traits>

template<typename T>
class GlxIsStandardLayout : public GlxBoolConstant<std::is_standard_layout_v<T>>
{};
