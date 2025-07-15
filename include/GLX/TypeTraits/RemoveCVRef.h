#pragma once

#include "RemoveCV.h"
#include "RemoveReference.h"

template<typename T>
class GlxRemoveCVRef
{
public:
	using Type = typename GlxRemoveCV<typename GlxRemoveReference<T>::Type>::Type;
};
