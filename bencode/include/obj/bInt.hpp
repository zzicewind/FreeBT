#include <sys/_types/_int64_t.h>
#include "bObj.hpp"
#include <optional>
#include <string>
namespace bencode {
class bInt:public bObj{
  using value_type= bTrait<bInt>::value_type;
 public:
  BTYPE GetType() const override
  {
    return BTYPE::B_INT;
  }
  operator value_type(){
    return std::any_cast<value_type>(val_);
  }
};
template<> struct bTrait<bInt>{
   using  value_type= int64_t;
   static constexpr const char first='i';
   static constexpr const char last='e';
};
}
