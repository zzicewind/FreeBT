#pragma once
#include "obj/bObj.hpp"
#include <utility>
namespace bencode{
template<typename parserPolicy>
class parser:private parserPolicy
{
 public:
  template<typename T>
  BOBJ_SPTR run(T &&in){
    return execute(std::forward<T>(in));
  }
 private:
  using parserPolicy::execute;
};
}
