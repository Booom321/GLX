#pragma once

#include "GLX/String/String.h"
#include "GLX/Math/Math.h"

#include <cstring>
#include <cmath>

#include "GLX/ThirdParty/xxHash/xxhash.h"

template<typename TKey, typename TCondition = void>
class GlxHasher;

namespace GlxNsHash
{
#if defined(GLX_PLATFORM_WIN64)
	GLX_INLINE GLX_CONSTEXPR GlxSizeT FNV_OffsetBasis = 14695981039346656037ULL;
	GLX_INLINE GLX_CONSTEXPR GlxSizeT FNV_Prime = 1099511628211ULL;
#else
	GLX_INLINE GLX_CONSTEXPR GlxSizeT FNV_OffsetBasis = 2166136261U;
	GLX_INLINE GLX_CONSTEXPR GlxSizeT FNV_Prime = 16777619U;
#endif

	template<typename TChar>
	GlxSizeT GetHashCodeFromString(const TChar* InStr, GlxSizeT InLen) noexcept
	{
		const GlxSizeT Count = InLen * sizeof(TChar);
		const unsigned char* const Data = reinterpret_cast<const unsigned char*>(InStr);

		GlxSizeT HashCode = FNV_OffsetBasis;
		for (GlxSizeT Idx = 0; Idx < Count; ++Idx)
		{
			HashCode ^= static_cast<GlxSizeT>(Data[Idx]);
			HashCode *= FNV_Prime;
		}

		return HashCode;
	}

	template<typename... TRest>
	GLX_INLINE GlxSizeT HashCombine(GlxSizeT InSeed /* = 0 */, TRest&&... InRest)
	{
		static GLX_CONSTEXPR GlxInt32 NumValues = sizeof...(TRest);
		GlxSizeT HashCodes[NumValues]{ GlxHasher<typename GlxRemoveCVRef<TRest>::Type>::GetHashCode(InRest)... };

		GlxSizeT Seed = InSeed;
		for (GlxInt32 Idx = 0; Idx < NumValues; ++Idx)
		{
			Seed ^= HashCodes[Idx] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
		}

		return Seed;
	}
}

template<>
class GlxHasher<const GlxChar*>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(const GlxChar* InStr)
	{
		return GlxNsHash::GetHashCodeFromString<GlxChar>(InStr, strlen(InStr));
	}
};

template<>
class GlxHasher<const GlxWChar*>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(const GlxWChar* InStr)
	{
		return GlxNsHash::GetHashCodeFromString<GlxWChar>(InStr, wcslen(InStr));
	}
};

template<>
class GlxHasher<GlxString>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(const GlxString& InStr)
	{
		return GlxNsHash::GetHashCodeFromString<GlxChar>(InStr.GetData(), InStr.GetElementCount());
	}
};

template<>
class GlxHasher<GlxWString>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(const GlxWString& InStr)
	{
		return GlxNsHash::GetHashCodeFromString<GlxWChar>(InStr.GetData(), InStr.GetElementCount());
	}
};

namespace GlxNsPrivate
{
	template<typename TArithmetic, typename = typename GlxEnableIf<GlxIsArithmetic<TArithmetic>::Value>::Type>
	class GlxDefaultHasher
	{
	public:
		static GLX_FORCE_INLINE GlxSizeT GetHashCode(TArithmetic InVal)
		{
			return XXH64(&InVal, sizeof(TArithmetic), 0);
		}
	};
}

template<> class GlxHasher<GlxInt8> : public GlxNsPrivate::GlxDefaultHasher<GlxInt8> {};
template<> class GlxHasher<GlxInt16> : public GlxNsPrivate::GlxDefaultHasher<GlxInt16> {};
template<> class GlxHasher<GlxInt32> : public GlxNsPrivate::GlxDefaultHasher<GlxInt32> {};
template<> class GlxHasher<GlxInt64> : public GlxNsPrivate::GlxDefaultHasher<GlxInt64> {};

template<> class GlxHasher<GlxUInt8> : public GlxNsPrivate::GlxDefaultHasher<GlxUInt8> {};
template<> class GlxHasher<GlxUInt16> : public GlxNsPrivate::GlxDefaultHasher<GlxUInt16> {};
template<> class GlxHasher<GlxUInt32> : public GlxNsPrivate::GlxDefaultHasher<GlxUInt32> {};
template<> class GlxHasher<GlxUInt64> : public GlxNsPrivate::GlxDefaultHasher<GlxUInt64> {};

template<> class GlxHasher<GlxBool> : public GlxNsPrivate::GlxDefaultHasher<GlxBool> {};
template<> class GlxHasher<GlxFloat> : public GlxNsPrivate::GlxDefaultHasher<GlxFloat> {};
template<> class GlxHasher<GlxDouble> : public GlxNsPrivate::GlxDefaultHasher<GlxDouble> {};
template<> class GlxHasher<GlxLongDouble> : public GlxNsPrivate::GlxDefaultHasher<GlxLongDouble> {};

template<> class GlxHasher<GlxChar> : public GlxNsPrivate::GlxDefaultHasher<GlxChar> {};
template<> class GlxHasher<GlxWChar> : public GlxNsPrivate::GlxDefaultHasher<GlxWChar> {};
#ifdef __cpp_char8_t
template<> class GlxHasher<GlxChar8> : public GlxNsPrivate::GlxDefaultHasher<GlxChar8> {};
#endif
template<> class GlxHasher<GlxChar16> : public GlxNsPrivate::GlxDefaultHasher<GlxChar16> {};
template<> class GlxHasher<GlxChar32> : public GlxNsPrivate::GlxDefaultHasher<GlxChar32> {};

template<typename TEnum>
class GlxHasher<TEnum, typename GlxEnableIf<GlxIsEnum<TEnum>::Value>::Type>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(TEnum InVal)
	{
		return GlxHasher<std::underlying_type_t<TEnum>>::GetHashCode(static_cast<std::underlying_type_t<TEnum>>(InVal));
	}
};

template<typename T>
class GlxHasher<T*, typename GlxEnableIf<!GlxOr<GlxIsSame<T, GlxChar>, GlxIsSame<T, GlxWChar>>::Value>::Type>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(const T* InVal)
	{
		static const GlxSizeT Shift = (GlxSizeT)log2(1 + sizeof(T));
		return (GlxSizeT)(InVal) >> Shift;
	}
};

template<typename TVec>
class GlxHasher<TVec, typename GlxEnableIf<GlxNsMath::GlxIsMathVector<TVec>::Value>::Type>
{
public:
	static GLX_FORCE_INLINE GlxSizeT GetHashCode(const TVec& InVec)
	{
		using ComponentType = typename TVec::Type;

		GlxSizeT Seed = 0;

		if constexpr (TVec::Size == 2)
		{
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.X) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.Y) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			return Seed;
		}
		else if constexpr (TVec::Size == 3)
		{
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.X) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.Y) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.Z) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			return Seed;
		}
		else if constexpr (TVec::Size == 4)
		{
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.X) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.Y) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.Z) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			Seed ^= GlxHasher<ComponentType>::GetHashCode(InVec.W) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
			return Seed;
		}
	}
};
