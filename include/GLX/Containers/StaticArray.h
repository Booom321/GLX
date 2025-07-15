#pragma once

#include "GLX/Assert.h"
#include "GLX/Memory/MemoryUtils.h"

template<typename T, GlxSizeT InCount>
class GlxStaticArray
{
public:
	using SizeType = GlxSizeT;

	using ElementType = T;
	using ReferenceType = T&;
	using PointerType = T*;
	using ConstReferenceType = const T&;
	using ConstPointerType = const T*;

	using IteratorType = T*;
	using ConstIteratorType = const T*;

	static GLX_CONSTEXPR SizeType InvalidIndex = GLX_INVALID_INDEX;
	static GLX_CONSTEXPR SizeType ElementCount = InCount;

	GlxStaticArray() = default;

	GlxStaticArray(const GlxStaticArray&) = default;
	GlxStaticArray(GlxStaticArray&&) noexcept = default;
	GlxStaticArray& operator=(const GlxStaticArray&) = default;
	GlxStaticArray& operator=(GlxStaticArray&&) noexcept = default;

	~GlxStaticArray() = default;

	GLX_FORCE_INLINE PointerType GetData()
	{
		return Elements;
	}

	GLX_FORCE_INLINE ConstPointerType GetData() const
	{
		return Elements;
	}

	GLX_FORCE_INLINE ReferenceType ElementAt(SizeType InIndex)
	{
		GLX_ASSERT(InIndex < InCount);
		return Elements[InIndex];
	}

	GLX_FORCE_INLINE ConstReferenceType ElementAt(SizeType InIndex) const
	{
		GLX_ASSERT(InIndex < InCount);
		return Elements[InIndex];
	}

	GLX_FORCE_INLINE ReferenceType operator[](SizeType InIndex)
	{
		GLX_ASSERT(InIndex < InCount);
		return Elements[InIndex];
	}

	GLX_FORCE_INLINE ConstReferenceType operator[](SizeType InIndex) const
	{
		GLX_ASSERT(InIndex < InCount);
		return Elements[InIndex];
	}

	GLX_FORCE_INLINE ReferenceType GetFirstElement()
	{
		return Elements[0];
	}

	GLX_FORCE_INLINE ConstReferenceType GetFirstElement() const
	{
		return Elements[0];
	}

	GLX_FORCE_INLINE ReferenceType GetLastElement()
	{
		return Elements[InCount - 1];
	}

	GLX_FORCE_INLINE ConstReferenceType GetLastElement() const
	{
		return Elements[InCount - 1];
	}

	GLX_FORCE_INLINE GlxBool IsEmpty() const noexcept
	{
		return InCount == 0;
	}

	GLX_FORCE_INLINE SizeType GetElementCount() const noexcept
	{
		return InCount;
	}

	GLX_FORCE_INLINE IteratorType begin()
	{
		return IteratorType(Elements);
	}

	GLX_FORCE_INLINE ConstIteratorType begin() const
	{
		return ConstIteratorType(Elements);
	}

	GLX_FORCE_INLINE IteratorType end()
	{
		return IteratorType(Elements + InCount);
	}

	GLX_FORCE_INLINE ConstIteratorType end() const
	{
		return ConstIteratorType(Elements + InCount);
	}

	GlxBool operator==(const GlxStaticArray& InOther) const
	{
		if constexpr (GlxIsMemcmpCompatible<ElementType>::Value)
		{
			return GLX_MEMCMP(Elements, InOther.Elements, InCount * sizeof(ElementType)) == 0;
		}
		else
		{
			for (SizeType Index = 0; Index < InCount; ++Index)
			{
				if (!(Elements[Index] == InOther.Elements[Index]))
				{
					return false;
				}
			}
			return true;
		}
	}

	GlxBool operator!=(const GlxStaticArray& InOther) const
	{
		return !operator==(InOther);
	}

	GLX_FORCE_INLINE SizeType Find(ConstReferenceType InItem) const
	{
		for (SizeType Index = 0; Index < InCount; ++Index)
		{
			if (Elements[Index] == InItem)
			{
				return Index;
			}
		}

		return InvalidIndex;
	}

	template<typename TPredicate>
	GLX_FORCE_INLINE SizeType FindIf(TPredicate InPred) const
	{
		for (SizeType Index = 0; Index < InCount; ++Index)
		{
			if (InPred(Elements[Index]))
			{
				return Index;
			}
		}

		return InvalidIndex;
	}

	GLX_FORCE_INLINE SizeType FindLast(ConstReferenceType InItem) const
	{
		for (SizeType Index = InCount - 1; Index > 0; --Index)
		{
			if (Elements[Index] == InItem)
			{
				return Index;
			}
		}

		return InvalidIndex;
	}

	template<typename TPredicate>
	GLX_FORCE_INLINE SizeType FindLastIf(TPredicate InPred) const
	{
		for (SizeType Index = InCount - 1; Index > 0; --Index)
		{
			if (InPred(Elements[Index]))
			{
				return Index;
			}
		}

		return InvalidIndex;
	}

	GLX_FORCE_INLINE SizeType Contains(ConstReferenceType InItem) const
	{
		for (SizeType Index = 0; Index < InCount; ++Index)
		{
			if (Elements[Index] == InItem)
			{
				return true;
			}
		}

		return false;
	}

	template<typename TPredicate>
	GLX_FORCE_INLINE SizeType ContainsIf(TPredicate InPred) const
	{
		for (SizeType Index = 0; Index < InCount; ++Index)
		{
			if (InPred(Elements[Index]))
			{
				return true;
			}
		}

		return false;
	}

	template<typename TFunc>
	GlxStaticArray ForEach(TFunc InFunc) const
	{
		GlxStaticArray Array(*this);
		for (SizeType Idx = 0; Idx < InCount; ++Idx)
		{
			InFunc(Array.Elements[Idx]);
		}
		return Array;
	}

	template<typename TFunc>
	void ForEachInternal(TFunc InFunc)
	{
		for (SizeType Idx = 0; Idx < InCount; ++Idx)
		{
			InFunc(Elements[Idx]);
		}
	}

private:
	ElementType Elements[InCount];
};
