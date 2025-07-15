#pragma once

#include "GLX/Types/Delegate.h"
#include "GLX/Utils/NonCopyable.h"

#if defined(GLX_PLATFORM_WINDOWS)
///////////////////////////////////////
#include <Windows.h>
using GlxConditionVariableHandle = CONDITION_VARIABLE;
///////////////////////////////////////
#else
	#error "GlxConditionVariableHandle is not declared on the current platform!"
#endif

#include "Mutex.h"

class GLX_API GlxConditionVariable : public GlxNonCopyable
{
public:
	GlxConditionVariable();
	~GlxConditionVariable();

	void NotifyOne() noexcept;
	void NotifyAll() noexcept;
	void Wait(GlxMutex& InMutex);
	void WaitFor(GlxMutex& InMutex, GlxInt32 InMilliseconds);

	template<typename TPredicate>
	void Wait(GlxMutex& InMutex, TPredicate InPred)
	{
		while (!InPred())
		{
			Wait(InMutex);
		}
	}

	GLX_FORCE_INLINE GlxConditionVariableHandle GetHandle() const
	{
		return Handle;
	}

private:
	GlxConditionVariableHandle Handle;
};

#if defined(GLX_PLATFORM_WINDOWS)
///////////////////////////////////////
#include "Windows/WindowsConditionVariableImpl.h"
///////////////////////////////////////
#else
	#error "GlxConditionVariable is not implemented on the current platform!"
#endif