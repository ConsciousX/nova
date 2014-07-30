#pragma once

#include "bool_to_type.h"
#include <vector>

namespace nova {

template<class T>
struct is_vector
{
    template<typename U>
    static char Test(std::vector<U>*);
    static int Test(...);

    static const bool value = (sizeof(Test((T*)0)) == sizeof(char));

    typedef bool value_type;

    typedef typename bool_to_type<value>::type type;
};

} //namespace nova
