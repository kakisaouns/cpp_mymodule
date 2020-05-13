#ifndef PARSE_MULTISEARCH_H
#define PARSE_MULTISEARCH_H

#include <cstdint>
#include <array>

namespace Module{
    namespace Internal{

        bool CheckStrColision(){
            static constexpr std::array<std::uint64_t,2> mod_val = {10e+18+7,10e+18+11};
            static constexpr std::array<std::uint64_t,2> mul_val = {17,7213};


        }
    }

    void FindMultiSearch(std::vector<std::vector<std::size_t>> & ret,const std::string & finddata,const std::vector<std::string_view> findstr){
        
    }
}

#endif