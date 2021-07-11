#pragma once
#include<iostream>
#include "obj/bList.hpp"
namespace bencode{
class blistPolicy{
  public:
  BOBJ_SPTR execute(std::istream & in);
};
}
