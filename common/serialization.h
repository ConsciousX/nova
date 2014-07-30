#pragma once

#include <type_traits>
#include "is_vector.hpp"
#include "has_mem_fun_serialize.h"

namespace nova {

class serializer;

namespace serialization {

template<class serializer, class T>
int serialize(serializer& s, T& t)
{
    return t.serialize(s);
}

} //namespace serialization

class serializer
{
public:
    serializer(char* buff, size_t size)
        :m_buff(buff), m_len(size), m_pos(m_buff), m_size(0) 
    {}

    //Serialize general object
    template<class T>
    int serialize(T& t)
    {
        serialize_impl(t, 0);
        return m_size;
    }

    template<class T>
    int operator & (T& t)
    {
        return serialize(t);
    }

    //Serialize array
    template<class T>
    int serialize(T &t, size_t size, bool malloc = true, typename std::enable_if<std::is_pointer<T>,int>::type = 0)
    {
        if(malloc)	serialize_array_and_size((char*&)t, sizeof(*t), size);
        for(size_t i = 0; i < size; i++)
        {
            serialize_impl(t[i], 0);
        }
        return m_size;
    }

    int serialize(char*& t, size_t size, bool malloc)
    {
        if(malloc)	serialize_array_and_size(t, 1, size);
        serialize_fundamental(t, size);
        return m_size;
    }

    int serialize(char* t, size_t size)
    {
        serialize_fundamental(t, size);
        return m_size;
    }

    //Special handle for char array
    template<size_t N>
    int serialize(char (&t) [N])
    {
        return serialize_fundamental(t, N);
    }

private:
    //Is fundamental type
    template<class T>
    int serialize_impl(T& t,typename std::enable_if<std::is_fundamental<T>, int>::type)
    {
        return serialize_fundamental((void*)&t, sizeof(T));
    }

    //Is array type
    template<class T, size_t N>
    int serialize_impl(T& t, typename std::enable_if<std::is_array<T>, int>::type)
    {
        for(size_t i = 0; i < N; i++)
        {
            serialize(t[i]);
        }

        return m_size;
    }

    //Has member function serialize
    template<class T>
    int serialize_impl(T& t,typename std::enable_if<typename serialization::has_mem_fun_serialize<T>::type, int>::type)
    {
        return t.serialize(*this);
    }

    //Is vector
    template<class T>
    int serialize_impl(T& t,typename std::enable_if<typename is_vector<T>::type, int>::type)
    {
        uint32 temp_size = t.size();
        serialize(temp_size);
        if(temp_size != t.size())
        {
            t.resize(temp_size);
        }
        for(size_t i = 0; i< temp_size; i++)
        {
            serialize(t[i]);
        }
        return m_size;
    }

    template<class T>
    int serialize_impl(T &t, char)
    {
        return serialization::serialize(*this, t);
    }
private:
    virtual int serialize_fundamental(void* p, size_t size) = 0;
    virtual int serialize_array_and_size(char* &p, size_t type_size, size_t array_size) = 0;
protected:
    char * m_buff;
    size_t m_len;
    char * m_pos;
    size_t m_size;
};

class packer : public serializer
{
public:
    packer(char * buff, size_t size)
        :serializer(buff, size) 
    {}
private:
    virtual int serialize_fundamental(void* p, size_t size)
    {
        m_size += size;
        if (m_size > m_len) throw std::runtime_error("Serialization size is larger than buffer size");
        memcpy(m_pos,p,size);
        m_pos += size;
        return m_size;
    }
    virtual int serialize_array_and_size(char* &p, size_t type_size, size_t array_size)
    {
        return m_size;
    }
};

class unpacker : public serializer
{
public:
    unpacker(char * buff, size_t size)
        :serializer(buff, size)
    {}
private:
    virtual int serialize_fundamental(void* p, size_t size)
    {
        m_size += size;
        if(m_size > m_len) throw std::runtime_error("Serialization size is larger than buffer size");
        memcpy(p,m_pos,size);
        m_pos += size;
        return m_size;
    }
    virtual int serialize_array_and_size(char* &p, size_t type_size, size_t array_size)
    {
        p = (char*)malloc(type_size * array_size);
        return m_size;
    }
};

} //namespace nova

