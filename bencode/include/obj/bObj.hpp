#pragma once
#include <any>
#include <memory>
#include <string>
namespace bencode{
enum class BTYPE{
  B_INT,
  B_STR,
  B_LIST,
  B_DICT,
  B_UNKNOW
};

template<typename  T>
struct bTrait{
  using value_type=std::string;
  static constexpr const char first='0';
  static constexpr const char last='0';
};

class noCopy
{
   noCopy(const noCopy&) = delete;
   noCopy& operator=(const noCopy&) = delete;
};




class bObj{
 public:
  virtual ~bObj()=default;
  virtual BTYPE GetType() const =0;
  const std::any&  GetVal() const{
    return val_;
  }
  std::any&  GetVal() {
    return val_;
  }
  void SetVal(std::any &&in){
    val_=std::move(in);
  }
  void SetVal(const std::any& in){
    val_=in;
  }
  void SetPos(int pos){
    pos_=pos;
  }
  void SetLen(int len){
    len_=len;
  }
  int GetPos() const{
    return pos_;
  }
  int GetLen() const{
    return len_;
  }
 private:
  int pos_{-1};
  int len_{-1};
 protected:
  std::any val_;
};


using BOBJ_SPTR= std::shared_ptr<bObj>;
}
