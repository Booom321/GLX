#pragma once

#include "GLX/Types/Delegate.h"
#include "GLX/Utils/NonCopyable.h"

#if defined(GLX_PLATFORM_WINDOWS)
///////////////////////////////////////
#include <Windows.h>
using GlxThreadHandle = HANDLE;
using GlxThreadID = DWORD;
///////////////////////////////////////
#else
	#error "GlxThreadHandle is not declared on the current platform!"
	#error "GlxThreadID is not declared on the current platform!"
#endif

class GlxThreadData
{
public:
	GlxThreadHandle ThreadHandle = nullptr;
	GlxThreadID ThreadID = 0;
};

class GLX_API GlxThread : public GlxNonCopyable
{
public:
	using ProcType = GlxDelegate<void()>;

	GlxThread() noexcept = default;

	GlxThread(GlxThread&& InOther) noexcept;
	GlxThread& operator=(GlxThread&& InOther) noexcept;

	template<typename TFunc, typename... TArgs>
	explicit GlxThread(TFunc&& InF, TArgs&&... InArgs);

	~GlxThread();

	GLX_FORCE_INLINE GlxThreadID GetID() const
	{
		return Data.ThreadID;
	}

	GLX_FORCE_INLINE GlxThreadHandle GetHandle() const
	{
		return Data.ThreadHandle;
	}

	GlxBool Joinable() const;
	GlxBool Join();
	GlxBool Detach();

private:
	GlxThreadData Data;
};

class GLX_API GlxThreadUtils
{
public:
	static void YieldThisThread();
	static GlxInt32 GetNumberOfThreads();
	static GlxThreadID GetCurrentThreadID();
	static void SleepFor(GlxInt64 InMilliseconds);
};

#if defined(GLX_PLATFORM_WINDOWS)
	#include "Windows/WindowsThreadImpl.h"
#else
	#error "GlxThread is not implemented on the current platform!"
	#error "GlxThreadUtils is not implemented on the current platform!"
#endif
