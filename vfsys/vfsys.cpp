#include <iostream>
#include <fstream>
#include <string>

#if __cplusplus < 201703L
typedef const char * filepath_type;
#define basepath "vfile_"
#else
#include <string_view>
using filepath_type = std::string_view;
constexpr filepath_type basepath = "vfile_";
#endif

#define print_error(...) std::cerr << "[VFSYS_Error]:" <<  __VA_ARGS__ << std::endl;

static std::string respath(basepath);

extern "C"{

bool vfsys_read(const char * filepath,char * res,std::size_t size){
    std::ifstream ifs(respath + filepath);

    if(!ifs){
        print_error("failed file open");
        return false;
    }

    ifs.seekg(0,std::ios_base::end);
    std::size_t filesize = ifs.tellg();
    ifs.seekg(0,std::ios_base::beg);

    if(size < filesize){
        print_error("buffer size less than file size");
        return false;
    }

    ifs.read(res,filesize);

    if(!ifs){
        print_error("read error");
        return false;
    }
}

bool vfsys_write(const char * filepath,char * res,std::size_t size){
    std::ofstream ofs(respath + filepath);

    if(!ofs){
        print_error("failed file open");
        return false;
    }

    ofs.write(res,size);

    if(!ofs){
        print_error("write error");
        return false;
    }
}

}

