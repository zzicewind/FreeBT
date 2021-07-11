#pragma once
#include<iostream>
#include "obj/bStr.hpp"
namespace bencode{
class bstrPolicy{
  public:
  BOBJ_SPTR execute(std::istream & in);
};
}
