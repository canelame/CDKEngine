#ifndef __H_TASK_MANAGER__
#define __H_TASK_MANAGER__
#include "display_list.h"
#include "geometry.h"
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
class Task{
public:
  virtual void runTask()=0;

private:
};

class UpdateDisplay : public Task{
public:
  void runTask(DisplayList &dl){
    
  }
};

class TaskManager{
public:
  void addTask(Task &t){
    task_list_->push_back(std::move(t));
  }

private:
  std::unique_ptr<std::vector<Task>> task_list_;
};


#endif