#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template <class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0>
{
    typedef Head TargetType;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i>
{
    typedef typename TypeAt<Tail, i-1>::TargetType TargetType;
};