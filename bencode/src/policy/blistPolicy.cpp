#include "policy/blistPolicy.hpp"
#include <string_view>
#include "except/bencodeFormatExcept.hpp"
#include "obj/bList.hpp"
#include "obj/bObj.hpp"
#include "policy/bintPolicy.hpp"
#include "policy/bstrPolicy.hpp"
#include "policy/bdictPolicy.hpp"
#include <vector>
namespace bencode{
BOBJ_SPTR blistPolicy::execute(std::istream & in){
  if(in.peek()!=bTrait<bList>::first){
    return nullptr;
  }
  BOBJ_SPTR res= std::make_shared<bList>();
  int ps=in.tellg();
  std::vector<BOBJ_SPTR> val;
  bintPolicy bip;
  bstrPolicy bsp;
  bdictPolicy bdp;
  while(!in.eof() && in.peek()!=bTrait<bList>::last){
    auto cobj=bip.execute(in);
    if(cobj){
      var.push_back(std::move(obj));
      continue;
    }
    cobj=bdp.execute(in);
    if(cobj){
      var.push_back(std::move(obj));
      continue;
    }
    cobj=execute(in);
    if(cobj){
      var.push_back(std::move(obj));
      continue;
    }
    cobj=bsp.execute(in);
    if(cobj){
      var.push_back(std::move(obj));
      continue;
    }
    throw B_FORMAT_EXCEP(FormatError::blistUnknowObj, in);
  }
  if(in.eof()){
    throw B_FORMAT_EXCEP(FormatError::cutoffByEof, in);
  }
  in.get();
  int lastps=in.tellg();
  res->SetPos(ps);
  res->SetLen(lastps-ps+1);
  res->SetVal(std::any(val));
  return res;
}
}
