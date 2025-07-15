#pragma once

#include "GLX/Types/DataTypes.h"
#include "GLX/TypeTraits/Logical.h"
#include "GLX/TypeTraits/PrimaryTypes.h"
#include "GLX/TypeTraits/Trivial.h"
#include "GLX/TypeTraits/IsBitwiseConstructible.h"
#include "GLX/TypeTraits/MemoryTraits.h"
#include "GLX/TypeTraits/RemoveReference.h"

#include <stdlib.h>

#if !defined(GLX_MALLOC)
	#define GLX_MALLOC(...) malloc(__VA_ARGS__)
#endif

#if !defined(GLX_FREE)
	#define GLX_FREE(...) free(__VA_ARGS__)
#endif

#if !defined(GLX_MEMCPY)
	#define GLX_MEMCPY(...) memcpy(__VA_ARGS__)
#endif

#if !defined(GLX_MEMSET)
	#define GLX_MEMSET(...) memset(__VA_ARGS__)
#endif

#if !defined(GLX_MEMMOVE)
	#define GLX_MEMMOVE(...) memmove(__VA_ARGS__)
#endif

#if !defined(GLX_MEMCMP)
	#define GLX_MEMCMP(...) memcmp(__VA_ARGS__)
#endif

#if !defined(GLX_MEMCHR)
	#define GLX_MEMCHR(...) memchr(__VA_ARGS__)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GlxMemoryUtils
{
public:
	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void DefaultConstructElements(TType* InDest, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemsetCompatible<TType>::Value)
		{
			GLX_MEMSET(InDest, 0, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				new (InDest) TType();
				++InDest;
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void DestructElements(TType* InDest, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (!GlxIsTriviallyDestructible<TType>::Value)
		{
			while (InCount)
			{
				InDest->~TType();
				++InDest;
				--InCount;
			}
		}
	}

	template<typename TDestinationType, typename TSourceType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void CopyConstructElements(TDestinationType* InDest, const TSourceType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsBitwiseConstructible<TDestinationType, TSourceType>::Value)
		{
			GLX_MEMCPY(InDest, InSource, InCount * sizeof(TSourceType));
		}
		else
		{
			while (InCount)
			{
				new (InDest) TDestinationType(*InSource);
				++InDest;
				++InSource;
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void MoveConstructElements(TType* InDest, TType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemcpyCompatible<TType>::Value)
		{
			GLX_MEMCPY(InDest, InSource, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				new (InDest) TType(Move(*InSource));
				++InDest;
				++InSource;
				--InCount;
			}
		}
	}

	template<typename TDestinationType, typename TSourceType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void CopyBackwardConstructElements(TDestinationType* InDest, const TSourceType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsBitwiseConstructible<TDestinationType, TSourceType>::Value)
		{
			GLX_MEMMOVE(InDest - InCount, InSource - InCount, InCount * sizeof(TSourceType));
		}
		else
		{
			while (InCount)
			{
				new (--InDest) TDestinationType(*--InSource);
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void MoveBackwardConstructElements(TType* InDest, TType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemmoveCompatible<TType>::Value)
		{
			GLX_MEMMOVE(InDest - InCount, InSource - InCount, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				new (--InDest) TType(Move(*--InSource));
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void CopyAssignElements(TType* InDest, const TType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemcpyCompatible<TType>::Value)
		{
			GLX_MEMCPY(InDest, InSource, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				*InDest = *InSource;
				++InDest;
				++InSource;
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void MoveAssignElements(TType* InDest, TType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemmoveCompatible<TType>::Value)
		{
			GLX_MEMCPY(InDest, InSource, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				*InDest = Move(*InSource);
				++InDest;
				++InSource;
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void CopyBackwardAssignElements(TType* InDest, const TType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemmoveCompatible<TType>::Value)
		{
			GLX_MEMMOVE(InDest - InCount, InSource - InCount, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				*--InDest = *--InSource;
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void MoveBackwardAssignElements(TType* InDest, TType* InSource, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		if constexpr (GlxIsMemmoveCompatible<TType>::Value)
		{
			GLX_MEMMOVE(InDest - InCount, InSource - InCount, InCount * sizeof(TType));
		}
		else
		{
			while (InCount)
			{
				*--InDest = Move(*--InSource);
				--InCount;
			}
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void FillConstructElements(TType* InDest, const TType& InValue, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		while (InCount)
		{
			new (InDest) TType(InValue);
			++InDest;
			--InCount;
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE void FillAssignElements(TType* InDest, const TType& InValue, TSizeType InCount)
	{
		if (InCount <= 0)
		{
			return;
		}

		while (InCount)
		{
			*InDest = InValue;
			++InDest;
			--InCount;
		}
	}

	template<typename TType, typename TSizeType = GlxSizeT>
	static GLX_FORCE_INLINE GlxBool CompareElements(const TType* InLhs, const TType* InRhs, TSizeType InCount)
	{
		if (InCount < 0)
		{
			return false;
		}

		if constexpr (GlxIsMemcmpCompatible<TType>::Value)
		{
			return (!InCount || !GLX_MEMCMP(InLhs, InRhs, InCount * sizeof(TType)));
		}
		else
		{
			while (InCount)
			{
				if (!(*InLhs == *InRhs))
				{
					return false;
				}

				++InLhs;
				++InRhs;
				--InCount;
			}

			return true;
		}
	}
};
