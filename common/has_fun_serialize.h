#pragma once

#include "bool_to_type.h"

namespace nova{
    
//Type traits for check if a type T has the function size
template<class T>
class has_fun_serialize{
public:
    template<typename U, typename S, int(*)(S&, U&)> struct SFINAE {};
    template<typename U,typename S>	static char Test(SFINAE<U, S, serialize>*);
    template<typename U,typename S>	static int Test(...);

    static const bool value = sizeof(Test<T,Serializer>(0)) == sizeof(char);

    typedef bool value_type;

    typedef typename bool_to_type<value>::type type;
};

} //namespace nova

