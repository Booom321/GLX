#pragma once

#include "BoolConstant.h"

#include <type_traits>

template<typename TReturnType, typename TFunc, typename... TArgs>
class GlxIsInvocableR : public GlxBoolConstant<std::is_invocable_r<TReturnType, TFunc, TArgs...>::value>
{};
