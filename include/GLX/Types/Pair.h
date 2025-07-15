#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/TypeTraits/RemoveReference.h"

template<typename T, typename U>
class GlxPair
{
public:
	GLX_INLINE GlxPair() = default;

	GLX_INLINE GlxPair(const T& InFirst, const U& InSecond)
		: First(InFirst), Second(InSecond)
	{}

	GLX_INLINE GlxPair(T&& InFirst, U&& InSecond) noexcept
		: First(Move(InFirst)), Second(Move(InSecond))
	{}

	GLX_INLINE GlxPair(T&& InFirst, const U& InSecond) noexcept
		: First(Move(InFirst)), Second(InSecond)
	{}

	GLX_INLINE GlxPair(const T& InFirst, U&& InSecond) noexcept
		: First(InFirst), Second(Move(InSecond))
	{}

	GLX_INLINE GlxPair(const GlxPair& InOther)
		: First(InOther.First), Second(InOther.Second)
	{}

	GLX_INLINE GlxPair(GlxPair&& InOther) noexcept
		: First(Move(InOther.First)), Second(Move(InOther.Second))
	{}

	~GlxPair() = default;

	GLX_INLINE GlxBool operator==(const GlxPair& InOther) const
	{
		return First == InOther.First && Second == InOther.Second;
	}

	GLX_INLINE GlxBool operator!=(const GlxPair& InOther) const
	{
		return First != InOther.First || Second != InOther.Second;
	}

	GlxPair& operator=(const GlxPair& InOther)
	{
		if (this != &InOther)
		{
			First = InOther.First;
			Second = InOther.Second;
		}
		return *this;
	}

	GlxPair& operator=(GlxPair&& InOther) noexcept
	{
		if (this != &InOther)
		{
			First = Move(InOther.First);
			Second = Move(InOther.Second);
		}
		return *this;
	}

	T First;
	U Second;
};

template<typename T, typename U>
GLX_INLINE GlxPair<T, U> MakePair(const T& InFirst, const U& InSecond)
{
	return GlxPair<T, U>(InFirst, InSecond);
}
