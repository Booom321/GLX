#pragma once

#include "GLX/Assert.h"
#include "GLX/TypeTraits/EnableIf.h"
#include "GLX/TypeTraits/TypeChooser.h"
#include "GLX/TypeTraits/RemoveReference.h"
#include "GLX/TypeTraits/TypeRelationships.h"

#include <initializer_list>

template<typename T>
class GlxList
{
public:
	class GlxNode
	{
	public:
		template<typename... TArgs>
		GLX_FORCE_INLINE GlxNode(TArgs&&... InArgs)
			: Value(Forward<TArgs>(InArgs)...)
		{}

		~GlxNode() = default;

		T Value;

		GlxNode* Next = nullptr;
		GlxNode* Previous = nullptr;
	};

	class GlxIterator
	{
	public:
		using NodeType = GlxNode;

		GLX_FORCE_INLINE GlxIterator(NodeType* InNode)
			: Current(InNode)
		{}

		GlxIterator(const GlxIterator&) = default;
		GlxIterator(GlxIterator&&) noexcept = default;
		GlxIterator& operator=(const GlxIterator&) = default;
		GlxIterator& operator=(GlxIterator&&) noexcept = default;
		~GlxIterator() = default;

		GLX_FORCE_INLINE explicit operator bool() const noexcept { return Current != nullptr; }
		GLX_FORCE_INLINE T& operator*() const { return Current->Value; }
		GLX_FORCE_INLINE T* operator->() const { return &Current->Value; }
		GLX_FORCE_INLINE GlxNode* GetNode() const { return Current; }

		GLX_FORCE_INLINE GlxIterator& operator++()
		{
			GLX_ASSERT(Current);
			Current = Current->Next;
			return *this;
		}

		GLX_FORCE_INLINE GlxIterator operator++(int)
		{
			GLX_ASSERT(Current);
			NodeType* Tmp = Current;
			Current = Current->Next;
			return GlxIterator(Tmp);
		}

		GLX_FORCE_INLINE GlxIterator& operator--()
		{
			GLX_ASSERT(Current);
			Current = Current->Previous;
			return *this;
		}

		GLX_FORCE_INLINE GlxIterator operator--(int)
		{
			GLX_ASSERT(Current);
			NodeType* Tmp = Current;
			Current = Current->Previous;
			return GlxIterator(Tmp);
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxIterator& InRhs) const
		{
			return Current == InRhs.Current;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxIterator& InRhs) const
		{
			return Current != InRhs.Current;
		}

	private:
		NodeType* Current;
	};

	class GlxConstIterator
	{
	public:
		using NodeType = const GlxNode;

		GLX_FORCE_INLINE GlxConstIterator(NodeType* InNode)
			: Current(InNode)
		{}

		GlxConstIterator(const GlxConstIterator&) = default;
		GlxConstIterator(GlxConstIterator&&) noexcept = default;
		GlxConstIterator& operator=(const GlxConstIterator&) = default;
		GlxConstIterator& operator=(GlxConstIterator&&) noexcept = default;
		~GlxConstIterator() = default;

		GLX_FORCE_INLINE explicit operator bool() const noexcept { return Current != nullptr; }
		GLX_FORCE_INLINE const T& operator*() const { return Current->Value; }
		GLX_FORCE_INLINE const T* operator->() const { return &Current->Value; }
		GLX_FORCE_INLINE const GlxNode* GetNode() const { return Current; }

		GLX_FORCE_INLINE GlxConstIterator& operator++()
		{
			GLX_ASSERT(Current);
			Current = Current->Next;
			return *this;
		}

		GLX_FORCE_INLINE GlxConstIterator operator++(int)
		{
			GLX_ASSERT(Current);
			NodeType* Tmp = Current;
			Current = Current->Next;
			return GlxConstIterator(Tmp);
		}

		GLX_FORCE_INLINE GlxConstIterator& operator--()
		{
			GLX_ASSERT(Current);
			Current = Current->Previous;
			return *this;
		}

		GLX_FORCE_INLINE GlxConstIterator operator--(int)
		{
			GLX_ASSERT(Current);
			NodeType* Tmp = Current;
			Current = Current->Previous;
			return GlxConstIterator(Tmp);
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxConstIterator& InRhs) const
		{
			return Current == InRhs.Current;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxConstIterator& InRhs) const
		{
			return Current != InRhs.Current;
		}

	private:
		NodeType* Current;
	};

	using SizeType = GlxInt64;

	using ElementType = T;
	using ReferenceType = T&;
	using ConstReferenceType = const T&;
	using PointerType = T*;
	using ConstPointerType = const T*;

	using NodeType = GlxNode;
	using IteratorType = GlxIterator;
	using ConstIteratorType = GlxConstIterator;

private:
	template<typename TIter, GlxBool InCalculateCount>
	void ConstructRange(TIter InFirst, TIter InLast)
	{
		if (!InFirst)
		{
			Head = nullptr;
			Tail = nullptr;
		}
		else
		{
			if constexpr (GlxIsSame<TIter, const GlxNode*>::Value)
			{
				Head = new NodeType(InFirst->Value);
				InFirst = InFirst->Next;
			}
			else
			{
				Head = new NodeType(*InFirst);
				++InFirst;
			}

			if constexpr (InCalculateCount)
			{
				Count = 1;
			}

			NodeType* CurrentNode = Head;
			while (InFirst != InLast)
			{
				if constexpr (GlxIsSame<TIter, const GlxNode*>::Value)
				{
					CurrentNode->Next = new NodeType(InFirst->Value);
					InFirst = InFirst->Next;
				}
				else
				{
					CurrentNode->Next = new NodeType(*InFirst);
					++InFirst;
				}

				if constexpr (InCalculateCount)
				{
					++Count;
				}

				CurrentNode->Next->Previous = CurrentNode;
				CurrentNode = CurrentNode->Next;
			}

			Tail = CurrentNode;
		}
	}

public:
	GLX_FORCE_INLINE GlxList()
		: Head(nullptr), Tail(nullptr), Count(0)
	{}

	GLX_FORCE_INLINE GlxList(GlxList&& InOther) noexcept
		: Head(InOther.Head), Tail(InOther.Tail), Count(InOther.Count)
	{
		InOther.Head = nullptr;
		InOther.Tail = nullptr;
		InOther.Count = 0;
	}

	GLX_FORCE_INLINE GlxList(const GlxList& InOther)
		: Count(InOther.Count)
	{
		ConstructRange<const NodeType*, false>(InOther.Head, nullptr);
	}

	GLX_FORCE_INLINE GlxList(std::initializer_list<ElementType> InList)
		: Count(static_cast<SizeType>(InList.size()))
	{
		ConstructRange<ConstPointerType, false>(InList.begin(), InList.end());
	}

	template<typename TIter>
	GLX_FORCE_INLINE GlxList(TIter InFirst, TIter InLast)
	{
		ConstructRange<ConstPointerType, true>(InFirst, InLast);
	}

	~GlxList()
	{
		Clear();
	}

	void Clear()
	{
		NodeType* Node;

		while (Head)
		{
			Node = Head->Next;
			delete Head;
			Head = Node;
		}

		Tail = nullptr;
		Count = 0;
	}

	void Release()
	{
		Clear();
	}

	GLX_FORCE_INLINE SizeType GetElementCount() const
	{
		return Count;
	}

	GLX_FORCE_INLINE GlxBool IsEmpty() const
	{
		return Count == 0;
	}

	GLX_FORCE_INLINE ReferenceType GetFirstElement()
	{
		GLX_ASSERT(Head);
		return Head->Value;
	}

	GLX_FORCE_INLINE ConstReferenceType GetFirstElement() const
	{
		GLX_ASSERT(Head);
		return Head->Value;
	}

	GLX_FORCE_INLINE ReferenceType GetLastElement()
	{
		GLX_ASSERT(Tail);
		return Tail->Value;
	}

	GLX_FORCE_INLINE ConstReferenceType GetLastElement() const
	{
		GLX_ASSERT(Tail);
		return Tail->Value;
	}

	GLX_FORCE_INLINE NodeType* GetHead()
	{
		return Head;
	}

	GLX_FORCE_INLINE const NodeType* GetHead() const
	{
		return Head;
	}

	GLX_FORCE_INLINE NodeType* GetTail()
	{
		return Tail;
	}

	GLX_FORCE_INLINE const NodeType* GetTail() const
	{
		return Tail;
	}

	ReferenceType operator[](SizeType InIndex)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex < Count);

		NodeType* Current = Head;
		while (InIndex > 0)
		{
			Current = Current->Next;
			--InIndex;
		}

		return Current->Value;
	}

	GLX_FORCE_INLINE ConstReferenceType operator[](SizeType InIndex) const
	{
		return const_cast<GlxList*>(this)->operator[](InIndex);
	}

	GLX_FORCE_INLINE IteratorType begin()
	{
		return IteratorType(Head);
	}

	GLX_FORCE_INLINE ConstIteratorType begin() const
	{
		return ConstIteratorType(Head);
	}

	GLX_FORCE_INLINE IteratorType end()
	{
		return IteratorType(nullptr);
	}

	GLX_FORCE_INLINE ConstIteratorType end() const
	{
		return ConstIteratorType(nullptr);
	}

private:
	template<typename TIter>
	void AssignImpl(SizeType InCount, TIter InFirst, TIter InLast)
	{
		SizeType Num = GLX_MIN(InCount, Count);

		NodeType* CurrentNode = Head;
		NodeType* TmpTail = CurrentNode;
		while (Num > 0)
		{
			if constexpr (GlxIsSame<TIter, const GlxNode*>::Value)
			{
				CurrentNode->Value = InFirst->Value;
			}
			else
			{
				CurrentNode->Value = *InFirst;
			}
			TmpTail = CurrentNode;
			CurrentNode = CurrentNode->Next;
			++InFirst;
			--Num;
		}

		if (InCount >= Count)
		{
			if (InFirst != InLast)
			{
				if constexpr (GlxIsSame<TIter, const GlxNode*>::Value)
				{
					CurrentNode = new NodeType(InFirst->Value);
					InFirst = InFirst->Next;
				}
				else
				{
					CurrentNode = new NodeType(*InFirst);
					++InFirst;
				}

				if (!Head)
				{
					Head = CurrentNode;
				}

				if (TmpTail)
				{
					TmpTail->Next = CurrentNode;
					TmpTail->Next->Previous = TmpTail;
				}

				while (InFirst != InLast)
				{
					if constexpr (GlxIsSame<TIter, const GlxNode*>::Value)
					{
						CurrentNode->Next = new NodeType(InFirst->Value);
						InFirst = InFirst->Next;
					}
					else
					{
						CurrentNode->Next = new NodeType(*InFirst);
						++InFirst;
					}
					CurrentNode->Next->Previous = CurrentNode;
					CurrentNode = CurrentNode->Next;
				}
			}

			Tail = CurrentNode;
			if (Tail)
			{
				Tail->Next = nullptr;
			}
		}
		else
		{
			if (CurrentNode == Head)
			{
				Head = nullptr;
				Tail = nullptr;
			}
			else
			{
				Tail = CurrentNode->Previous;
				Tail->Next = nullptr;
			}

			NodeType* Node;
			while (CurrentNode)
			{
				Node = CurrentNode->Next;
				delete CurrentNode;
				CurrentNode = Node;
			}
		}

		Count = InCount;
	}

public:
	GlxList& operator=(GlxList&& InOther) noexcept
	{
		if (this != & InOther)
		{
			if (Head)
			{
				NodeType* Node;
				while (Head)
				{
					Node = Head->Next;
					delete Head;
					Head = Node;
				}
			}

			Head = InOther.Head;
			Tail = InOther.Tail;
			Count = InOther.Count;
			InOther.Head = nullptr;
			InOther.Tail = nullptr;
			InOther.Count = 0;
		}

		return *this;
	}

	GLX_FORCE_INLINE GlxList& operator=(const GlxList& InOther)
	{
		if (this != &InOther)
		{
			AssignImpl<const GlxNode*>(InOther.Count, InOther.Head, nullptr);
		}

		return *this;
	}

	GLX_FORCE_INLINE GlxList& operator=(std::initializer_list<ElementType> InList)
	{
		AssignImpl<ConstPointerType>(InList.size(), InList.begin(), InList.end());
		return *this;
	}

	GlxBool operator==(const GlxList& InOther) const
	{
		if (Count != InOther.Count)
		{
			return false;
		}

		const NodeType* CurrentNode = Head;
		const NodeType* OtherNode = InOther.Head;

		while (CurrentNode)
		{
			if (!(CurrentNode->Value == OtherNode->Value))
			{
				return false;
			}
			CurrentNode = CurrentNode->Next;
			OtherNode = OtherNode->Next;
		}

		return true;
	}

	GLX_FORCE_INLINE GlxBool operator!=(const GlxList& InOther) const
	{
		return !operator==(InOther);
	}

	template<typename... TArgs>
	NodeType* EmplaceFront(TArgs&&... InArgs)
	{
		NodeType* NewNode = new NodeType(Forward<TArgs>(InArgs)...);
		NewNode->Next = Head;

		if (Head)
		{
			NewNode->Next->Previous = NewNode;
		}
		else
		{
			Tail = NewNode;
		}

		Head = NewNode;
		++Count;
		return Head;
	}

	template<typename... TArgs>
	NodeType* EmplaceBack(TArgs&&... InArgs)
	{
		NodeType* NewNode = new NodeType(Forward<TArgs>(InArgs)...);
		NewNode->Previous = Tail;

		if (Tail)
		{
			NewNode->Previous->Next = NewNode;
		}
		else
		{
			Head = NewNode;
		}

		Tail = NewNode;
		++Count;
		return Tail;
	}

	template<typename... TArgs>
	NodeType* EmplaceAt(NodeType* InNodePos, TArgs&&... InArgs)
	{
		if (!InNodePos)
		{
			return EmplaceBack(Forward<TArgs>(InArgs)...);
		}

		if (InNodePos == Head)
		{
			return EmplaceFront(Forward<TArgs>(InArgs)...);
		}

		NodeType* NewNode = new NodeType(Forward<TArgs>(InArgs)...);

		NewNode->Previous = InNodePos->Previous;
		NewNode->Next = InNodePos;

		InNodePos->Previous->Next = NewNode;
		InNodePos->Previous = NewNode;

		++Count;
		return NewNode;
	}

	template<typename TIter>
	NodeType* Insert(NodeType* InNodePos, TIter InFirst, TIter InLast)
	{
		NodeType* NewHead = new NodeType(*InFirst);
		NodeType* CurrentNode = NewHead;
		++InFirst;
		++Count;
		while (InFirst != InLast)
		{
			CurrentNode->Next = new NodeType(*InFirst);
			CurrentNode->Next->Previous = CurrentNode;
			CurrentNode = CurrentNode->Next;
			++InFirst;
			++Count;
		}
		NodeType* NewTail = CurrentNode;

		if (!InNodePos || InNodePos == Tail)
		{
			NewHead->Previous = Tail;

			if (Tail)
			{
				NewHead->Previous->Next = NewHead;
			}
			else
			{
				Head = NewHead;
			}

			Tail = NewTail;
			return NewHead;
		}
		else if (InNodePos == Head)
		{
			NewTail->Next = Head;

			if (Head)
			{
				NewTail->Next->Previous = NewTail;
			}
			else
			{
				Tail = NewTail;
			}

			Head = NewHead;
			return NewHead;
		}
		else
		{
			NewHead->Previous = InNodePos->Previous;
			NewHead->Previous->Next = NewHead;
			NewTail->Next = InNodePos;
			NewTail->Next->Previous = NewTail;
		}

		return NewHead;
	}

	NodeType* RemoveAtHead()
	{
		if (Count == 0)
		{
			return nullptr;
		}

		NodeType* OldHead = Head->Next;
		delete Head;
		Head = OldHead;

		if (Head)
		{
			Head->Previous = nullptr;
		}
		else
		{
			Tail = nullptr;
		}
		--Count;
		return Head;
	}

	NodeType* RemoveAtTail()
	{
		if (Count == 0)
		{
			return nullptr;
		}

		NodeType* OldTail = Tail->Previous;
		delete Tail;
		Tail = OldTail;

		if (Tail)
		{
			Tail->Next = nullptr;
		}
		else
		{
			Head = nullptr;
		}
		--Count;
		return Tail;
	}

	NodeType* RemoveAt(NodeType* InNodePos)
	{
		if (Count == 0 || !InNodePos)
		{
			return nullptr;
		}

		NodeType* Ret = nullptr;
		if (InNodePos == Head)
		{
			Head = Head->Next;
			Ret = Head;
			if (Head)
			{
				Head->Previous = nullptr;
			}
			else
			{
				Tail = nullptr;
			}
		}
		else if (InNodePos == Tail)
		{
			Tail = Tail->Previous;
			Ret = Tail;
			if (Tail)
			{
				Tail->Next = nullptr;
			}
			else
			{
				Head = nullptr;
			}
		}
		else
		{
			Ret = InNodePos->Next;
			InNodePos->Previous->Next = InNodePos->Next;
			InNodePos->Next->Previous = InNodePos->Previous;
		}

		delete InNodePos;
		--Count;

		return Ret;
	}

	ElementType PopFront()
	{
		GLX_ASSERT(Count != 0);
		ElementType Result{ Head->Value };
		RemoveAtHead();
		return Result;
	}

	ElementType PopBack()
	{
		GLX_ASSERT(Count != 0);
		ElementType Result{ Tail->Value };
		RemoveAtTail();
		return Result;
	}

	template<typename TFunc>
	GlxList ForEach(TFunc InFunc) const
	{
		GlxList List(*this);
		List.ForEachInternal(InFunc);
		return List;
	}

	template<typename TFunc>
	void ForEachInternal(TFunc InFunc)
	{
		NodeType* Current = Head;

		while (Current)
		{
			InFunc(Current->Value);
			Current = Current->Next;
		}
	}

	template<typename TPredicate>
	void Filter(TPredicate InPred, GlxList& InList)
	{
		NodeType* Current = Head;

		while (Current)
		{
			if (InPred(Current->Value))
			{
				InList.EmplaceBack(Current->Value);
			}
			Current = Current->Next;
		}
	}

	NodeType* Find(ConstReferenceType InItem)
	{
		NodeType* Node = Head;
		while (Node)
		{
			if (Node->Value == InItem)
			{
				return Node;
			}

			Node = Node->Next;
		}
		return nullptr;
	}

	NodeType* FindLast(ConstReferenceType InItem)
	{
		NodeType* Node = Tail;
		while (Node)
		{
			if (Node->Value == InItem)
			{
				return Node;
			}

			Node = Node->Previous;
		}
		return nullptr;
	}

	template<typename TPredicate>
	NodeType* FindIf(TPredicate InPred)
	{
		NodeType* Node = Head;
		while (Node)
		{
			if (InPred(Node->Value))
			{
				return Node;
			}

			Node = Node->Next;
		}
		return nullptr;
	}

	template<typename TPredicate>
	NodeType* FindLastIf(TPredicate InPred)
	{
		NodeType* Node = Tail;
		while (Node)
		{
			if (InPred(Node->Value))
			{
				return Node;
			}

			Node = Node->Previous;
		}
		return nullptr;
	}

	GLX_FORCE_INLINE const NodeType* Find(ConstReferenceType InItem) const
	{
		return const_cast<GlxList*>(this)->Find(InItem);
	}

	GLX_FORCE_INLINE const NodeType* FindLast(ConstReferenceType InItem) const
	{
		return const_cast<GlxList*>(this)->FindLast(InItem);
	}

	template<typename TPredicate>
	GLX_FORCE_INLINE const NodeType* FindIf(TPredicate InPred) const
	{
		return const_cast<GlxList*>(this)->FindIf(InPred);
	}

	template<typename TPredicate>
	GLX_FORCE_INLINE const NodeType* FindLastIf(TPredicate InPred) const
	{
		return const_cast<GlxList*>(this)->FindLastIf(InPred);
	}

	GLX_FORCE_INLINE GlxBool Contains(ConstReferenceType InItem) const
	{
		return const_cast<GlxList*>(this)->Find(InItem) != nullptr;
	}

	template<typename TPredicate>
	GLX_FORCE_INLINE GlxBool ContainsIf(TPredicate InPred) const
	{
		return const_cast<GlxList*>(this)->FindIf(InPred) != nullptr;
	}

private:
	NodeType* Head;
	NodeType* Tail;
	SizeType Count;
};
