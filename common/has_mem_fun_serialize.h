#pragma once

#include "bool_to_type.h"

namespace nova {

    //Type traits for check if a type T has the member function size
    template<class T>
    class has_mem_fun_serialize{
    public:
        template<typename U, U> struct SFINAE {};

        template<typename C>	static char Test(SFINAE<int (C::*)(Serializer&), &C::serialize>*);
        template<typename C>	static int Test(...);

        static const bool value = sizeof(Test<T>(0)) == sizeof(char);

        typedef bool value_type;

        typedef typename bool_to_type<value>::type type;
    };
} //namespace nova
