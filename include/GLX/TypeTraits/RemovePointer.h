#pragma once

template<typename T>
class GlxRemovePointer
{
public:
	using Type = T;
};

template<typename T>
class GlxRemovePointer<T*>
{
public:
	using Type = T;
};

template<typename T>
class GlxRemovePointer<const T*>
{
public:
	using Type = T;
};

template<typename T>
class GlxRemovePointer<volatile T*>
{
public:
	using Type = T;
};

template<typename T>
class GlxRemovePointer<const volatile T*>
{
public:
	using Type = T;
};
