#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename TFunc, typename... TArgs>
class GlxIsInvocable : public GlxBoolConstant<std::is_invocable<TFunc, TArgs...>::value>
{};
