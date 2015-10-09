/**
* @author Alejandro Canela Mendez. 2015
* Basic RAII Pattern implementation.
*/
#ifndef __H_RAII_P__
#define __H_RAII_P__
#include <stdio.h>
#include "ref_counter.h"
template <class T>class raii_pointer{
public:

  explicit raii_pointer<T>(T *t = NULL){ raii_p_ = t; }

  T* get()const{ return raii_p_; }
  void alloc(){ 
    reset(new T);
    ref_count_ = new Ref_Counter(); 
    ref_count_->addRef(); 
  }
  void reset(T *t = NULL){ delete raii_p_; raii_p_ = t;}

  ~raii_pointer(){ 
    if (ref_count_->rmRef() == 0){
      delete ref_count_;
      delete raii_p_; printf("Destructor called\n");
    }
  }

  raii_pointer &operator->(){ return raii_p_; }

private:
  T* raii_p_;
  Ref_Counter *ref_count_;

  raii_pointer(const raii_pointer &)=delete;
  raii_pointer &operator=(const raii_pointer &)=delete;

};

#endif