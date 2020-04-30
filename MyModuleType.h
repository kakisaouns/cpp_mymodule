#ifndef MYMODULETYPE_H
#define MYMODULETYPE_H

namespace Module{
    template<typename T=void>
    constexpr bool true_type=true;

    template<typename T=void>
    constexpr bool false_type=false;
}

#endif