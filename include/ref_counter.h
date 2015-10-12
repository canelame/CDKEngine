#ifndef __H_REF_COUNTER__
#define __H_REF_COUNTER__

class Ref_Counter{
public:
  Ref_Counter(){};
  void addRef();
  int rmRef();


private:
  unsigned int count_ref_=0;
  Ref_Counter(const Ref_Counter&);
  Ref_Counter& operator=(const Ref_Counter&);
};


inline void Ref_Counter::addRef(){
  ++count_ref_;
}

inline int Ref_Counter::rmRef(){
  --count_ref_;
  return count_ref_;
//TODO asserts;

}
#endif