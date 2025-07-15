#pragma once

#include "GLX/Assert.h"
#include "GLX/TypeTraits/RemoveReference.h"

template<typename T>
class GlxSingleton
{
protected:
	GlxSingleton() = default;
	~GlxSingleton() = default;

private:
	GlxSingleton(const GlxSingleton&) = delete;
	GlxSingleton& operator=(const GlxSingleton&) = delete;
	GlxSingleton(GlxSingleton&&) = delete;
	GlxSingleton& operator=(GlxSingleton&&) = delete;

public:
	template<typename U /* = T */, typename... TArgs>
	static GLX_FORCE_INLINE void CreateInstance(TArgs&&... InArgs)
	{
		GLX_ASSERT(Instance == nullptr);
		Instance = new U(Forward<TArgs>(InArgs)...);
	}

	static GLX_FORCE_INLINE T* GetInstance()
	{
		return Instance;
	}

	static GLX_FORCE_INLINE void DeleteInstance()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}

protected:
	static T* Instance;
};

template<typename T>
T* GlxSingleton<T>::Instance = nullptr;
