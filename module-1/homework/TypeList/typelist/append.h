#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template <>
struct Append<NullType, NullType>
{
    typedef NullType NewTypeList;
};

template <class T>
struct Append<NullType, T>
{
    typedef TypeList<T, NullType> NewTypeList;
};

template <class Head, class Tail>
struct Append<NullType, TypeList<Head, Tail> >
{
    typedef TypeList<Head, Tail> NewTypeList;
};

template <class Head, class Tail, class T>
struct Append<TypeList<Head, Tail>, T>
{
    typedef TypeList <Head, 
        typename Append<Tail, T>::NewTypeList> 
      NewTypeList;
};