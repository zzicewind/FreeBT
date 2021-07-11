#include "policy/bintPolicy.hpp"
#include <cctype>
#include "except/bencodeFormatExcept.hpp"
namespace bencode{
BOBJ_SPTR bintPolicy::execute(std::istream & in){
  if(in.peek()!=bTrait<bInt>::first){
    return nullptr;
  }
  auto ps= in.tellg();
  BOBJ_SPTR res= std::make_shared<bInt>{};
  std::string intStr;
  bool isNeg=false;
  if(in.peek()=='-'){
    isNeg=true;
    intStr+=in.get();
  }
  if(in.peek()=='0'){
    if(isNeg)
      throw B_FORMAT_EXCEP(FormatError::bIntNegZero,in);
    intStr+=in.get();
    if(in.peek()!=bTrait<bInt>::last)
      throw B_FORMAT_EXCEP(FormatError::bIntprefixZero,in);
    in.get();
    res->SetPos(ps);
    res->SetLen(in.tellg()-ps+1);
    res->SetVal(std::any(int64_t(0)));
    return res;
  }
  while(!in.eof() && in.peek()!=bTrait<bInt>::last){
    char c = in.get();
    if(!std::isdigit(c))
      throw B_FORMAT_EXCEP(FormatError::bIntnoneDigitChar,in);
    intStr+=c;
  }
  if(in.eof())
    throw  B_FORMAT_EXCEP(FormatError::cutoffByEof,in);
  in.get();
  try{
  int64_t val=std::stoll(intStr);
  res->SetPos(ps);
  res->SetLen(in.tellg()-ps+1);
  res->SetVal(std::any(val));
  }catch(std::out_of_range &e){
    throw B_FORMAT_EXCEP(FormatError::bIntOverFlow,in);
  }
  return res;
}
}
