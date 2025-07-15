#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Utils/NonCopyable.h"

#if defined(GLX_PLATFORM_WINDOWS)
///////////////////////////////////////
#include <Windows.h>
using GlxMutexHandle = CRITICAL_SECTION;
///////////////////////////////////////
#else
	#error "GlxMutexHandle is not declared on the current platform!"
#endif

class GlxConditionVariable;

class GLX_API GlxMutex : public GlxNonCopyable
{
public:
	friend class GlxConditionVariable;

	GlxMutex() noexcept;
	~GlxMutex();

	void Lock();
	void Unlock();
	bool TryLock();

	GLX_FORCE_INLINE GlxMutexHandle GetHandle() const
	{
		return Handle;
	}

private:
	GlxMutexHandle Handle;
};

#if defined(GLX_PLATFORM_WINDOWS)
///////////////////////////////////////
#include "Windows/WindowsMutexImpl.h"
///////////////////////////////////////
#else
	#error "GlxMutex is not implemented on the current platform!"
#endif