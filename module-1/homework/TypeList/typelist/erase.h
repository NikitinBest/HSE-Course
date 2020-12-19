#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template <class T>
struct Erase<NullType, T>
{
    typedef NullType NewTypeList;
};

template <class T, class Tail>
struct Erase<TypeList<T, Tail>, T>
{
    typedef Tail NewTypeList;
};

template <class Head, class Tail, class T>
struct Erase<TypeList<Head, Tail>, T>
{
    typedef TypeList<Head,
        typename Erase<Tail, T>::NewTypeList>
      NewTypeList;
};