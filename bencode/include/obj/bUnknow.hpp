#pragma once
#include "bObj.hpp"

class bUnknow:public bObj{
  public:
  BTYPE GetType() const override
  {
    return BTYPE::B_UNKNOW;
  }
};
