#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace Module{

    class Argparser{
    public:
        using argstr_t = std::string;
        using argview_t = std::string_view;
        using argtype_t = std::vector<argstr_t>;

        std::vector<argtype_t> arglist;

        Argparser(){}
        Argparser(int argc, char ** argv){ParseArg(argc, argv);}
        virtual ~Argparser(){}

        virtual bool ParseArg(int argc, char ** argv){
            argtype_t nowarg;
            for(int i=0;i<argc;++i){
                argview_t tgt(argv[i]);
                auto foundpos = tgt.find("-");

                if(foundpos == 0 && 0 < nowarg.size()){
                    arglist.emplace_back(std::move(nowarg));
                    nowarg = argtype_t();
                }

                nowarg.emplace_back(tgt);

                if(foundpos != 0){
                    arglist.emplace_back(std::move(nowarg));
                    nowarg = argtype_t();
                }
            }

            if(0 < nowarg.size()){
                arglist.emplace_back(std::move(nowarg));
            }

            return true;
        }

    };
}

#endif