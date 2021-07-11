#pragma once
#include "bencodeExcept.hpp"
namespace bencode{
enum class FormatError{
  bIntNegZero,// "-0"
  bIntprefixZero,//"00,01"
  bIntnoneDigitChar,
  bIntOverFlow,
  bstrLenNoneDigitChar,
  bstrLenOverFlow,
  blistUnknowObj,
  bdictInvalidKey,
  bdicDupKey,
  bdictInvalidVal,
  cutoffByEof,
};
const char*[] errorMsg={
  "Bint error For Negtive 0",           //bIntNegZero
  "Bint error For prefix 0",            //bIntprefixZero
  "Bint error For none digit char",     //bIntnoneDigitChar
  "Bint error For int64 overflow",      //bIntOverFlow
  "Bstr error For none digit char in Len", //bstrLenNoneDigitChar,
  "Bstr error For int64 len overflow",    // bstrLenOverFlow
  "Blist error For unknow object",        //blistUnknowObj
  "Bdict error For invalid key",          //bdictInvalidKey
  "Bdict error For duplicate key",          //bdictDupKey
  "Bdict error For invalid val",        // bdictInvalidVal
  "Boject cut off by EOF"               //cutoffByEof
};
class bencodeFormatExcept:public bencodeExcept{
  public:
  bencodeFormatExcept(FormatError err,
                      const char* file,
                      int line,
                      const char* func,
                      int64_t charPS):
      bencodeExcept(errorMsg[size_t(err)],file,line,func),
      charPS_{charPS}{
  }
  int64_t ErrorCharPosInStream(){
    return charPS_;
  }
 private:
  int64_t charPS_;
};

#define B_FORMAT_EXCEP(formatError,instream) \
bencodeFormatExcept(formatError,\
                                __FILE__,\
                                __LINE__,\
                                __func__,\
                    instream.tellg())




#define B_FORMAT_EXCEP_PS(formatError,pos) \
bencodeFormatExcept(formatError,\
                                __FILE__,\
                                __LINE__,\
                                __func__,\
                    pos)

}
