#pragma once

#include "bool_to_type.h"

namespace nova {

//Type traits for check if a type T has the member function size
template<class T>
class has_mem_fun_size{
public:
    template<typename U,	int (U::*)()> struct SFINAE1 {};
    template<typename U,	int (U::*)() const> struct SFINAE2 {};
    template<typename U>	static char Test(SFINAE1<U, &U::size>*);
    template<typename U>	static char Test(SFINAE2<U, &U::size>*);
    template<typename U>	static int Test(...);

    static const bool value = sizeof(Test<T>(0)) == sizeof(char);

    typedef bool value_type;

    typedef typename bool_to_type<value>::type type;
};

} //namespace nova


