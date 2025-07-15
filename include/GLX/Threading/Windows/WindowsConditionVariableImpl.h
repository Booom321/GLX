#pragma once

#if defined(GLX_PLATFORM_WINDOWS)

GlxConditionVariable::GlxConditionVariable()
{
	InitializeConditionVariable(&Handle);
}

GlxConditionVariable::~GlxConditionVariable()
{}

void GlxConditionVariable::NotifyOne() noexcept
{
	WakeConditionVariable(&Handle);
}

void GlxConditionVariable::NotifyAll() noexcept
{
	WakeAllConditionVariable(&Handle);
}

void GlxConditionVariable::Wait(GlxMutex& InMutex)
{
	SleepConditionVariableCS(&Handle, &InMutex.Handle, INFINITE);
}

void GlxConditionVariable::WaitFor(GlxMutex& InMutex, GlxInt32 InMilliseconds)
{
	SleepConditionVariableCS(&Handle, &InMutex.Handle, InMilliseconds);
}

#endif
