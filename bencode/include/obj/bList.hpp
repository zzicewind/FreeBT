#pragma once
#include "bObj.hpp"
#include <vector>
namespace bencode{
class bList :public bObj{
  using value_type =  bTrait<bList>::value_type;
 public:
  BTYPE GetType() const override
  {
    return BTYPE::B_LIST;
  }
  operator value_type(){
    return std::any_cast<value_type>(val_);
  };
};



template<> struct bTrait<bList>{
  using  value_type=std::vector<BOBJ_SPTR>;
  static constexpr const char first='l';
  static constexpr const char last='e';
};
}
