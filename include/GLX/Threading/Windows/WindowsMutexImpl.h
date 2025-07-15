#pragma once

#if defined(GLX_PLATFORM_WINDOWS)

GlxMutex::GlxMutex() noexcept
{
	InitializeCriticalSection(&Handle);
}

GlxMutex::~GlxMutex()
{
	DeleteCriticalSection(&Handle);
}

void GlxMutex::Lock()
{
	EnterCriticalSection(&Handle);
}

void GlxMutex::Unlock()
{
	LeaveCriticalSection(&Handle);
}

bool GlxMutex::TryLock()
{
	return TryEnterCriticalSection(&Handle) != 0;
}

#endif
