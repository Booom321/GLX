#pragma once

#include "GLX/Assert.h"
#include "GLX/Types/Pair.h"
#include "GLX/Utils/HashFunctions.h"
#include "GLX/TypeTraits/EnableIf.h"
#include "GLX/TypeTraits/TypeChooser.h"
#include "GLX/TypeTraits/RemoveReference.h"
#include "GLX/TypeTraits/IsRvalueReference.h"

#include "DynamicArray.h"

template<typename TKey, typename TValue, typename TKeyHasher = GlxHasher<TKey>>
class GlxHashMap
{
public:
	using KeyType = TKey;
	using ValueType = TValue;
	using KeyHasherType = TKeyHasher;
	using HashCodeType = GlxSizeT;

	using SizeType = GlxInt64;
	using PairType = GlxPair<KeyType, ValueType>;

	class GlxElement
	{
	public:
		friend class GlxHashMap<TKey, TValue, TKeyHasher>;

		using HashCodeType = GlxSizeT;

		GLX_FORCE_INLINE GlxElement(HashCodeType InHash, const KeyType& InKey, const ValueType& InVal)
			: HashCode(InHash), Key(InKey), Value(InVal)
		{}

		GLX_FORCE_INLINE GlxElement(HashCodeType InHash, KeyType&& InKey, ValueType&& InVal) noexcept
			: HashCode(InHash), Key(Move(InKey)), Value(Move(InVal))
		{}

		GLX_FORCE_INLINE GlxElement(HashCodeType InHash, const KeyType& InKey, ValueType&& InVal)
			: HashCode(InHash), Key(InKey), Value(Move(InVal))
		{}

		GLX_FORCE_INLINE GlxElement(HashCodeType InHash, KeyType&& InKey, const ValueType& InVal)
			: HashCode(InHash), Key(Move(InKey)), Value(InVal)
		{}

		GLX_FORCE_INLINE GlxElement(HashCodeType InHash, const KeyType& InKey)
			: HashCode(InHash), Key(InKey), Value()
		{}

		GLX_FORCE_INLINE GlxElement(HashCodeType InHash, KeyType&& InKey) noexcept
			: HashCode(InHash), Key(Move(InKey)), Value()
		{}

		GLX_FORCE_INLINE HashCodeType GetHashCode() const
		{
			return HashCode;
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxElement& InOther) const
		{
			return Key == InOther.Key && Value == InOther.Value && HashCode == InOther.HashCode;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxElement& InOther) const
		{
			return Key != InOther.Key || Value != InOther.Value || HashCode != InOther.HashCode;
		}

		KeyType Key;
		ValueType Value;

	private:
		HashCodeType HashCode;
	};

	using ElementType = GlxElement;
	using PointerType = ElementType*;
	using ReferenceType = ElementType&;
	using ConstPointerType = const ElementType*;
	using ConstReferenceType = const ElementType&;

	static GLX_CONSTEXPR GlxFloat MaxLoadFactor = 0.75f;
	static GLX_CONSTEXPR GlxFloat InvalidLoadFactor = -1.0f;
	static GLX_CONSTEXPR SizeType InitialNumList = 8;

	static GLX_FORCE_INLINE HashCodeType GetHashCode(const KeyType& InKey)
	{
		return KeyHasherType::GetHashCode(InKey);
	}

	static GLX_CONSTEXPR GLX_FORCE_INLINE GlxFloat GetMaxLoadFactor()
	{
		return MaxLoadFactor;
	}

	class GlxNode
	{
	public:
		template<typename... TArgs>
		GLX_FORCE_INLINE GlxNode(TArgs&&... InArgs)
			: Element(Forward<TArgs>(InArgs)...)
		{}

		~GlxNode() = default;

		ElementType Element;
		GlxNode* Next = nullptr;
	};

	class GlxElementList
	{
	public:
		using NodeType = GlxNode;

		GlxElementList() = default;
		~GlxElementList() { Clear(); };

		GlxElementList(const GlxElementList& InOther)
			: Count(InOther.Count)
		{
			if (!InOther.Head)
			{
				Head = nullptr;
				Tail = nullptr;
			}
			else
			{
				NodeType* OtherNode = InOther.Head;
				Head = new NodeType(OtherNode->Element);
				OtherNode = OtherNode->Next;

				NodeType* CurrentNode = Head;
				while (OtherNode)
				{
					CurrentNode->Next = new NodeType(OtherNode->Element);
					OtherNode = OtherNode->Next;
					CurrentNode = CurrentNode->Next;
				}

				Tail = CurrentNode;
			}
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

		template<typename... TArgs>
		NodeType* EmplaceBack(TArgs&&... InArgs)
		{
			NodeType* NewNode = new NodeType(Forward<TArgs>(InArgs)...);

			if (Tail)
			{
				Tail->Next = NewNode;
				Tail = NewNode;
			}
			else
			{
				Head = NewNode;
				Tail = NewNode;
			}

			Tail->Next = nullptr;
			++Count;

			return NewNode;
		}

		NodeType* Head;
		NodeType* Tail;
		SizeType Count;
	};

	using ElementListType = GlxElementList;
	using NodeType = GlxNode;

public:
	template<GlxBool InIsConst>
	class GlxIteratorBase
	{
	public:
		friend class GlxHashMap<KeyType, ValueType, KeyHasherType>;

		using HashMapType = typename GlxTypeChooser<InIsConst, const GlxHashMap, GlxHashMap>::Type;
		using ListType    = typename GlxTypeChooser<InIsConst, const ElementListType, ElementListType>::Type;
		using NodeType    = typename GlxTypeChooser<InIsConst, const NodeType, NodeType>::Type;

		GLX_FORCE_INLINE GlxIteratorBase(HashMapType* InMap, ListType* InCurrentList, NodeType* InNode)
			: Map(InMap), CurrentList(InCurrentList), CurrentNode(InNode)
		{
			SetIteratorToValidNode();
		}

		GlxIteratorBase(const GlxIteratorBase&) = default;
		GlxIteratorBase(GlxIteratorBase&&) noexcept = default;
		GlxIteratorBase& operator=(const GlxIteratorBase&) = default;
		GlxIteratorBase& operator=(GlxIteratorBase&&) noexcept = default;
		~GlxIteratorBase() = default;

		GLX_FORCE_INLINE ConstReferenceType operator*() const
		{
			return CurrentNode->Element;
		}

		GLX_FORCE_INLINE ConstPointerType operator->() const
		{
			return &CurrentNode->Element;
		}

		GLX_FORCE_INLINE GlxBool operator==(const GlxIteratorBase& InIt) const
		{
			return Map == InIt.Map && CurrentList == InIt.CurrentList && CurrentNode == InIt.CurrentNode;
		}

		GLX_FORCE_INLINE GlxBool operator!=(const GlxIteratorBase& InIt) const
		{
			return Map != InIt.Map || CurrentList != InIt.CurrentList || CurrentNode != InIt.CurrentNode;
		}

		GlxIteratorBase& operator++()
		{
			if (CurrentNode)
			{
				CurrentNode = CurrentNode->Next;
			}

			if (!CurrentNode)
			{
				++CurrentList;
				SetIteratorToValidNode();
			}

			return *this;
		}

		GLX_FORCE_INLINE GlxIteratorBase operator++(int)
		{
			GlxIteratorBase It(*this);
			this->operator++();
			return It;
		}

		GLX_FORCE_INLINE const NodeType* GetCurrentNode() const
		{
			return CurrentNode;
		}

		GLX_FORCE_INLINE HashCodeType GetHashCode() const
		{
			return CurrentNode->Element.GetHashCode();
		}

		GLX_FORCE_INLINE const KeyType& GetKey() const
		{
			return CurrentNode->Element.Key;
		}

		GLX_FORCE_INLINE const ValueType& GetValue() const
		{
			return CurrentNode->Element.Value;
		}

	protected:
		void SetIteratorToValidNode()
		{
			ListType* LastList = Map->Lists + Map->NumList;

			while (CurrentList < LastList && !CurrentList->Head)
			{
				++CurrentList;
			}

			if (CurrentList >= LastList)
			{
				CurrentNode = nullptr;
			}
			else
			{
				CurrentNode = CurrentList->Head;
			}
		}

		HashMapType* Map;
		ListType* CurrentList;
		NodeType* CurrentNode;
	};

	template<GlxBool InIsConst>
	friend class GlxIteratorBase;

	class GlxIterator : public GlxIteratorBase<false>
	{
	public:
		using Super = GlxIteratorBase<false>;
		GLX_FORCE_INLINE GlxIterator(GlxHashMap* InMap, ElementListType* InCurrentList, NodeType* InNode)
			: Super(InMap, InCurrentList, InNode)
		{}

		GLX_FORCE_INLINE ReferenceType operator*()
		{
			return this->CurrentNode->Element;
		}

		GLX_FORCE_INLINE PointerType operator->()
		{
			return &this->CurrentNode->Element;
		}

		GLX_FORCE_INLINE NodeType* GetCurrentNode()
		{
			return this->CurrentNode;
		}

		GLX_FORCE_INLINE KeyType& GetKey()
		{
			return this->CurrentNode->Element.Key;
		}

		GLX_FORCE_INLINE ValueType& GetValue()
		{
			return this->CurrentNode->Element.Value;
		}
	};

	class GlxConstIterator : public GlxIteratorBase<true>
	{
	public:
		using Super = GlxIteratorBase<true>;
		GLX_FORCE_INLINE GlxConstIterator(const GlxHashMap* InMap, const ElementListType* InCurrentList, const NodeType* InNode)
			: Super(InMap, InCurrentList, InNode)
		{}
	};

	using IteratorType = GlxIterator;
	using ConstIteratorType = GlxConstIterator;

	GlxHashMap()
		:	ElementCount(0),
			NumList(0),
			Lists(nullptr)
	{}

	GlxHashMap(const GlxHashMap& InOther)
		:	ElementCount(InOther.ElementCount),
			NumList(InOther.NumList),
			Lists(NumList > 0 ? static_cast<ElementListType*>(GLX_MALLOC(NumList * sizeof(ElementListType))) : nullptr)
	{
		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			new (Lists + Index) ElementListType(InOther.Lists[Index]);
		}
	}

	GlxHashMap(GlxHashMap&& InOther) noexcept
		:	ElementCount(InOther.ElementCount),
			NumList(InOther.NumList),
			Lists(InOther.Lists)
	{
		InOther.ElementCount = 0;
		InOther.NumList = 0;
		InOther.Lists = nullptr;
	}

	GlxHashMap(std::initializer_list<PairType> InPairs)
		:	ElementCount(0)
	{
		const GlxSizeT PairCount = InPairs.size();

		if ((static_cast<GlxFloat>(PairCount) / static_cast<GlxFloat>(InitialNumList)) > MaxLoadFactor)
		{
			NumList = static_cast<SizeType>(static_cast<GlxFloat>(PairCount) / MaxLoadFactor) + 1;
		}
		else
		{
			NumList = InitialNumList;
		}

		Lists = static_cast<ElementListType*>(GLX_MALLOC(NumList * sizeof(ElementListType)));
		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			new (Lists + Index) ElementListType();
		}

		const PairType* Begin = InPairs.begin();
		const PairType* End = InPairs.end();

		while (Begin != End)
		{
			HashCodeType HashCode = KeyHasherType::GetHashCode(Begin->First);
			NodeType* FoundNode = FindByHash(HashCode);

			if (!FoundNode)
			{
				Lists[HashCode % NumList].EmplaceBack(HashCode, Begin->First, Begin->Second);
				++ElementCount;
			}

			++Begin;
		}
	}

	explicit GlxHashMap(const SizeType InNumList)
		:	ElementCount(0),
			NumList(InNumList > 0 ? InNumList : 0),
			Lists(NumList > 0 ? static_cast<ElementListType*>(GLX_MALLOC(NumList * sizeof(ElementListType))) : nullptr)
	{
		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			new (Lists + Index) ElementListType();
		}
	}

	~GlxHashMap()
	{
		Release();
	}

	void Clear()
	{
		if (!Lists || NumList == 0)
		{
			return;
		}

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			(Lists + Index)->Clear();
		}

		ElementCount = 0;
	}

	void Release()
	{
		if (!Lists || NumList == 0)
		{
			return;
		}

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			(Lists + Index)->~ElementListType();
		}

		GLX_FREE(Lists);

		Lists = nullptr;
		NumList = 0;
		ElementCount = 0;
	}

	GlxHashMap& operator=(const GlxHashMap& InOther)
	{
		if (this != &InOther)
		{
			for (SizeType Index = 0; Index < NumList; ++Index)
			{
				(Lists + Index)->~ElementListType();
			}

			GLX_FREE(Lists);

			ElementCount = InOther.ElementCount;
			NumList = InOther.NumList;
			Lists = static_cast<ElementListType*>(GLX_MALLOC(NumList * sizeof(ElementListType)));
			for (SizeType Index = 0; Index < NumList; ++Index)
			{
				new (Lists + Index) ElementListType(InOther.Lists[Index]);
			}
		}

		return *this;
	}

	GlxHashMap& operator=(GlxHashMap&& InOther) noexcept
	{
		if (this != &InOther)
		{
			for (SizeType Index = 0; Index < NumList; ++Index)
			{
				(Lists + Index)->~ElementListType();
			}

			GLX_FREE(Lists);

			Lists = InOther.Lists;
			NumList = InOther.NumList;
			ElementCount = InOther.ElementCount;

			InOther.Lists = nullptr;
			InOther.NumList = 0;
			InOther.ElementCount = 0;
		}

		return *this;
	}

	GlxHashMap& operator=(std::initializer_list<PairType> InPairs)
	{
		Clear();
		InsertInitListImpl<false>(InPairs.size(), InPairs.begin(), InPairs.end());
		return *this;
	}

	GLX_FORCE_INLINE SizeType GetElementCount() const
	{
		return ElementCount;
	}

	GLX_FORCE_INLINE SizeType GetNumList() const
	{
		return NumList;
	}

	GLX_FORCE_INLINE SizeType GetListCount(SizeType InIndex) const
	{
		return Lists[InIndex].Count;
	}

	GLX_FORCE_INLINE SizeType GetListIndexByKey(const KeyType& InKey) const
	{
		return KeyHasherType::GetHashCode(InKey) % NumList;
	}

	GLX_FORCE_INLINE GlxBool IsEmpty() const
	{
		return ElementCount == 0;
	}

	GLX_FORCE_INLINE IteratorType begin()
	{
		return IteratorType(this, Lists, NumList > 0 ? Lists[0].Head : nullptr);
	}

	GLX_FORCE_INLINE ConstIteratorType begin() const
	{
		return ConstIteratorType(this, Lists, NumList > 0 ? Lists[0].Head : nullptr);
	}

	GLX_FORCE_INLINE IteratorType end()
	{
		return IteratorType(this, Lists + NumList, nullptr);
	}

	GLX_FORCE_INLINE ConstIteratorType end() const
	{
		return ConstIteratorType(this, Lists + NumList, nullptr);
	}

	GLX_FORCE_INLINE GlxFloat GetLoadFactor() const
	{
		return NumList > 0 ? (static_cast<GlxFloat>(ElementCount) / static_cast<GlxFloat>(NumList)) : InvalidLoadFactor;
	}

	NodeType* FindByHash(HashCodeType InHash)
	{
		if (NumList > 0)
		{
			NodeType* Node = Lists[InHash % NumList].Head;

			while (Node)
			{
				if (Node->Element.HashCode == InHash)
				{
					return Node;
				}

				Node = Node->Next;
			}
		}

		return nullptr;
	}

	const NodeType* FindByHash(const HashCodeType InHash) const
	{
		if (NumList > 0)
		{
			const NodeType* Node = Lists[InHash % NumList].Head;

			while (Node)
			{
				if (Node->Element.HashCode == InHash)
				{
					return Node;
				}

				Node = Node->Next;
			}
		}
		return nullptr;
	}

	GLX_FORCE_INLINE NodeType* Find(const KeyType& InKey)
	{
		return FindByHash(KeyHasherType::GetHashCode(InKey));
	}

	GLX_FORCE_INLINE const NodeType* Find(const KeyType& InKey) const
	{
		return FindByHash((const HashCodeType)KeyHasherType::GetHashCode(InKey));
	}

	GLX_FORCE_INLINE GlxBool Contains(const KeyType& InKey) const
	{
		return FindByHash((const HashCodeType)KeyHasherType::GetHashCode(InKey)) != nullptr;
	}

	GLX_FORCE_INLINE GlxBool ContainsByHash(const HashCodeType InHash) const
	{
		return FindByHash(InHash) != nullptr;
	}

	GlxBool operator==(const GlxHashMap& InOther) const
	{
		if (ElementCount != InOther.ElementCount)
		{
			return false;
		}

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				const NodeType* FoundNode = InOther.FindByHash(Node->Element.HashCode);

				if (!FoundNode || !(FoundNode->Element.Value == Node->Element.Value))
				{
					return false;
				}

				Node = Node->Next;
			}
		}

		return true;
	}

	GLX_FORCE_INLINE GlxBool operator!=(const GlxHashMap& InOther) const
	{
		return !operator==(InOther);
	}

private:
	void RehashImpl(SizeType InNewNumList)
	{
		SizeType OldNumList = NumList;
		NumList = InNewNumList;

		ElementListType* NewLists = static_cast<ElementListType*>(GLX_MALLOC(NumList * sizeof(ElementListType)));

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			new (NewLists + Index) ElementListType();
		}

		for (SizeType Index = 0; Index < OldNumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				NewLists[Node->Element.HashCode % NumList].EmplaceBack(Node->Element.HashCode, Move(Node->Element.Key), Move(Node->Element.Value));
				Node = Node->Next;
			}

			Lists[Index].~ElementListType();
		}

		GLX_FREE(Lists);
		Lists = NewLists;
	}

	void RehashForInsertion(SizeType InNewElemCount)
	{
		if (NumList > 0)
		{
			if ((static_cast<GlxFloat>(InNewElemCount) / static_cast<GlxFloat>(NumList)) > MaxLoadFactor)
			{
				RehashImpl(static_cast<SizeType>(static_cast<GlxFloat>(InNewElemCount) / MaxLoadFactor) + 1);
			}
		}
		else
		{
			RehashImpl(static_cast<SizeType>(static_cast<GlxFloat>(InNewElemCount) / MaxLoadFactor) + 1);
		}
	}

	template<typename K, typename... TArgs>
	NodeType* EmplaceByHashImpl(HashCodeType InHash, K InKey, TArgs&&... InArgs)
	{
		NodeType* FoundNode = (NumList > 0) ? FindByHash(InHash) : nullptr;

		if (!FoundNode)
		{
			RehashForInsertion(++ElementCount);

			if constexpr (GlxIsRvalueReference<K>::Value)
			{
				return Lists[InHash % NumList].EmplaceBack(InHash, Move(InKey), ValueType(Forward<TArgs>(InArgs)...));
			}
			else
			{
				return Lists[InHash % NumList].EmplaceBack(InHash, InKey, ValueType(Forward<TArgs>(InArgs)...));
			}
		}

		return nullptr;
	}

	template<typename K, typename... TArgs>
	NodeType* EmplaceOrAssignImpl(HashCodeType InHash, K InKey, TArgs&&... InArgs)
	{
		NodeType* FoundNode = (NumList > 0) ? FindByHash(InHash) : nullptr;

		if (FoundNode)
		{
			FoundNode->Element.Value = ValueType(Forward<TArgs>(InArgs)...);
		}
		else
		{
			RehashForInsertion(++ElementCount);

			if constexpr (GlxIsRvalueReference<K>::Value)
			{
				return Lists[InHash % NumList].EmplaceBack(InHash, Move(InKey), ValueType(Forward<TArgs>(InArgs)...));
			}
			else
			{
				return Lists[InHash % NumList].EmplaceBack(InHash, InKey, ValueType(Forward<TArgs>(InArgs)...));
			}
		}

		return FoundNode;
	}

	template<GlxBool InAssign>
	void InsertInitListImpl(SizeType PairCount, const PairType* Begin, const PairType* End)
	{
		RehashForInsertion(ElementCount + PairCount);

		while (Begin != End)
		{
			HashCodeType HashCode = KeyHasherType::GetHashCode(Begin->First);
			NodeType* FoundNode = FindByHash(HashCode);

			if constexpr (InAssign)
			{
				if (FoundNode)
				{
					FoundNode->Element.Value = Begin->Second;
					++Begin;
					continue;
				}
			}

			if (!FoundNode)
			{
				++ElementCount;
				Lists[HashCode % NumList].EmplaceBack(HashCode, Begin->First, Begin->Second);
			}

			++Begin;
		}
	}

public:
	void Rehash(SizeType InNewNumList)
	{
		SizeType Num = static_cast<SizeType>(static_cast<GlxFloat>(ElementCount) / MaxLoadFactor) + 1;
		InNewNumList = GLX_MAX(InNewNumList, Num);

		if (InNewNumList > NumList)
		{
			RehashImpl(InNewNumList);
		}
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE NodeType* EmplaceByHash(HashCodeType InHash, const KeyType& InKey, TArgs&&... InArgs)
	{
		return EmplaceByHashImpl<const KeyType&>(InHash, InKey, Forward<TArgs>(InArgs)...);
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE NodeType* EmplaceByHash(HashCodeType InHash, KeyType&& InKey, TArgs&&... InArgs)
	{
		return EmplaceByHashImpl<KeyType&&>(InHash, Move(InKey), Forward<TArgs>(InArgs)...);
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE NodeType* Emplace(const KeyType& InKey, TArgs&&... InArgs)
	{
		return EmplaceByHashImpl<const KeyType&>(KeyHasherType::GetHashCode(InKey), InKey, Forward<TArgs>(InArgs)...);
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE NodeType* Emplace(KeyType&& InKey, TArgs&&... InArgs)
	{
		return EmplaceByHashImpl<KeyType&&>(KeyHasherType::GetHashCode(InKey), Move(InKey), Forward<TArgs>(InArgs)...);
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE NodeType* EmplaceOrAssign(const KeyType& InKey, TArgs&&... InArgs)
	{
		return EmplaceOrAssignImpl<const KeyType&>(KeyHasherType::GetHashCode(InKey), InKey, Forward<TArgs>(InArgs)...);
	}

	template<typename... TArgs>
	GLX_FORCE_INLINE NodeType* EmplaceOrAssign(KeyType&& InKey, TArgs&&... InArgs)
	{
		return EmplaceOrAssignImpl<KeyType&&>(KeyHasherType::GetHashCode(InKey), Move(InKey), Forward<TArgs>(InArgs)...);
	}

	GLX_FORCE_INLINE NodeType* Insert(const PairType& InKV)
	{
		return EmplaceByHashImpl<const KeyType&>(KeyHasherType::GetHashCode(InKV.First), InKV.First, InKV.Second);
	}

	GLX_FORCE_INLINE NodeType* Insert(PairType&& InKV)
	{
		return EmplaceByHashImpl<KeyType&&>(KeyHasherType::GetHashCode(InKV.First), Move(InKV.First), Move(InKV.Second));
	}

	GLX_FORCE_INLINE NodeType* InsertOrAssign(const PairType& InKV)
	{
		return EmplaceOrAssignImpl<const KeyType&>(KeyHasherType::GetHashCode(InKV.First), InKV.First, InKV.Second);
	}

	GLX_FORCE_INLINE NodeType* InsertOrAssign(PairType&& InKV)
	{
		return EmplaceOrAssignImpl<KeyType&&>(KeyHasherType::GetHashCode(InKV.First), Move(InKV.First), Move(InKV.Second));
	}

	GLX_FORCE_INLINE void Insert(std::initializer_list<PairType> InPairs)
	{
		InsertInitListImpl<false>((SizeType)InPairs.size(), InPairs.begin(), InPairs.end());
	}

	GLX_FORCE_INLINE void InsertOrAssign(std::initializer_list<PairType> InPairs)
	{
		InsertInitListImpl<true>((SizeType)InPairs.size(), InPairs.begin(), InPairs.end());
	}

private:
	template<typename K>
	ValueType& GetValueByKey(K InKey)
	{
		HashCodeType HashCode = KeyHasherType::GetHashCode(InKey);
		NodeType* Node = (NumList > 0) ? FindByHash(HashCode) : nullptr;

		if (!Node)
		{
			RehashForInsertion(++ElementCount);

			if constexpr (GlxIsRvalueReference<K>::Value)
			{
				Node = Lists[HashCode % NumList].EmplaceBack(HashCode, Move(InKey));
			}
			else
			{
				Node = Lists[HashCode % NumList].EmplaceBack(HashCode, InKey);
			}
		}

		return Node->Element.Value;
	}

public:
	GLX_NODISCARD GLX_FORCE_INLINE ValueType& operator[](const KeyType& InKey)
	{
		return GetValueByKey<const KeyType&>(InKey);
	}

	GLX_NODISCARD GLX_FORCE_INLINE ValueType& operator[](KeyType&& InKey)
	{
		return GetValueByKey<KeyType&&>(Move(InKey));
	}

	GLX_NODISCARD ValueType& At(const KeyType& InKey)
	{
		NodeType* FoundNode = FindByHash(KeyHasherType::GetHashCode(InKey));
		GLX_ASSERT(FoundNode);
		return FoundNode->Element.Value;
	}

	GLX_NODISCARD const ValueType& At(const KeyType& InKey) const
	{
		const NodeType* FoundNode = FindByHash(KeyHasherType::GetHashCode(InKey));
		GLX_ASSERT(FoundNode);
		return FoundNode->Element.Value;
	}

	GLX_FORCE_INLINE NodeType* Remove(const KeyType& InKey)
	{
		return RemoveByHash(KeyHasherType::GetHashCode(InKey));
	}

	GLX_FORCE_INLINE NodeType* RemoveAt(IteratorType InIt)
	{
		return RemoveByHash(InIt.CurrentNode->Element.HashCode);
	}

	NodeType* RemoveByHash(const HashCodeType InHash)
	{
		ElementListType& List = Lists[InHash % NumList];

		if (!List.Count || !List.Head)
		{
			return nullptr;
		}

		NodeType* Node = List.Head;
		NodeType* Prev = List.Head;

		while (Node)
		{
			if (Node->Element.HashCode == InHash)
			{
				break;
			}

			Prev = Node;
			Node = Node->Next;
		}

		NodeType* Tmp = nullptr;
		NodeType* Ret = nullptr;
		if (Node == List.Head)
		{
			Tmp = List.Head;
			List.Head = List.Head->Next;
			Ret = List.Head;
		}
		else if (Node == List.Tail)
		{
			Tmp = List.Tail;
			Ret = Prev;
			List.Tail = Prev;
			List.Tail->Next = nullptr;
		}
		else
		{
			Tmp = Node;
			Ret = Node->Next;
			Prev->Next = Node->Next;
		}

		delete Tmp;
		--ElementCount;

		return Ret;
	}

	SizeType GetKeys(GlxDynamicArray<KeyType>& InArr) const
	{
		InArr.Reserve(ElementCount);

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				InArr.EmplaceBack(Node->Element.Key);
				Node = Node->Next;
			}
		}

		return InArr.GetElementCount();
	}

	SizeType GetValues(GlxDynamicArray<ValueType>& InArr) const
	{
		InArr.Reserve(ElementCount);

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				InArr.EmplaceBack(Node->Element.Value);
				Node = Node->Next;
			}
		}

		return InArr.GetElementCount();
	}

	SizeType GetElements(GlxDynamicArray<ElementType>& InArr) const
	{
		InArr.Reserve(ElementCount);

		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				InArr.EmplaceBack(Node->Element.HashCode, Node->Element.Key, Node->Element.Value);
				Node = Node->Next;
			}
		}

		return InArr.GetElementCount();
	}

	template<typename TPredicate>
	void FilterKeys(TPredicate InPred, GlxDynamicArray<KeyType>& InArr) const
	{
		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				if (InPred(Node->Element.Key))
				{
					InArr.EmplaceBack(Node->Element.Key);
				}
				Node = Node->Next;
			}
		}
	}

	template<typename TPredicate>
	void FilterValues(TPredicate InPred, GlxDynamicArray<ValueType>& InArr) const
	{
		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				if (InPred(Node->Element.Value))
				{
					InArr.EmplaceBack(Node->Element.Value);
				}
				Node = Node->Next;
			}
		}
	}

	template<typename TPredicate>
	void FilterElements(TPredicate InPred, GlxDynamicArray<ElementType>& InArr) const
	{
		for (SizeType Index = 0; Index < NumList; ++Index)
		{
			NodeType* Node = Lists[Index].Head;

			while (Node)
			{
				if (InPred(Node->Element))
				{
					InArr.EmplaceBack(Node->Element.HashCode, Node->Element.Key, Node->Element.Value);
				}
				Node = Node->Next;
			}
		}
	}

private:
	SizeType ElementCount;
	SizeType NumList;
	ElementListType* Lists;
};
