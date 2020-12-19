#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template <class T>
struct IndexOf<NullType, T>
{
    enum { pos = -1 };
};

template <class T, class Tail>
struct IndexOf<TypeList<T, Tail>, T>
{
    enum { pos = 0 };
};

template <class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
private:
    enum { temp = IndexOf<Tail, T>::pos };
public:
    enum { pos = temp == -1 ? -1 : 1 + temp };
};