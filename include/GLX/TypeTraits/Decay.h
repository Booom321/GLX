#pragma once

#include "AddPointer.h"
#include "PrimaryTypes.h"
#include "RemoveCV.h"
#include "RemoveExtent.h"
#include "RemoveReference.h"
#include "TypeChooser.h"

template<typename T>
class GlxDecay
{
	using U = typename GlxRemoveReference<T>::Type;

public:
	using Type = typename GlxTypeChooser<
		GlxIsArray<U>::Value,
		typename GlxAddPointer<typename GlxRemoveExtent<U>::Type>::Type,
		typename GlxTypeChooser<
			GlxIsFunction<U>::Value,
			typename GlxAddPointer<U>::Type,
			typename GlxRemoveCV<U>::Type>::Type>::Type;
};
