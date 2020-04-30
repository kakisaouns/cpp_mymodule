#ifndef RESULT_H
#define RESULT_H

#include <variant>
#include <type_traits>

#include "MyModuleType.h"

namespace Module{
    template<typename TrueType,typename FalseType>
    class Result{
        public:
            constexpr Result(){}

            constexpr Result(TrueType && true_value) : value(std::forward<TrueType>(true_value)){}
            constexpr Result(FalseType && false_value) : value(std::forward<TrueType>(false_value)){}

            operator bool() const noexcept{
                return std::holds_alternative<TrueType>();
            }

            //variantを使う限りはreferenceタイプは防いでくれるっぽい
            std::remove_reference_t<TrueType> & GetTrue(){
                return std::get<TrueType>(value);
            }

            std::remove_reference_t<FalseType> & GetFalse(){
                return std::get<FalseType>(value);
            }

            template<typename T=TrueType,std::enable_if_t<!std::is_lvalue_reference_v<T>,void *>v=nullptr>
            TrueType && GetTrue_Move(){
                decltype(auto) ret = std::move(std::get<TrueType>(value));
                value = blank();
                return ret;
            }

            template<typename T=FalseType,std::enable_if_t<!std::is_lvalue_reference_v<T>,void *>v=nullptr>
            FalseType && GetFalse_Move(){
                decltype(auto) ret = std::move(std::get<FalseType>(value));
                value = blank();
                return ret;
            }

            template<typename T=TrueType,std::enable_if_t<std::is_lvalue_reference_v<T>,void *>v=nullptr>
            void GetTrue_Move(){
                static_assert(false_type<decltype(v)>,"[Module::Result]Error.Can't move \"TrueType\"");
            }
            
            template<ttypename T=FalseType,std::enable_if_t<std::is_lvalue_reference_v<T>,void *>v=nullptr>
            void GetFalse_Move(){
                static_assert(false_type<decltype(v)>,"[Module::Result]Error.Can't move \"FalseType\"");
            }

        private:
            struct blank{};
            std::variant<TrueType,FalseType,blank> value;

            void CheckCollisionType(){
                if constexpr(std::is_same_v<TrueType,FalseType>){
                    static_assert(false_type<TrueType>,"[Moudle::Result]Error. type collision in \"TrueType\" and \"FalseType\"");
                }
            }
    };
}

#endif