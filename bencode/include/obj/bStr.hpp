#pragma once
#include "bObj.hpp"
#include <string>
namespace becode{
class bStr:public bObj{
  using value_type = bTrait<bStr>::value_type;
  public:
  BTYPE GetType() const override
  {
    return BTYPE::B_STR;
  }

   operator value_type(){
     return std::any_cast<value_type>(val_);
  }
};
template<> struct bTrait<bStr>{
  using  value_type=std::string;
};
}
