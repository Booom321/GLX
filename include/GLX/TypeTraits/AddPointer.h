#pragma once

#include <type_traits>

template<typename T>
class GlxAddPointer
{
public:
	using Type = std::add_pointer_t<T>;
};
