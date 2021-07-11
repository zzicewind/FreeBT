#pragma once
#include "bObj.hpp"
#include <unordered_map>
namespace bencode {

class bDict:public bObj{
  using value_type= bTrait<bDict>::value_type;
  public:
  BTYPE GetType() const override
  {
    return BTYPE::B_DICT;
  }
  const BOBJ_SPTR& at(const std::string &key) const
  {
    auto* pv = std::any_cast<bTrait<bDict>::value_type>(&val_);
    return (*pv).at(key);
  }
  BOBJ_SPTR& operator[](const std::string &key)
  {
    auto* pv = std::any_cast<bTrait<bDict>::value_type>(&val_);
    return (*pv)[key];
  }
  operator value_type(){
    return std::any_cast<value_type>(val_);
  }

};

template<> struct bTrait<bDict>{
  using  value_type=std::unordered_map<std::string,BOBJ_SPTR>;
  static constexpr const char first='d';
  static constexpr const char last='e';
};

}
