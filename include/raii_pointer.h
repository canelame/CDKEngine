/**
* @author Alejandro Canela Mendez. 2015
* Basic RAII Pattern implementation.
*/
#ifndef __H_RAII_P__
#define __H_RAII_P__
#include <stdio.h>

template <class T>class raii_pointer{
public:

  explicit raii_pointer<T>(T *t = NULL){
    raii_p_ = t; 
  
  }

  T* get()const{ return raii_p_; }
  T* alloc(){ 
    reset(new T);
    if (raii_p_)raii_p_->addRef();
    return raii_p_;
  }
  void reset(T *t = NULL){ delete raii_p_; raii_p_ = t;}

  ~raii_pointer(){ 
    

    raii_p_->rmRef();
  
    raii_p_ = NULL; printf("Destructor called\n");
 
  }

  T *operator->(){ return raii_p_; }
  T &operator*(){ return *raii_p_; }
  raii_pointer &operator=(const raii_pointer &p) {
    if (raii_p_ != p.raii_p_){
      T* temp_p = raii_p_;
      raii_p_ = p.raii_p_;
      temp_p.rmRef();
    }
    return *this;
  }
private:
  T* raii_p_;
 // Ref_Counter *ref_count_;

  raii_pointer(const raii_pointer &)=delete;
 

};

#endif