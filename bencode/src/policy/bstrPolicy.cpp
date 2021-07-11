#include "policy/bstrPolicy.hpp"
#include <cctype>
#include <stdexcept>
#include "except/bencodeFormatExcept.hpp"
#include "obj/bObj.hpp"
namespace bencode{
BOBJ_SPTR bstrPolicy::execute(std::istream &in){
  if(!std::isdigit(in.peek()))
    return nullptr;
  std::string lenStr;
  int ps=in.tellg();
  while(!in.eof()&&in.peek()!=':'){
    char c=in.get();
    if(!std::isdigit(c))
      throw B_FORMAT_EXCEP(FormatError::bstrLenNoneDigitChar, in);
    lenStr+=c;
  }
  int len=0;
  try{
    len=std::stoll(lenStr);
  }catch(std::out_of_range &e){
    throw B_FORMAT_EXCEP(FormatError::bstrLenOverFlow, in);
  }
  BOBJ_SPTR res=std::make_shared<bStr>();
  std::string val;
  val.resize(len);
  while(!in.eof() && len){
    char c=in.get();
    val+=c;
    --len;
  }
  res->SetVal(std::any{val});
  res->SetPos(ps);
  int lastps=in.tellg();
  res->SetLen(lastps-ps+1);
  return res;
}
}
