#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H

#include <cstdio>
#include <string_view>

namespace Module{

    template<int printlevel>
    class PrintDebugLog{
        public:
            constexpr PrintDebugLog(){}

            template<int level = 0,typename... Args>
            void log_printf(const char * format,const Args&... args){
                if constexpr(printlevel <= level){
                    std::printf(format,args...);
                }
            }

            template<int level = 0>
            void log_puts(const char * format){
                if constexpr(printlevel <= level){
                    std::puts(format);
                }
            }
    };
}

#define PDEB_INIT(printlevel) namespace Module::DebugPrint{ static PrintDebugLog<printlevel> printer;}
#define logprintf Module::DebugPrint::printer.log_printf
#define logputs Module::DebugPrint::printer.log_puts

#endif