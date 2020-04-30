#ifndef PARSE_COMMENT_H
#define PARSE_COMMENT_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

namespace Module{
    namespace Internal{
        void addCommentInfos(std::map<size_t,size_t> & result_insertmap,const std::string & filedata,
                        std::string_view find_first_str,std::string_view find_end_str){

            auto first_commentpos = filedata.find(&find_first_str[0],0,find_first_str.size());
            auto end_commentpos = filedata.find(&find_end_str[0],first_commentpos + find_first_str.size(),find_end_str.size());

            while(first_commentpos != std::string::npos){
                
                if(end_commentpos == std::string::npos){
                    end_commentpos = filedata.size();
                }

                if(result_insertmap.find(first_commentpos) == result_insertmap.end()){
                    result_insertmap[first_commentpos] = end_commentpos;
                }else{
                    result_insertmap[first_commentpos] = std::max(result_insertmap[first_commentpos],end_commentpos);
                }

                first_commentpos = filedata.find(&find_first_str[0],end_commentpos + find_end_str.size(),find_first_str.size());
                end_commentpos = filedata.find(&find_end_str[0],first_commentpos + find_first_str.size(),find_end_str.size());
            }
        }


        void getCommentPosList(std::vector<std::pair<size_t,size_t>> & result_insertbox,const std::map<size_t,size_t> & position_map,const std::string & filedata){
            auto now_firstpos = position_map.begin()->first;
            auto now_endpos = position_map.begin()->second; 

            auto itr = position_map.begin();
            for(++itr;itr != position_map.end();++itr){
                if(now_endpos < itr->first){
                    result_insertbox.emplace_back(now_firstpos,now_endpos);
                    now_firstpos = itr->first;
                    now_endpos = itr->second;
                }else{
                    now_endpos = std::max(itr->second,now_endpos);
                }
            }
            if(now_firstpos >= now_endpos){
                now_endpos = filedata.size();
            }

            result_insertbox.emplace_back(now_firstpos,now_endpos);
        }
    }


    void GetIgnorePosList(const std::string & filedata,const std::vector<std::pair<std::string_view,std::string_view>> & ignorepos,
            std::vector<std::pair<std::size_t,std::size_t>> & result){

        std::map<size_t,size_t> commentpos_tree;
        
        for(auto &i : ignorepos){
            Internal::addCommentInfos(commentpos_tree,filedata,i.first,i.second);
        }
        Internal::getCommentPosList(result,commentpos_tree,filedata);

    }
}

#endif