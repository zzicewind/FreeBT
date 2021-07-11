#pragma once
#include<iostream>
#include "obj/bDict.hpp"
namespace bencode{
class bdictPolicy{
  public:
  BOBJ_SPTR execute(std::istream & in);
};
}
