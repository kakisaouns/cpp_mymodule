#ifndef FCTRL_H
#define FCTRL_H

#include <vector>
#include <fstream>

namespace Module{
    template<typename str_type>
    bool ReadFile(std::vector<char> & data,const str_type & filepath){
        std::ifstream ifs(filepath);
        if(!ifs){return false;}
        
        ifs.seekg(0,std::ios_base::end);
        data.resize(ifs.tellg());
        
        ifs.seekg(0,std::ios_base::beg);
        ifs.read(&*data.begin(),data.size());

        return true;
    }

    template<typename str_type>
    bool WriteFile(const std::vector<char> & data,const str_type & str,std::ios_base::openmode mode = std::ios_base::binary){
        std::ofstream ofs(str,mode);
        if(!ofs){return false;}

        ofs.write(&*data.begin(),data.size());
        return true;
    }

}
#endif