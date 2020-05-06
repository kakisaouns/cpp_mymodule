#ifndef FCTRL_H
#define FCTRL_H

#include <vector>
#include <fstream>
#include <filesystem>

namespace Module{
    template<typename str_type>
    bool ReadFile(std::vector<char> & result,const str_type & filepath){
        std::ifstream ifs(filepath);
        if(!ifs){return false;}
        
        ifs.seekg(0,std::ios_base::end);
        result.resize(ifs.tellg());
        
        ifs.seekg(0,std::ios_base::beg);
        ifs.read(&*result.begin(),result.size());

        return true;
    }

    template<typename str_type>
    bool WriteFile(const std::vector<char> & result,const str_type & filepath,std::ios_base::openmode mode = std::ios_base::binary){
        std::ofstream ofs(filepath,mode);
        if(!ofs){return false;}

        ofs.write(&*result.begin(),result.size());
        return true;
    }

    template<bool use_filesystem = true,typename dst_strtype,typename src_strtype>
    bool CopyFile(const dst_strtype & dst,const src_strtype & src){
        if constexpr(use_filesystem){
            std::filesystem::copy_file(dst,src,std::filesystem::copy_options::overwrite_existing);
        }else{
            std::vector<char> dstdata;
            if(!ReadFile(dstdata,dst)){
                return false;
            }
            if(!WriteFile(dstdata,src)){
                return false;
            }
        }
        return true;
    }

}
#endif