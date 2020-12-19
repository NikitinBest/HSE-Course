#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template <class T>
struct EraseAll<NullType, T>
{
    typedef NullType NewTypeList;
};

template <class T, class Tail>
struct EraseAll<TypeList<T, Tail>, T>
{
    typedef typename EraseAll<Tail, T>::NewTypeList NewTypeList;
};

template <class Head, class Tail, class T>
struct EraseAll<TypeList<Head, Tail>, T>
{
    typedef TypeList<Head,
        typename EraseAll<Tail, T>::NewTypeList>
      NewTypeList;
};