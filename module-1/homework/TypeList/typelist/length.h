#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template <>
struct Length<NullType>
{
    enum { length = 0 };
};

template <class T, class U>
struct Length< TypeList<T, U> >
{
    enum { length = 1 + Length<U>::length};
};