#pragma once

#include "GLX/Assert.h"
#include "GLX/Memory/MemoryUtils.h"
#include "GLX/TypeTraits/TypeChooser.h"
#include "GLX/TypeTraits/IsMoveAssignable.h"
#include "GLX/TypeTraits/IsMoveConstructible.h"

#include <initializer_list>

template<typename T>
class GlxDynamicArray
{
public:
	using SizeType = GlxInt64;

	using ElementType = T;
	using ReferenceType = T&;
	using PointerType = T*;
	using ConstReferenceType = const T&;
	using ConstPointerType = const T*;

	using IteratorType = T*;
	using ConstIteratorType = const T*;

	static GLX_CONSTEXPR SizeType InvalidIndex = GLX_INVALID_INDEX;
	static GLX_CONSTEXPR GlxFloat GrowthFactor = 2.0f;

private:
	void Initialize(SizeType InElementCount, ConstPointerType InElements)
	{
		Data = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

		if (InElementCount > 0 && InElements)
		{
			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(Data, InElements, InElementCount * sizeof(ElementType));
			}
			else
			{
				for (SizeType Idx = 0; Idx < InElementCount; ++Idx)
				{
					new (Data + Idx) ElementType(InElements[Idx]);
				}
			}
		}
	}

	template<GlxBool InUseMove>
	void Reallocate(SizeType InNewCap, typename GlxTypeChooser<InUseMove, PointerType, ConstPointerType>::Type InElements, SizeType InElementCount)
	{
		PointerType NewData = static_cast<PointerType>(GLX_MALLOC(InNewCap * sizeof(ElementType)));

		if (InElementCount > 0 && InElements)
		{
			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData, InElements, InElementCount * sizeof(ElementType));
			}
			else
			{
				for (SizeType Idx = 0; Idx < InElementCount; ++Idx)
				{
					if constexpr (InUseMove)
					{
						new (NewData + Idx) ElementType(Move(InElements[Idx]));
					}
					else
					{
						new (NewData + Idx) ElementType(InElements[Idx]);
					}
				}
			}
		}

		if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
		{
			for (SizeType Idx = 0; Idx < Length; ++Idx)
			{
				Data[Idx].~ElementType();
			}
		}

		GLX_FREE(Data);
		Data = NewData;
		Capacity = InNewCap;
	}

public:
	GlxDynamicArray()
		: Data(nullptr), Length(0), Capacity(0)
	{}

	GlxDynamicArray(ConstPointerType InElements, SizeType InElementCount)
	{
		GLX_ASSERT(InElementCount >= 0);
		Length = InElementCount;
		Capacity = InElementCount;
		Initialize(InElementCount, InElements);
	}

	GlxDynamicArray(ConstPointerType InElements, SizeType InElementCount, SizeType InExtraCapacity)
	{
		GLX_ASSERT(InElementCount >= 0 && InExtraCapacity >= 0);
		Length = InElementCount;
		Capacity = InElementCount + InExtraCapacity;
		Initialize(InElementCount, InElements);
	}

	GlxDynamicArray(std::initializer_list<ElementType> InElementList)
		: Length(static_cast<SizeType>(InElementList.size())), Capacity(Length)
	{
		Initialize(Length, InElementList.begin());
	}

	GlxDynamicArray(const GlxDynamicArray& InOther)
		: Length(InOther.Length), Capacity(InOther.Capacity)
	{
		Initialize(InOther.Length, InOther.Data);
	}

	GlxDynamicArray(GlxDynamicArray&& InOther) noexcept
		: Data(InOther.Data), Length(InOther.Length), Capacity(InOther.Capacity)
	{
		InOther.Data = nullptr;
		InOther.Length = 0;
		InOther.Capacity = 0;
	}

	GlxDynamicArray(const GlxDynamicArray& InArray, SizeType InStartPos, SizeType InElementCount)
	{
		GLX_ASSERT(InStartPos >= 0 && InElementCount >= 0 && InStartPos + InElementCount <= InArray.Length);
		Length = InElementCount;
		Capacity = InElementCount;
		Initialize(Length, InArray.Data + InStartPos);
	}

	explicit GlxDynamicArray(SizeType InInitialCapacity)
		: Length(0)
	{
		GLX_ASSERT(InInitialCapacity >= 0);
		Capacity = InInitialCapacity;
		Data = static_cast<PointerType>(GLX_MALLOC(InInitialCapacity * sizeof(ElementType)));
	}

	GlxDynamicArray(ConstIteratorType InStart, ConstIteratorType InEnd)
	{
		GLX_ASSERT(InEnd >= InStart);
		Length = static_cast<SizeType>(InEnd - InStart);
		Capacity = Length;
		Initialize(Length, InStart);
	}

	~GlxDynamicArray()
	{
		Release();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Release()
	{
		if (Data)
		{
			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					Data[Idx].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = nullptr;
			Length = 0;
			Capacity = 0;
		}
	}

	GLX_FORCE_INLINE SizeType GetElementCount() const
	{
		return Length;
	}

	GLX_FORCE_INLINE SizeType GetCapacity() const
	{
		return Capacity;
	}

	GLX_FORCE_INLINE SizeType GetRemainingCapacity() const
	{
		return Capacity - Length;
	}

	GLX_FORCE_INLINE PointerType GetData()
	{
		return Data;
	}

	GLX_FORCE_INLINE ConstPointerType GetData() const
	{
		return Data;
	}

	GLX_FORCE_INLINE GlxBool IsEmpty() const
	{
		return Length == 0;
	}

	GLX_FORCE_INLINE ReferenceType ElementAt(SizeType InIndex)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex < Length);
		return Data[InIndex];
	}

	GLX_FORCE_INLINE ConstReferenceType ElementAt(SizeType InIndex) const
	{
		GLX_ASSERT(InIndex >= 0 && InIndex < Length);
		return Data[InIndex];
	}

	GLX_FORCE_INLINE ReferenceType operator[](SizeType InIndex)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex < Length);
		return Data[InIndex];
	}

	GLX_FORCE_INLINE ConstReferenceType operator[](SizeType InIndex) const
	{
		GLX_ASSERT(InIndex >= 0 && InIndex < Length);
		return Data[InIndex];
	}

	GLX_FORCE_INLINE ReferenceType GetFirstElement()
	{
		GLX_ASSERT(Length > 0);
		return Data[0];
	}

	GLX_FORCE_INLINE ConstReferenceType GetFirstElement() const
	{
		GLX_ASSERT(Length > 0);
		return Data[0];
	}

	GLX_FORCE_INLINE ReferenceType GetLastElement()
	{
		GLX_ASSERT(Length > 0);
		return Data[Length - 1];
	}

	GLX_FORCE_INLINE ConstReferenceType GetLastElement() const
	{
		GLX_ASSERT(Length > 0);
		return Data[Length - 1];
	}

	GLX_FORCE_INLINE IteratorType begin()
	{
		return IteratorType(Data);
	}

	GLX_FORCE_INLINE ConstIteratorType begin() const
	{
		return ConstIteratorType(Data);
	}

	GLX_FORCE_INLINE IteratorType end()
	{
		return IteratorType(Data + Length);
	}

	GLX_FORCE_INLINE ConstIteratorType end() const
	{
		return ConstIteratorType(Data + Length);
	}

	void Assign(SizeType InNewLength, ConstPointerType InElements)
	{
		if (InNewLength > Capacity)
		{
			Reallocate<false>(InNewLength, InElements, InNewLength);
		}
		else
		{
			GlxBool B = Length >= InNewLength;
			if (B)
			{
				if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
				{
					SizeType Count = Length - InNewLength;
					PointerType Dest = Data + InNewLength;

					while (Count)
					{
						Dest->~ElementType();
						++Dest, --Count;
					}
				}
			}

			SizeType Count = B ? InNewLength : Length;

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(Data, InElements, Count * sizeof(ElementType));
			}
			else
			{
				for (SizeType Idx = 0; Idx < Count; ++Idx)
				{
					Data[Idx] = InElements[Idx];
				}
			}

			if (!B)
			{
				PointerType Dest = Data + Count;
				ConstPointerType Source = InElements + Count;
				Count = InNewLength - Length;

				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					GLX_MEMCPY(Dest, Source, Count * sizeof(ElementType));
				}
				else
				{
					while (Count)
					{
						new (Dest) ElementType(*Source);
						++Dest, ++Source, --Count;
					}
				}
			}
		}

		Length = InNewLength;
	}

	GLX_FORCE_INLINE GlxDynamicArray& operator=(std::initializer_list<ElementType> InElementList)
	{
		Assign(static_cast<SizeType>(InElementList.size()), InElementList.begin());
		return *this;
	}

	GLX_FORCE_INLINE GlxDynamicArray& operator=(const GlxDynamicArray& InOther)
	{
		if (this != &InOther)
		{
			Assign(InOther.Length, InOther.Data);
		}

		return *this;
	}

	GlxDynamicArray& operator=(GlxDynamicArray&& InOther) noexcept
	{
		if (this != &InOther)
		{
			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					Data[Idx].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = InOther.Data;
			Length = InOther.Length;
			Capacity = InOther.Capacity;

			InOther.Data = nullptr;
			InOther.Length = 0;
			InOther.Capacity = 0;
		}

		return *this;
	}

	GLX_FORCE_INLINE void Clear()
	{
		if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
		{
			for (SizeType Idx = 0; Idx < Length; ++Idx)
			{
				Data[Idx].~ElementType();
			}
		}
		Length = 0;
	}

	GLX_FORCE_INLINE void Reserve(SizeType InNewCapacity)
	{
		if (InNewCapacity > Capacity)
		{
			Reallocate<true>(InNewCapacity, Data, Length);
		}
	}

	GLX_FORCE_INLINE void Shrink()
	{
		if (Capacity != Length)
		{
			Reallocate<true>(Length, Data, Length);
		}
	}

	void Resize(SizeType InNewLength)
	{
		GLX_ASSERT(InNewLength >= 0);

		if (Length == InNewLength)
		{
			return;
		}

		if (Length > InNewLength)
		{
			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				GlxMemoryUtils::DestructElements<ElementType, SizeType>(Data + InNewLength, Length - InNewLength);
			}
		}
		else
		{
			if (InNewLength > Capacity)
			{
				Reallocate<true>(InNewLength, Data, Length);
			}

			SizeType Count = InNewLength - Length;
			if constexpr (GlxIsMemsetCompatible<ElementType>::Value)
			{
				GLX_MEMSET(Data + Length, 0, Count * sizeof(ElementType));
			}
			else
			{
				PointerType Dest = Data + Length;
				while (Count)
				{
					new (Dest) ElementType();
					++Dest, --Count;
				}
			}
		}
		Length = InNewLength;
	}

	GLX_NODISCARD SizeType Find(ConstReferenceType InItem) const
	{
		for (const ElementType* Start = Data, *End = Data + Length; Start != End; ++Start)
		{
			if (*Start == InItem)
			{
				return static_cast<SizeType>(Start - Data);
			}
		}

		return InvalidIndex;
	}

	GLX_NODISCARD SizeType FindLast(ConstReferenceType InItem) const
	{
		for (const ElementType* End = Data + Length; End != Data;)
		{
			--End;
			if (*End == InItem)
			{
				return static_cast<SizeType>(End - Data);
			}
		}
		return InvalidIndex;
	}

	GLX_NODISCARD GlxBool Contains(ConstReferenceType InItem) const
	{
		for (const ElementType* Start = Data, *End = Data + Length; Start != End; ++Start)
		{
			if (*Start == InItem)
			{
				return true;
			}
		}

		return false;
	}

	template<typename TPredicate>
	GLX_NODISCARD SizeType FindIf(TPredicate InPred) const
	{
		for (const ElementType* Start = Data, *End = Data + Length; Start != End; ++Start)
		{
			if (InPred(*Start))
			{
				return static_cast<SizeType>(Start - Data);
			}
		}

		return InvalidIndex;
	}

	template<typename TPredicate>
	GLX_NODISCARD SizeType FindLastIf(TPredicate InPred) const
	{
		for (const ElementType* End = Data + Length; End != Data;)
		{
			--End;
			if (InPred(*End))
			{
				return static_cast<SizeType>(End - Data);
			}
		}
		return InvalidIndex;
	}

	template<typename TPredicate>
	GLX_NODISCARD GlxBool ContainsIf(TPredicate InPred) const
	{
		for (const ElementType* Start = Data, *End = Data + Length; Start != End; ++Start)
		{
			if (InPred(*Start))
			{
				return true;
			}
		}

		return false;
	}

	template<typename TPredicate>
	void Filter(TPredicate InPred, GlxDynamicArray& InArray) const
	{
		for (const ElementType* Start = Data, *End = Data + Length; Start != End; ++Start)
		{
			if (InPred(*Start))
			{
				InArray.EmplaceBack(*Start);
			}
		}
	}

	GlxBool operator==(const GlxDynamicArray& InArray) const
	{
		if (Length != InArray.Length)
		{
			return false;
		}

		if constexpr (GlxIsMemcmpCompatible<ElementType>::Value)
		{
			return !Length || !GLX_MEMCMP(Data, InArray.Data, Length * sizeof(ElementType));
		}
		else
		{
			for (SizeType Idx = 0; Idx < Length; ++Idx)
			{
				if (!(Data[Idx] == InArray.Data[Idx]))
				{
					return false;
				}
			}
			return true;
		}
	}

	GLX_FORCE_INLINE GlxBool operator!=(const GlxDynamicArray& InArray) const
	{
		return !operator==(InArray);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename... TArgs>
	void EmplaceBack(TArgs&&... InArgs)
	{
		if (Length >= Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + 1);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

			new (NewData + Length) ElementType(Forward<TArgs>(InArgs)...);

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			}
			else
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (NewData + Idx) ElementType(Move(Data[Idx]));
					}
					else
					{
						new (NewData + Idx) ElementType(Data[Idx]);
					}
				}

				if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
				{
					for (SizeType Idx = 0; Idx < Length; ++Idx)
					{
						Data[Idx].~ElementType();
					}
				}
			}

			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			new (Data + Length) ElementType(Forward<TArgs>(InArgs)...);
		}
		++Length;
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE ReferenceType EmplaceBackGetRef(TArgs&&... InArgs)
	{
		EmplaceBack(Forward<TArgs>(InArgs)...);
		return Data[Length - 1];
	}

	SizeType AddDefaulted(SizeType InCount = 1)
	{
		GLX_ASSERT(InCount >= 0);

		if (Length + InCount >= Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InCount);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			}
			else
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (NewData + Idx) ElementType(Move(Data[Idx]));
					}
					else
					{
						new (NewData + Idx) ElementType(Data[Idx]);
					}
				}
			}

			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Index = 0; Index < Length; ++Index)
				{
					Data[Index].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = NewData;
		}

		SizeType Index = Length;
		if constexpr (GlxIsMemsetCompatible<ElementType>::Value)
		{
			GLX_MEMSET(Data + Index, 0, InCount * sizeof(ElementType));
		}
		else
		{
			PointerType Dest = Data + Index;
			SizeType Count = InCount;
			while (Count)
			{
				new (Dest) ElementType();
				++Dest;
				--Count;
			}
		}

		Length += InCount;
		return Index;
	}

	ReferenceType AddDefaultedGetRef()
	{
		SizeType Index = AddDefaulted();
		return Data[Index];
	}

	GlxBool AddUnique(ConstReferenceType InVal)
	{
		if (Contains(InVal))
		{
			return false;
		}

		EmplaceBack(InVal);
		return true;
	}

	template<typename TFunc>
	GlxDynamicArray ForEach(TFunc InFunc) const
	{
		GlxDynamicArray Array(Data, Length);
		for (SizeType Idx = 0; Idx < Length; ++Idx)
		{
			InFunc(Array.Data[Idx]);
		}
		return Array;
	}

	template<typename TFunc>
	void ForEachInternal(TFunc InFunc)
	{
		for (SizeType Idx = 0; Idx < Length; ++Idx)
		{
			InFunc(Data[Idx]);
		}
	}

	SizeType RemoveAt(SizeType InIndex, SizeType InCount = 1)
	{
		GLX_ASSERT(InIndex >= 0 && InCount >= 0 && InIndex + InCount <= Length);

		Length -= InCount;
		PointerType Dest = Data + InIndex;

		if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
		{
			GLX_MEMCPY(Dest, Dest + InCount, (Length - InIndex) * sizeof(ElementType));
		}
		else
		{
			PointerType Source = Dest + InCount;
			for (SizeType Idx = 0, Cnt = Length - InIndex; Idx < Cnt; ++Idx)
			{
				if constexpr (GlxIsMoveAssignable<ElementType>::Value)
				{
					Dest[Idx] = Move(Source[Idx]);
				}
				else
				{
					Dest[Idx] = Source[Idx];
				}
			}
		}

		if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
		{
			Dest = Data + Length;

			for (SizeType Idx = 0; Idx < InCount; ++Idx)
			{
				Dest[Idx].~ElementType();
			}
		}

		return InIndex;
	}

	SizeType Remove(ConstReferenceType InItem)
	{
		SizeType Index = Find(InItem);

		if (Index == InvalidIndex)
		{
			return InvalidIndex;
		}

		return RemoveAt(Index);
	}

	SizeType RemoveLast(ConstReferenceType InItem)
	{
		SizeType Index = FindLast(InItem);

		if (Index == InvalidIndex)
		{
			return InvalidIndex;
		}

		return RemoveAt(Index);
	}

	void RemoveAll(ConstReferenceType InItem)
	{
		for (SizeType Idx = Length - 1; Idx >= 0; --Idx)
		{
			if (Data[Idx] == InItem)
			{
				RemoveAt(Idx);

				if (Length == 0)
				{
					break;
				}
			}
		}
	}

	template<typename TPredicate>
	SizeType RemoveIf(TPredicate InPred)
	{
		SizeType Index = FindIf(InPred);

		if (Index == InvalidIndex)
		{
			return InvalidIndex;
		}

		return RemoveAt(Index);
	}

	template<typename TPredicate>
	SizeType RemoveLastIf(TPredicate InPred)
	{
		SizeType Index = FindLastIf(InPred);

		if (Index == InvalidIndex)
		{
			return InvalidIndex;
		}

		return RemoveAt(Index);
	}

	template<typename TPredicate>
	void RemoveAllIf(TPredicate InPred)
	{
		for (SizeType Idx = Length - 1; Idx >= 0; --Idx)
		{
			if (InPred(Data[Idx]))
			{
				RemoveAt(Idx);

				if (Length == 0)
				{
					break;
				}
			}
		}
	}

	ElementType Pop()
	{
		ElementType Item(Data[Length - 1]);
		RemoveAt(Length - 1);
		return Item;
	}

	void Append(SizeType InCount, ConstPointerType InElements)
	{
		GLX_ASSERT(InCount >= 0);

		if (Length + InCount >= Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InCount);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData + Length, InElements, InCount * sizeof(ElementType));
				GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			}
			else
			{
				PointerType Dest = NewData + Length;

				for (SizeType Idx = 0; Idx < InCount; ++Idx)
				{
					new (Dest + Idx) ElementType(InElements[Idx]);
				}

				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (NewData + Idx) ElementType(Move(Data[Idx]));
					}
					else
					{
						new (NewData + Idx) ElementType(Data[Idx]);
					}
				}
			}

			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					Data[Idx].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(Data + Length, InElements, InCount * sizeof(ElementType));
			}
			else
			{
				PointerType Dest = Data + Length;

				for (SizeType Idx = 0; Idx < InCount; ++Idx)
				{
					new (Dest + Idx) ElementType(InElements[Idx]);
				}
			}
		}

		Length += InCount;
	}

	void Append(SizeType InCount, ConstReferenceType InItem)
	{
		GLX_ASSERT(InCount >= 0);

		if (Length + InCount >= Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InCount);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

			PointerType Dest = NewData + Length;
			for (SizeType Idx = 0; Idx < InCount; ++Idx)
			{
				new (Dest + Idx) ElementType(InItem);
			}

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			}
			else
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (NewData + Idx) ElementType(Move(Data[Idx]));
					}
					else
					{
						new (NewData + Idx) ElementType(Data[Idx]);
					}
				}
			}

			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					Data[Idx].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			PointerType Dest = Data + Length;
			for (SizeType Idx = 0; Idx < InCount; ++Idx)
			{
				new (Dest + Idx) ElementType(InItem);
			}
		}

		Length += InCount;
	}

	void Append(std::initializer_list<ElementType> InElementList)
	{
		Append(InElementList.size(), InElementList.begin());
	}

	void Append(const GlxDynamicArray& InArray)
	{
		Append(InArray.Length, InArray.Data);
	}

	void Append(ConstIteratorType InFirst, ConstIteratorType InLast)
	{
		Append(static_cast<SizeType>(InLast - InFirst), InFirst);
	}

	GlxDynamicArray& operator+=(const GlxDynamicArray& InArray)
	{
		Append(InArray.Length, InArray.Data);
		return *this;
	}

	GlxDynamicArray& operator+=(std::initializer_list<ElementType> InElementList)
	{
		Append(InElementList.size(), InElementList.begin());
		return *this;
	}

	template<typename... TArgs>
	SizeType EmplaceAt(SizeType InIndex, TArgs&&... InArgs)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex <= Length);

		if (InIndex == Length)
		{
			EmplaceBack(Forward<TArgs>(InArgs)...);
			return InIndex;
		}

		if (Length == Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + 1);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

			new (NewData + InIndex) ElementType(Forward<TArgs>(InArgs)...);

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData, Data, InIndex * sizeof(ElementType));
				GLX_MEMCPY(NewData + InIndex + 1, Data + InIndex, (Length - InIndex) * sizeof(ElementType));
			}
			else
			{
				SizeType Count = InIndex;
				PointerType Dest = NewData;
				PointerType Source = Data;

				while (Count)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (Dest) ElementType(Move(*Source));
					}
					else
					{
						new (Dest) ElementType(*Source);
					}
					++Dest, ++Source;
					--Count;
				}

				++Dest;
				Count = Length - InIndex;
				while (Count)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (Dest) ElementType(Move(*Source));
					}
					else
					{
						new (Dest) ElementType(*Source);
					}
					++Dest, ++Source;
					--Count;
				}
			}

			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					Data[Idx].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			PointerType Dest = Data + Length;

			if constexpr (GlxIsMoveConstructible<ElementType>::Value)
			{
				new (Dest) ElementType(Move(*(Dest - 1)));
			}
			else
			{
				new (Dest) ElementType(*(Dest - 1));
			}

			Dest = Data + InIndex + 1;

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(Dest, Dest - 1, (Length - InIndex - 1) * sizeof(ElementType));
			}
			else
			{
				SizeType Count = Length - InIndex - 1;
				Dest += Count;
				PointerType Source = Dest - 1;

				while (Count)
				{
					if constexpr (GlxIsMoveAssignable<ElementType>::Value)
					{
						*--Dest = Move(*--Source);
					}
					else
					{
						*--Dest = *--Source;
					}
					--Count;
				}
			}

			Dest = Data + InIndex;
			Dest->~ElementType();
			new (Dest) ElementType(Forward<TArgs>(InArgs)...);
		}

		++Length;
		return InIndex;
	}

	template<typename... TArgs>
	ReferenceType EmplaceAtGetRef(SizeType InIndex, TArgs&&... InArgs)
	{
		EmplaceAt(InIndex, Forward<TArgs>(InArgs)...);
		return Data[InIndex];
	}

	SizeType InsertDefaulted(SizeType InIndex)
	{
		return EmplaceAt(InIndex);
	}

	ReferenceType InsertDefaultedGetRef(SizeType InIndex)
	{
		EmplaceAt(InIndex);
		return Data[InIndex];
	}

	SizeType Insert(SizeType InIndex, ConstPointerType InElements, SizeType InCount)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex <= Length && InCount >= 0);

		if (Length + InCount >= Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InCount);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC(Capacity * sizeof(ElementType)));

			if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
			{
				GLX_MEMCPY(NewData, Data, InIndex * sizeof(ElementType));
				PointerType Dest = NewData + InIndex;
				GLX_MEMCPY(Dest, InElements, InCount * sizeof(ElementType));
				GLX_MEMCPY(Dest + InCount, Data + InIndex, (Length - InIndex) * sizeof(ElementType));
			}
			else
			{
				PointerType Dest = NewData;
				PointerType Source = Data;

				SizeType Count = InIndex;
				while (Count)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (Dest) ElementType(Move(*Source));
					}
					else
					{
						new (Dest) ElementType(*Source);
					}
					++Dest, ++Source, --Count;
				}

				Count = InCount;
				while (Count)
				{
					new (Dest) ElementType(*InElements);

					++Dest, ++InElements, --Count;
				}

				Count = Length - InIndex;
				while (Count)
				{
					if constexpr (GlxIsMoveConstructible<ElementType>::Value)
					{
						new (Dest) ElementType(Move(*Source));
					}
					else
					{
						new (Dest) ElementType(*Source);
					}
					++Dest, ++Source, --Count;
				}
			}

			if constexpr (!GlxIsTriviallyDestructible<ElementType>::Value)
			{
				for (SizeType Idx = 0; Idx < Length; ++Idx)
				{
					Data[Idx].~ElementType();
				}
			}

			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			if (InIndex + InCount >= Length)
			{
				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					PointerType Source = Data + InIndex;
					GLX_MEMCPY(Source + InCount, Source, (Length - InIndex) * sizeof(ElementType));
				}
				else
				{
					PointerType Source = Data + InIndex;
					PointerType Dest = Source + InCount;
					SizeType Count = Length - InIndex;

					while (Count)
					{
						if constexpr (GlxIsMoveConstructible<ElementType>::Value)
						{
							new (Dest) ElementType(Move(*Source));
						}
						else
						{
							new (Dest) ElementType(*Source);
						}
						++Dest, ++Source, --Count;
					}
				}

				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					GLX_MEMCPY(Data + InIndex, InElements, (Length - InIndex) * sizeof(ElementType));
				}
				else
				{
					ConstPointerType Source = InElements;
					PointerType Dest = Data + InIndex;
					SizeType Count = Length - InIndex;

					while (Count)
					{
						*Dest = *Source;
						++Dest, ++Source, --Count;
					}
				}

				SizeType Remaining = Length - InIndex;
				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					GLX_MEMCPY(Data + Length, InElements + Remaining, (InCount - Remaining) * sizeof(ElementType));
				}
				else
				{
					SizeType Count = InCount - Remaining;
					ConstPointerType Source = InElements + Remaining;
					PointerType Dest = Data + Length;

					while (Count)
					{
						new (Dest) ElementType(*Source);
						++Dest, ++Source, --Count;
					}
				}
			}
			else
			{
				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					PointerType Dest = Data + Length;
					GLX_MEMCPY(Dest, Dest - InCount, InCount * sizeof(ElementType));
				}
				else
				{
					PointerType Dest = Data + Length;
					PointerType Source = Dest - InCount;
					SizeType Count = InCount;

					while (Count)
					{
						if constexpr (GlxIsMoveConstructible<ElementType>::Value)
						{
							new (Dest) ElementType(Move(*Source));
						}
						else
						{
							new (Dest) ElementType(*Source);
						}
						++Dest, ++Source, --Count;
					}
				}

				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					PointerType Source = Data + InIndex;
					GLX_MEMCPY(Source + InCount, Source, (Length - InIndex - InCount) * sizeof(ElementType));
				}
				else
				{
					SizeType Count = Length - InIndex - InCount;
					PointerType Source = Data + InIndex + Count;
					PointerType Dest = Source + InCount;

					while (Count)
					{
						if constexpr (GlxIsMoveAssignable<ElementType>::Value)
						{
							*--Dest = Move(*--Source);
						}
						else
						{
							*--Dest = *--Source;
						}
						--Count;
					}
				}

				if constexpr (GlxIsMemcpyCompatible<ElementType>::Value)
				{
					GLX_MEMCPY(Data + InIndex, InElements, InCount * sizeof(ElementType));
				}
				else
				{
					PointerType Dest = Data + InIndex;
					SizeType Count = InCount;

					while (Count)
					{
						*Dest = *InElements;
						++Dest, ++InElements, --Count;
					}
				}
			}
		}

		Length += InCount;
		return InIndex;
	}

	SizeType Insert(SizeType InIndex, const GlxDynamicArray& InArray)
	{
		return Insert(InIndex, InArray.Data, InArray.Length);
	}

	SizeType Insert(SizeType InIndex, std::initializer_list<ElementType> InElementList)
	{
		return Insert(InIndex, InElementList.begin(), InElementList.size());
	}

	SizeType Insert(SizeType InIndex, ConstIteratorType InFirst, ConstIteratorType InLast)
	{
		return Insert(InIndex, InFirst, static_cast<SizeType>(InLast - InFirst));
	}

private:
	PointerType Data;
	SizeType Length;
	SizeType Capacity;
};
