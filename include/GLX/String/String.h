#pragma once

#include "CStringUtils.h"
#include "GLX/Containers/DynamicArray.h"
#include "GLX/TypeTraits/IsStandardLayout.h"

#include "GLX/ThirdParty/fmt/core.h"
#include "GLX/ThirdParty/fmt/xchar.h"

template<typename TChar>
class GlxBasicString
{
public:
	static_assert(!GlxIsArray<TChar>::Value && GlxIsTrivial<TChar>::Value && GlxIsStandardLayout<TChar>::Value);

	using SizeType = GlxInt64;

	using ElementType = TChar;
	using ReferenceType = TChar&;
	using PointerType = TChar*;
	using ConstReferenceType = const TChar&;
	using ConstPointerType = const TChar*;

	using IteratorType = TChar*;
	using ConstIteratorType = const TChar*;

	using CharUtils = GlxCharUtils<TChar>;
	using CStringUtils = GlxCStringUtils<TChar>;

	static GLX_CONSTEXPR SizeType InvalidIndex = GLX_INVALID_INDEX;
	static GLX_CONSTEXPR GlxFloat GrowthFactor = 1.5f;

	static GLX_CONSTEXPR ElementType NullChar = static_cast<ElementType>(0);

	static GLX_CONSTEXPR GlxBool IsChar = GlxIsSame<TChar, GlxChar>::Value;
	static GLX_CONSTEXPR GlxBool IsWChar = GlxIsSame<TChar, GlxWChar>::Value;

	static_assert(IsChar || IsWChar, "GlxBasicString<TChar> is not implemented for this char type.");

private:
	void Initialize(SizeType InLength, ConstPointerType InStr)
	{
		Data = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));

		if (InLength > 0 && InStr)
		{
			GLX_MEMCPY(Data, InStr, InLength * sizeof(ElementType));
		}

		Data[InLength] = NullChar;
	}

	void Initialize(SizeType InCount, ElementType InCh)
	{
		Data = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));

		if (InCount > 0)
		{
			if constexpr (IsChar)
			{
				GLX_MEMSET(Data, InCh, InCount);
			}
			else if constexpr (IsWChar)
			{
				GLX_WMEMSET(Data, InCh, InCount);
			}
		}

		Data[InCount] = NullChar;
	}

	GLX_FORCE_INLINE GlxBasicString(SizeType InLength)
		: Data(static_cast<PointerType>(GLX_MALLOC((InLength + 1) * sizeof(ElementType)))), Length(InLength), Capacity(InLength)
	{
		Data[InLength] = NullChar;
	}

public:
	GlxBasicString(GlxNullPtr) = delete;

	GlxBasicString()
		: Data(static_cast<PointerType>(GLX_MALLOC(sizeof(ElementType)))), Length(0), Capacity(0)
	{
		*Data = NullChar;
	}

	GlxBasicString(const GlxBasicString& InStr)
		: Length(InStr.Length), Capacity(InStr.Length)
	{
		Initialize(Length, InStr.Data);
	}

	GlxBasicString(const GlxBasicString& InStr, SizeType InStartPos, SizeType InLength)
	{
		GLX_ASSERT(InStartPos >= 0 && InLength >= 0 && InStartPos + InLength <= InStr.Length);
		Length = InLength;
		Capacity = InLength;
		Initialize(Length, InStr.Data + InStartPos);
	}

	GlxBasicString(GlxBasicString&& InStr) noexcept
		: Data(InStr.Data), Length(InStr.Length), Capacity(InStr.Capacity)
	{
		InStr.Data = static_cast<PointerType>(GLX_MALLOC(sizeof(ElementType)));
		InStr.Length = 0;
		InStr.Capacity = 0;
		*InStr.Data = NullChar;
	}

	GlxBasicString(ConstPointerType InStr)
		: Length(static_cast<SizeType>(CStringUtils::Strlen(InStr))), Capacity(Length)
	{
		Initialize(Length, InStr);
	}

	GlxBasicString(ConstPointerType InStr, SizeType InLength)
	{
		GLX_ASSERT(InLength >= 0);
		Length = InLength;
		Capacity = InLength;
		Initialize(InLength, InStr);
	}

	GlxBasicString(ElementType InCh, SizeType InCount)
	{
		GLX_ASSERT(InCount >= 0);
		Length = InCount;
		Capacity = InCount;
		Initialize(InCount, InCh);
	}

	~GlxBasicString()
	{
		Release();
	}

	void Release()
	{
		if (Data)
		{
			GLX_FREE(Data);
			Data = nullptr;
			Length = 0;
			Capacity = 0;
		}
	}

	void Assign(ConstPointerType InStr, SizeType InLength)
	{
		GLX_ASSERT(InLength >= 0);

		if (InLength > Capacity)
		{
			Capacity = InLength;
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, InStr, InLength * sizeof(ElementType));

			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			GLX_MEMCPY(Data, InStr, InLength * sizeof(ElementType));
		}

		Data[InLength] = NullChar;
		Length = InLength;
	}

	GlxBasicString& operator=(GlxNullPtr) = delete;

	GlxBasicString& operator=(const GlxBasicString& InStr)
	{
		if (this != &InStr)
		{
			Assign(InStr.Data, InStr.Length);
		}
		return *this;
	}

	GlxBasicString& operator=(GlxBasicString&& InStr) noexcept
	{
		if (this != &InStr)
		{
			PointerType TmpData = Data;
			Data = InStr.Data;
			InStr.Data = TmpData;

			SizeType TmpCapacity = Capacity;
			Capacity = InStr.Capacity;
			InStr.Capacity = TmpCapacity;

			Length = InStr.Length;

			InStr.Length = 0;
			*InStr.Data = NullChar;
		}
		return *this;
	}

	GlxBasicString& operator=(ConstPointerType InStr)
	{
		if (Data != InStr)
		{
			Assign(InStr, static_cast<SizeType>(CStringUtils::Strlen(InStr)));
		}
		return *this;
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

	GLX_FORCE_INLINE ReferenceType CharAt(SizeType InIndex)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex < Length);
		return Data[InIndex];
	}

	GLX_FORCE_INLINE ConstReferenceType CharAt(SizeType InIndex) const
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
		return *Data;
	}

	GLX_FORCE_INLINE ConstReferenceType GetFirstElement() const
	{
		GLX_ASSERT(Length > 0);
		return *Data;
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

	GLX_FORCE_INLINE ConstIteratorType cbegin() const
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

	GLX_FORCE_INLINE ConstIteratorType cend() const
	{
		return ConstIteratorType(Data + Length);
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool Equals(ConstPointerType InStr, GlxBool InIgnoreCase = false) const
	{
		if (InIgnoreCase)
		{
			return CStringUtils::Stricmp(Data, InStr) == 0;
		}
		return CStringUtils::Strcmp(Data, InStr) == 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool Equals(const GlxBasicString& InStr, GlxBool InIgnoreCase = false) const
	{
		if (Length == InStr.Length)
		{
			if (InIgnoreCase)
			{
				return CStringUtils::Stricmp(Data, InStr.Data) == 0;
			}

			return CStringUtils::Strcmp(Data, InStr.Data) == 0;
		}
		return false;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxInt32 Compare(ConstPointerType InStr, GlxBool InIgnoreCase = false) const
	{
		if (InIgnoreCase)
		{
			return CStringUtils::Stricmp(Data, InStr);
		}
		return CStringUtils::Strcmp(Data, InStr);
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxInt32 Compare(const GlxBasicString& InStr, GlxBool InIgnoreCase = false) const
	{
		if (InIgnoreCase)
		{
			return CStringUtils::Stricmp(Data, InStr.Data);
		}

		return CStringUtils::Strcmp(Data, InStr.Data);
	}

	GLX_NODISCARD GlxInt32 Compare(SizeType InLhsStartPos, SizeType InLhsLength, const GlxBasicString& InRhs, SizeType InRhsStartPos, SizeType InRhsLength, GlxBool InIgnoreCase = false) const
	{
		GLX_ASSERT((InLhsStartPos >= 0 && InLhsStartPos + InLhsLength <= Length) && (InRhsStartPos >= 0 && InRhsStartPos + InRhsLength <= InRhs.Length));

		PointerType LhsPtr = Data + InLhsStartPos;
		PointerType RhsPtr = InRhs.Data + InRhsStartPos;

		GlxInt32 Result = InIgnoreCase ?
			CStringUtils::Strnicmp(LhsPtr, RhsPtr, GLX_MIN(InLhsLength, InRhsLength)) :
			CStringUtils::Strncmp(LhsPtr, RhsPtr, GLX_MIN(InLhsLength, InRhsLength));

		if (Result != 0)
		{
			return Result;
		}

		if (InLhsLength < InRhsLength)
		{
			return -1;
		}

		if (InLhsLength > InRhsLength)
		{
			return 1;
		}

		return 0;
	}

	// ==
	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator==(ConstPointerType InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr) == 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator==(const GlxBasicString& InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr.Data) == 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBool operator==(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return CStringUtils::Strcmp(InLhs, InRhs.Data) == 0;
	}

	// !=
	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator!=(ConstPointerType InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr) != 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator!=(const GlxBasicString& InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr.Data) != 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBool operator!=(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return CStringUtils::Strcmp(InLhs, InRhs.Data) != 0;
	}

	// >
	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator>(ConstPointerType InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr) > 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator>(const GlxBasicString& InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr.Data) > 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBool operator>(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return CStringUtils::Strcmp(InLhs, InRhs.Data) > 0;
	}

	// >=
	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator>=(ConstPointerType InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr) >= 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator>=(const GlxBasicString& InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr.Data) >= 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBool operator>=(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return CStringUtils::Strcmp(InLhs, InRhs.Data) >= 0;
	}

	// <
	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator<(ConstPointerType InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr) < 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator<(const GlxBasicString& InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr.Data) < 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBool operator<(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return CStringUtils::Strcmp(InLhs, InRhs.Data) < 0;
	}

	// <=
	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator<=(ConstPointerType InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr) <= 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool operator<=(const GlxBasicString& InStr) const
	{
		return CStringUtils::Strcmp(Data, InStr.Data) <= 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBool operator<=(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return CStringUtils::Strcmp(InLhs, InRhs.Data) <= 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GLX_NODISCARD GLX_FORCE_INLINE GlxBasicString Substring(SizeType InStartPos) const
	{
		GLX_ASSERT(InStartPos >= 0 && InStartPos < Length);
		return GlxBasicString(Data + InStartPos, Length - InStartPos);
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBasicString Substring(SizeType InStartPos, SizeType InLength) const
	{
		GLX_ASSERT(InStartPos >= 0 && InStartPos + InLength <= Length);
		return GlxBasicString(Data + InStartPos, InLength);
	}

	void ToUpper()
	{
		for (SizeType i = 0; i < Length; ++i)
		{
			Data[i] = CharUtils::ToUpper(Data[i]);
		}
	}

	void ToLower()
	{
		for (SizeType i = 0; i < Length; ++i)
		{
			Data[i] = CharUtils::ToLower(Data[i]);
		}
	}

	void Reverse()
	{
		if (Length > 1)
		{
			PointerType Start = Data;
			PointerType End = Data + (Length - 1);
			ElementType TmpChar;
			do
			{
				TmpChar = *Start;
				*Start = *End;
				*End = TmpChar;

				Start++, --End;
			} while (Start < End);
		}
	}

	GLX_NODISCARD SizeType Find(SizeType InSubstrLen, ConstPointerType InSubstr, SizeType InStartPos = 0, GlxBool InIgnoreCase = false) const
	{
		if (InStartPos < 0)
		{
			InStartPos = 0;
		}

		if (InSubstrLen > Length || InStartPos > Length - InSubstrLen)
		{
			return InvalidIndex;
		}

		if (*InSubstr == NullChar || !InSubstrLen)
		{
			return InStartPos;
		}

		ConstPointerType EndStrPos = Data + (Length - InSubstrLen) + 1;

		if (InIgnoreCase)
		{
			const ElementType FirstUpperSubstrChar = CharUtils::ToUpper(*InSubstr);
			for (ConstPointerType Tmp = Data + InStartPos; Tmp < EndStrPos; ++Tmp)
			{
				if (CharUtils::ToUpper(*Tmp) == FirstUpperSubstrChar && CStringUtils::Strnicmp(Tmp, InSubstr, InSubstrLen) == 0)
				{
					return static_cast<SizeType>(Tmp - Data);
				}
			}
		}
		else
		{
			for (ConstPointerType Tmp = Data + InStartPos; Tmp < EndStrPos; ++Tmp)
			{
				if (*Tmp == *InSubstr && CStringUtils::Strncmp(Tmp, InSubstr, InSubstrLen) == 0)
				{
					return static_cast<SizeType>(Tmp - Data);
				}
			}
		}

		return InvalidIndex;
	}

	GLX_NODISCARD SizeType FindLast(SizeType InSubstrLen, ConstPointerType InSubstr, SizeType InStartPos = InvalidIndex, GlxBool InIgnoreCase = false) const
	{
		if (InStartPos == InvalidIndex || InStartPos > Length)
		{
			InStartPos = Length;
		}

		if (InSubstrLen > Length)
		{
			return InvalidIndex;
		}

		if (*InSubstr == NullChar || InSubstrLen == 0)
		{
			return InStartPos;
		}

		if (InIgnoreCase)
		{
			SizeType Offset = Length - InSubstrLen;
			const ElementType FirstUpperSubstrChar = CharUtils::ToUpper(*InSubstr);

			for (ConstPointerType Tmp = Data + (GLX_MIN(InStartPos, Offset));; --Tmp)
			{
				if (CharUtils::ToUpper(*Tmp) == FirstUpperSubstrChar && CStringUtils::Strnicmp(Tmp, InSubstr, InSubstrLen) == 0)
				{
					return static_cast<SizeType>(Tmp - Data);
				}

				if (Tmp == Data)
				{
					break;
				}
			}
		}
		else
		{
			SizeType Offset = Length - InSubstrLen;

			for (ConstPointerType Tmp = Data + (GLX_MIN(InStartPos, Offset));; --Tmp)
			{
				if (*Tmp == *InSubstr && CStringUtils::Strncmp(Tmp, InSubstr, InSubstrLen) == 0)
				{
					return static_cast<SizeType>(Tmp - Data);
				}

				if (Tmp == Data)
				{
					break;
				}
			}
		}

		return InvalidIndex;
	}

	GLX_NODISCARD GLX_FORCE_INLINE SizeType Find(const GlxBasicString& InSubstr, SizeType InStartPos = 0, GlxBool InIgnoreCase = false) const
	{
		return Find(InSubstr.Length, InSubstr.Data, InStartPos, InIgnoreCase);
	}

	GLX_NODISCARD GLX_FORCE_INLINE SizeType FindLast(const GlxBasicString& InSubstr, SizeType InStartPos = InvalidIndex, GlxBool InIgnoreCase = false) const
	{
		return FindLast(InSubstr.Length, InSubstr.Data, InStartPos, InIgnoreCase);
	}

	GLX_NODISCARD SizeType Find(ConstPointerType InSubstr, SizeType InStartPos = 0, GlxBool InIgnoreCase = false) const
	{
		if (InStartPos < 0)
		{
			InStartPos = 0;
		}

		ConstPointerType Pos = InIgnoreCase ? CStringUtils::Stristr(Data + InStartPos, InSubstr) : CStringUtils::Strstr(Data + InStartPos, InSubstr);

		return Pos ? static_cast<SizeType>(Pos - Data) : InvalidIndex;
	}

	GLX_NODISCARD SizeType FindLast(ConstPointerType InSubstr, SizeType InStartPos = InvalidIndex, GlxBool InIgnoreCase = false) const
	{
		return FindLast(CStringUtils::Strlen(InSubstr), InSubstr, InStartPos, InIgnoreCase);
	}

	GLX_NODISCARD SizeType FindChar(ElementType InCh, SizeType InStartPos = 0, GlxBool InIgnoreCase = false) const
	{
		if (InStartPos < 0)
		{
			InStartPos = 0;
		}

		if (InIgnoreCase)
		{
			ConstPointerType Start = Data + InStartPos;
			ElementType UpperChr = CharUtils::ToUpper(InCh);

			while (*Start)
			{
				if (CharUtils::ToUpper(*Start) == UpperChr)
				{
					return static_cast<SizeType>(Start - Data);
				}
				++Start;
			}
		}
		else
		{
			ConstPointerType Pos = CStringUtils::Strchr(Data + InStartPos, InCh);
			return Pos ? static_cast<SizeType>(Pos - Data) : InvalidIndex;
		}

		return InvalidIndex;
	}

	GLX_NODISCARD SizeType FindLastChar(ElementType InCh, SizeType InStartPos = InvalidIndex, GlxBool InIgnoreCase = false) const
	{
		ConstPointerType End = Data + ((InStartPos < 0) ? Length : InStartPos);

		if (InIgnoreCase)
		{
			ElementType UpperChr = CharUtils::ToUpper(InCh);
			for (;; --End)
			{
				if (CharUtils::ToUpper(*End) == UpperChr)
				{
					return static_cast<SizeType>(End - Data);
				}

				if (End == Data)
				{
					break;
				}
			}
		}
		else
		{
			for (;; --End)
			{
				if (*End == InCh)
				{
					return static_cast<SizeType>(End - Data);
				}

				if (End == Data)
				{
					break;
				}
			}
		}

		return InvalidIndex;
	}

	GLX_NODISCARD GlxBool Contains(ConstPointerType InSubstr, GlxBool InIgnoreCase = false) const
	{
		if (InIgnoreCase)
		{
			return CStringUtils::Stristr(Data, InSubstr) != nullptr;
		}
		return CStringUtils::Strstr(Data, InSubstr) != nullptr;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool Contains(const GlxBasicString& InSubstr, GlxBool InIgnoreCase = false) const
	{
		return Contains(InSubstr.Data, InIgnoreCase);
	}

	GLX_FORCE_INLINE void Clear()
	{
		Length = 0;
		*Data = NullChar;
	}

	void Resize(SizeType InNewLength, ElementType InCh = NullChar)
	{
		GLX_ASSERT(InNewLength >= 0);

		if (InNewLength == Length)
		{
			return;
		}

		if (InNewLength > Capacity)
		{
			Capacity = InNewLength;
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			GLX_FREE(Data);
			Data = NewData;
		}

		if (InNewLength > Length)
		{
			if constexpr (IsChar)
			{
				GLX_MEMSET(Data + Length, InCh, InNewLength - Length);
			}
			else if constexpr (IsWChar)
			{
				GLX_WMEMSET(Data + Length, InCh, InNewLength - Length);
			}
		}

		Data[InNewLength] = NullChar;
		Length = InNewLength;
	}

	void Reserve(SizeType NewCapacity)
	{
		if (NewCapacity > Capacity)
		{
			Capacity = NewCapacity;
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			GLX_FREE(Data);
			Data = NewData;
			Data[Length] = NullChar;
		}
	}

	void Shrink()
	{
		if (Capacity != Length)
		{
			Capacity = Length;
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			GLX_FREE(Data);
			Data = NewData;
			Data[Length] = NullChar;
		}
	}

	GLX_NODISCARD GlxBool StartsWith(ConstPointerType InPrefix, SizeType InPrefixLen, GlxBool InIgnoreCase = false) const
	{
		if (InIgnoreCase)
		{
			return InPrefixLen >= 0 && Length >= InPrefixLen && CStringUtils::Strnicmp(Data, InPrefix, InPrefixLen) == 0;
		}
		return InPrefixLen >= 0 && Length >= InPrefixLen && CStringUtils::Strncmp(Data, InPrefix, InPrefixLen) == 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool StartsWith(ConstPointerType InPrefix, GlxBool InIgnoreCase = false) const
	{
		return StartsWith(InPrefix, CStringUtils::Strlen(InPrefix), InIgnoreCase);
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool StartsWith(const GlxBasicString& InPrefix, GlxBool InIgnoreCase = false) const
	{
		return StartsWith(InPrefix.Data, InPrefix.Length, InIgnoreCase);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	GLX_NODISCARD GlxBool EndsWith(ConstPointerType InSuffix, SizeType InSuffixLen, GlxBool InIgnoreCase = false) const
	{
		if (InIgnoreCase)
		{
			return InSuffixLen >= 0 && Length >= InSuffixLen && CStringUtils::Strnicmp(Data + (Length - InSuffixLen), InSuffix, InSuffixLen) == 0;
		}
		return InSuffixLen >= 0 && Length >= InSuffixLen && CStringUtils::Strncmp(Data + (Length - InSuffixLen), InSuffix, InSuffixLen) == 0;
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool EndsWith(ConstPointerType InSuffix, GlxBool InIgnoreCase = false) const
	{
		return EndsWith(InSuffix, CStringUtils::Strlen(InSuffix), InIgnoreCase);
	}

	GLX_NODISCARD GLX_FORCE_INLINE GlxBool EndsWith(const GlxBasicString& InSuffix, GlxBool InIgnoreCase = false) const
	{
		return EndsWith(InSuffix.Data, InSuffix.Length, InIgnoreCase);
	}

private:
	static GLX_NODISCARD GlxBasicString Concat(ConstPointerType InLhs, SizeType InLhsLen, ConstPointerType InRhs, SizeType InRhsLen)
	{
		GLX_ASSERT(InLhsLen >= 0 && InRhsLen >= 0);

		GlxBasicString Str(InLhsLen + InRhsLen);
		GLX_MEMCPY(Str.Data, InLhs, InLhsLen * sizeof(ElementType));
		GLX_MEMCPY(Str.Data + InLhsLen, InRhs, InRhsLen * sizeof(ElementType));
		return Str;
	}

	static GLX_NODISCARD GlxBasicString Concat(GlxBasicString&& InLhs, GlxBasicString&& InRhs)
	{
		GlxBasicString Str(InLhs.Length + InRhs.Length);

		GLX_MEMCPY(Str.Data, InLhs.Data, InLhs.Length * sizeof(ElementType));
		GLX_MEMCPY(Str.Data + InLhs.Length, InRhs.Data, InRhs.Length * sizeof(ElementType));
		InLhs.Length = 0;
		*InLhs.Data = NullChar;
		InRhs.Length = 0;
		*InRhs.Data = NullChar;
		return Str;
	}

	static GLX_NODISCARD GlxBasicString Concat(GlxBasicString&& InLhs, ConstPointerType InRhs, SizeType InRhsLen)
	{
		GlxBasicString Str(InLhs.Length + InRhsLen);

		GLX_MEMCPY(Str.Data, InLhs.Data, InLhs.Length * sizeof(ElementType));
		GLX_MEMCPY(Str.Data + InLhs.Length, InRhs, InRhsLen * sizeof(ElementType));
		InLhs.Length = 0;
		*InLhs.Data = NullChar;
		return Str;
	}

	static GLX_NODISCARD GlxBasicString Concat(ConstPointerType InLhs, SizeType InLhsLen, GlxBasicString&& InRhs)
	{
		GlxBasicString Str(InLhsLen + InRhs.Length);

		GLX_MEMCPY(Str.Data, InLhs, InLhsLen * sizeof(ElementType));
		GLX_MEMCPY(Str.Data + InLhsLen, InRhs.Data, InRhs.Length * sizeof(ElementType));
		InRhs.Length = 0;
		*InRhs.Data = NullChar;
		return Str;
	}

public:
	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(const GlxBasicString& InLhs, const GlxBasicString& InRhs)
	{
		return Concat(InLhs.Data, InLhs.Length, InRhs.Data, InRhs.Length);
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(const GlxBasicString& InLhs, ConstPointerType InRhs)
	{
		return Concat(InLhs.Data, InLhs.Length, InRhs, CStringUtils::Strlen(InRhs));
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(const GlxBasicString& InLhs, GlxBasicString&& InRhs)
	{
		return Concat(InLhs.Data, InLhs.Length, Move(InRhs));
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(ConstPointerType InLhs, const GlxBasicString& InRhs)
	{
		return Concat(InLhs, CStringUtils::Strlen(InLhs), InRhs.Data, InRhs.Length);
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(ConstPointerType InLhs, GlxBasicString&& InRhs)
	{
		return Concat(InLhs, CStringUtils::Strlen(InLhs), Move(InRhs));
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(GlxBasicString&& InLhs, const GlxBasicString& InRhs)
	{
		return Concat(Move(InLhs), InRhs.Data, InRhs.Length);
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(GlxBasicString&& InLhs, GlxBasicString&& InRhs)
	{
		return Concat(Move(InLhs), Move(InRhs));
	}

	GLX_NODISCARD GLX_FORCE_INLINE friend GlxBasicString operator+(GlxBasicString&& InLhs, ConstPointerType InRhs)
	{
		return Concat(Move(InLhs), InRhs, CStringUtils::Strlen(InRhs));
	}

	void Append(ConstPointerType InStr, SizeType InLength)
	{
		GLX_ASSERT(InStr != nullptr && InLength >= 0);

		if (Length + InLength > Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InLength);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			GLX_MEMCPY(NewData + Length, InStr, InLength * sizeof(ElementType));
			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			GLX_MEMCPY(Data + Length, InStr, InLength * sizeof(ElementType));
		}

		Length += InLength;
		Data[Length] = NullChar;
	}

	void Append(ElementType InCh, SizeType InCount)
	{
		GLX_ASSERT(InCount >= 0);

		if (Length + InCount > Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InCount);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, Data, Length * sizeof(ElementType));
			if constexpr (IsChar)
			{
				GLX_MEMSET(NewData + Length, InCh, InCount);
			}
			else if constexpr (IsWChar)
			{
				GLX_WMEMSET(NewData + Length, InCh, InCount);
			}
			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			if constexpr (IsChar)
			{
				GLX_MEMSET(Data + Length, InCh, InCount);
			}
			else if constexpr (IsWChar)
			{
				GLX_WMEMSET(Data + Length, InCh, InCount);
			}
		}

		Length += InCount;
		Data[Length] = NullChar;
	}

	GLX_FORCE_INLINE void Append(const GlxBasicString& InStr)
	{
		Append(InStr.Data, InStr.Length);
	}

	GLX_FORCE_INLINE void Append(ConstPointerType InStr)
	{
		Append(InStr, CStringUtils::Strlen(InStr));
	}

	GLX_FORCE_INLINE void Append(const GlxBasicString& InStr, SizeType InStartPos, SizeType InLength)
	{
		GLX_ASSERT(InStartPos >= 0 && InStartPos + InLength <= InStr.Length);
		Append(InStr.Data + InStartPos, InLength);
	}

	GLX_FORCE_INLINE GlxBasicString& operator+=(const GlxBasicString& InStr)
	{
		Append(InStr.Data, InStr.Length);
		return *this;
	}

	GLX_FORCE_INLINE GlxBasicString& operator+=(ConstPointerType InStr)
	{
		Append(InStr, CStringUtils::Strlen(InStr));
		return *this;
	}

	GLX_FORCE_INLINE GlxBasicString& operator+=(ElementType InCh)
	{
		Append(InCh, 1);
		return *this;
	}

	void RemoveAt(SizeType InPos, SizeType InLength)
	{
		GLX_ASSERT(InPos >= 0 && InLength >= 0 && InPos + InLength <= Length);

		if (InPos == 0 && InLength == Length)
		{
			Length = 0, *Data = NullChar;
			return;
		}

		Length -= InLength;

		PointerType Dest = Data + InPos;
		GLX_MEMCPY(Dest, Dest + InLength, (Length - InPos) * sizeof(ElementType));
		Data[Length] = NullChar;
	}

	void Insert(SizeType InIndex, ConstPointerType InStr, SizeType InLength)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex <= Length && InLength >= 0 && InStr != nullptr);

		if (Length + InLength > Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InLength);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			PointerType Dest = NewData + InIndex;
			GLX_MEMCPY(NewData, Data, InIndex * sizeof(ElementType));
			GLX_MEMCPY(Dest, InStr, InLength * sizeof(ElementType));
			GLX_MEMCPY(Dest + InLength, Data + InIndex, (Length - InIndex) * sizeof(ElementType));
			GLX_FREE(Data);
			Data = NewData;
		}
		else
		{
			PointerType Dest = Data + InIndex;
			GLX_MEMMOVE(Dest + InLength, Dest, (Length - InIndex) * sizeof(ElementType));
			GLX_MEMCPY(Dest, InStr, InLength * sizeof(ElementType));
		}

		Length += InLength;
		Data[Length] = NullChar;
	}

	void Insert(SizeType InIndex, ElementType InCh, SizeType InCount)
	{
		GLX_ASSERT(InIndex >= 0 && InIndex <= Length && InCount >= 0);

		if (Length + InCount > Capacity)
		{
			Capacity = static_cast<SizeType>(Capacity * GrowthFactor + InCount);
			PointerType NewData = static_cast<PointerType>(GLX_MALLOC((Capacity + 1) * sizeof(ElementType)));
			GLX_MEMCPY(NewData, Data, InIndex * sizeof(ElementType));
			GLX_MEMCPY(NewData + InIndex + InCount, Data + InIndex, (Length - InIndex) * sizeof(ElementType));
			GLX_FREE(Data);
			Data = NewData;
		}

		PointerType Dest = Data + InIndex;
		GLX_MEMMOVE(Dest + InCount, Dest, (Length - InIndex) * sizeof(ElementType));
		if constexpr (IsChar)
		{
			GLX_MEMSET(Dest, InCh, InCount);
		}
		else if constexpr (IsWChar)
		{
			GLX_WMEMSET(Dest, InCh, InCount);
		}

		Length += InCount;
		Data[Length] = NullChar;
	}

	GLX_FORCE_INLINE void Insert(SizeType InIndex, ConstPointerType InStr)
	{
		Insert(InIndex, InStr, CStringUtils::Strlen(InStr));
	}

	GLX_FORCE_INLINE void Insert(SizeType InIndex, const GlxBasicString& InStr)
	{
		Insert(InIndex, InStr.Data, InStr.Length);
	}

	GLX_FORCE_INLINE void Insert(SizeType InIndex, const GlxBasicString& InStr, SizeType InStartPos, SizeType InLength)
	{
		GLX_ASSERT(InStartPos >= 0 && InStartPos + InLength <= InStr.Length);
		Insert(InIndex, InStr.Data + InStartPos, InLength);
	}

	void TrimStart()
	{
		SizeType Pos = 0;
		while (Pos < Length)
		{
			if constexpr (IsChar)
			{
				if (!isspace(Data[Pos]))
				{
					break;
				}
			}
			else if constexpr (IsWChar)
			{
				if (!iswspace(Data[Pos]))
				{
					break;
				}
			}
			++Pos;
		}

		RemoveAt(0, Pos);
	}

	void TrimEnd()
	{
		SizeType End = Length;
		while (End > 0)
		{
			if constexpr (IsChar)
			{
				if (!isspace(Data[End - 1]))
				{
					break;
				}
			}
			else if constexpr (IsWChar)
			{
				if (!iswspace(Data[End - 1]))
				{
					break;
				}
			}
			--End;
		}

		RemoveAt(End, Length - End);
	}

	void Trim()
	{
		TrimStart();
		TrimEnd();
	}

	template<typename... TArgs>
	static GlxBasicString<ElementType> Format(ConstPointerType InFmt, TArgs&&... InArgs)
	{
		fmt::basic_memory_buffer<ElementType> Buffer{};

		if constexpr (IsChar)
		{
			fmt::detail::vformat_to(Buffer, fmt::string_view{ InFmt }, fmt::vargs<TArgs...>{ { InArgs... } });
		}
		else if constexpr (IsWChar)
		{
			fmt::detail::vformat_to(Buffer, fmt::wstring_view{ InFmt }, fmt::make_format_args<fmt::wformat_context>(InArgs...));
		}

		return GlxBasicString<ElementType>{ Buffer.data(), static_cast<SizeType>(Buffer.size()) };
	}

private:
	static ConstPointerType FindAnyCharImpl(ConstPointerType InStr, ConstPointerType InChars)
	{
		if (!InStr || !InChars)
		{
			return nullptr;
		}

		while (*InStr != NullChar)
		{
			if (CStringUtils::Strchr(InChars, *InStr))
			{
				return InStr;
			}

			++InStr;
		}
		return nullptr;
	}

public:
	void SplitBySeparators(GlxDynamicArray<GlxBasicString<ElementType>>& InArr, ConstPointerType InSeps) const
	{
		SizeType LastOffset = 0, Offset;
		ConstPointerType Found = FindAnyCharImpl(Data, InSeps);

		while (Found)
		{
			Offset = static_cast<SizeType>(Found - Data);
			SizeType Count = Offset - LastOffset;
			if (Count > 0)
			{
				InArr.EmplaceBack(*this, LastOffset, Count);
			}
			LastOffset = Offset + 1;
			Found = FindAnyCharImpl(Data + LastOffset, InSeps);
		}

		Offset = Length - LastOffset;
		if (Offset > 0)
		{
			InArr.EmplaceBack(*this, LastOffset, Offset);
		}
	}

	void SplitByString(GlxDynamicArray<GlxBasicString<ElementType>>& InArr, ConstPointerType InStr) const
	{
		SizeType LastOffset = 0, Offset;

		const SizeType StrLen = CStringUtils::Strlen(InStr);
		ConstPointerType Found = CStringUtils::Strstr(Data, InStr);

		while (Found)
		{
			Offset = static_cast<SizeType>(Found - Data);
			SizeType Count = Offset - LastOffset;

			if (Count > 0)
			{
				InArr.EmplaceBack(*this, LastOffset, Count);
			}
			LastOffset = Offset + StrLen;
			Found = CStringUtils::Strstr(Data + LastOffset, InStr);
		}

		Offset = Length - LastOffset;
		if (Offset > 0)
		{
			InArr.EmplaceBack(*this, LastOffset, Offset);
		}
	}

private:
	PointerType Data;
	SizeType Length;
	SizeType Capacity;
};

using GlxString = GlxBasicString<GlxChar>;
using GlxWString = GlxBasicString<GlxWChar>;
