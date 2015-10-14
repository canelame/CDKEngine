#ifndef __H_REF_COUNTER__
#define __H_REF_COUNTER__
/**
* @author Alejandro Canela
* @brief This class is inherited from all clases that represents any kind of resource.
* Example: Geometry, texture, material, etc...
*/
class Ref_Counter{
public:
  Ref_Counter(){};
  void addRef();
  void rmRef();


private:
  unsigned int count_ref_=0;
  Ref_Counter(const Ref_Counter&);
  Ref_Counter& operator=(const Ref_Counter&);
protected:
  virtual ~Ref_Counter(){};
};


inline void Ref_Counter::addRef(){
  ++count_ref_;
}

inline void Ref_Counter::rmRef(){
  --count_ref_;
  int temp_c = count_ref_;
  if (count_ref_ == 0){
    delete this;

  }
 
//TODO asserts;

}
#endif