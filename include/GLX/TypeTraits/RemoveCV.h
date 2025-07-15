#pragma once

template<typename T>
class GlxRemoveCV
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveCV<const T>
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveCV<volatile T>
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveCV<const volatile T>
{
public:
	using Type = T;
};
