#pragma once
#include<iostream>
#include "obj/bInt.hpp"
namespace bencode{
class bintPolicy{
  public:
  BOBJ_SPTR execute(std::istream & in);
};
}
