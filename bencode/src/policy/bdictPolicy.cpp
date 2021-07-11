#include "policy/bdictPolicy.hpp"
#include <any>
#include <istream>
#include <memory>
#include "except/bencodeFormatExcept.hpp"
#include "obj/bDict.hpp"
#include "obj/bObj.hpp"
#include "policy/bintPolicy.hpp"
#include "policy/blistPolicy.hpp"
#include "policy/bstrPolicy.hpp"
namespace bencode{
BOBJ_SPTR bdictPolicy::execute(std::istream &in){
  if(in.peek()!=bTrait<bDict>::first)
    return nullptr;
  int ps=in.tellg();
  BOBJ_SPTR res=std::make_shared<bDict>();
  bstrPolicy bsp;
  bintPolicy bip;
  blistPolicy blp;
  bTrait<bDict>::value_type dictData;
  while(!in.eof() && in.peek()!=bTrait<bDict>::last){
    int keyps=in.tellg();
    auto keyobj = bsp.execute(in);
    if(!keyobj)
      throw B_FORMAT_EXCEP_PS(FormatError::bdictInvalidKey, keyps);
    std::string key = std::any_cast<std::string>(keyobj->GetVal());
    if(dictData.count(key))
      throw B_FORMAT_EXCEP_PS(FormatError::bdicDupKey, keyps);
    int valps=in.tellg();
    auto valObj = bip.execute(in);
    if(valObj)
    {
      dictData[key]=valObj;
      continue;
    }
    valObj= blp.execute(in);
    if(valObj)
    {
      dictData[key]=valObj;
      continue;
    }
    valObj=execute(in);
    if(valObj)
    {
      dictData[key]=valObj;
      continue;
    }
    valObj=bsp.execute(in);
    if(valObj)
    {
      dictData[key]=valObj;
      continue;
    }
    throw B_FORMAT_EXCEP_PS(FormatError::bdictInvalidVal, valps);
  }
  if(in.eof())
    throw B_FORMAT_EXCEP(FormatError::cutoffByEof, in);
  in.get();
  int lastps=in.tellg();
  res->SetPos(ps);
  res->SetLen(lastps-ps+1);
  res->SetVal(std::any(dictData));
  return res;
}
}
