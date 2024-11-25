#ifndef MY_FUNCS_H
#define MY_FUNCS_H

#include<cstddef>

inline std::size_t i_to_s(int i)
{
    return static_cast<std::size_t>(i);
}

inline int s_to_i(std::size_t s)
{
    return static_cast<int>(s);
}


#endif