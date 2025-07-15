#pragma once

#include "GLX/Preprocessor.h"
#include "GLX/Utils/NonCopyable.h"

#include <mutex>

template<typename TMutex>
class GlxScopedLock : public GlxNonCopyable
{
public:
	using MutexType = TMutex;

	explicit GLX_INLINE GlxScopedLock(MutexType& InMut)
		: Mutex(InMut)
	{
		Mutex.Lock();
	}

	~GlxScopedLock()
	{
		Mutex.Unlock();
	}

private:
	MutexType& Mutex;
};

template<>
class GlxScopedLock<std::mutex> : public GlxNonCopyable
{
public:
	using MutexType = std::mutex;

	explicit GLX_INLINE GlxScopedLock(MutexType& InMut)
		: Mutex(InMut)
	{
		Mutex.lock();
	}

	~GlxScopedLock()
	{
		Mutex.unlock();
	}

private:
	MutexType& Mutex;
};
