#pragma once

template<typename T>
class GlxRemoveConst
{
public:
	using Type = T;
};

template<typename T>
class GlxRemoveConst<const T>
{
public:
	using Type = T;
};
