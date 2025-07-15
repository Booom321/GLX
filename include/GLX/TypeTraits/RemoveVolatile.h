#pragma once

template<typename T>
class GlxRemoveVolatile
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveVolatile<volatile T>
{
public:
	using Type = T;
};
