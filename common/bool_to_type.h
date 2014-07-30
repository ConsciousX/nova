#pragma once

#include <type_traits>

namespace nova {

template<bool T>
class bool_to_type{};

template<>
class bool_to_type<true>{
public:
    typedef std::true_type type;
};

template<>
class bool_to_type<false>{
public:
    typedef std::false_type type;
};

} //namespace nova

