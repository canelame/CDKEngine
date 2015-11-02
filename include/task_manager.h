#ifndef __H_TASK_MANAGER__
#define __H_TASK_MANAGER__
#include "display_list.h"
#include "geometry.h"
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
class Task{
public:

  virtual void runTask()const=0;

  
private:
  int id_;


 

};
class UpdateDisplay : public Task {
public:
  UpdateDisplay(std::shared_ptr<DisplayList> &dl){
    dl_ = dl;
  }
  void runTask()const{
    dl_->update();
  }
  std::shared_ptr<DisplayList> dl_;
};


class TaskManager {
  typedef std::shared_ptr<Task> TaskT_;
   typedef std::vector<TaskT_> TaskListT_;
public:

  static void mainThreadLoop();
    void addTask(TaskT_ t){
      task_list_.push_back(t);
      cond_variable_.notify_all();
  }
    void execute(){
      for (int i = 0; i < num_cores_; i++){
        list_thread_[i].join();
      }
    }
  void init();
  static std::mutex mutex_;
  static  std::condition_variable cond_variable_;
  static bool stop_;
    std::vector<std::thread> list_thread_;
    int num_cores_;
    static TaskListT_ task_list_;
private:
  

};


#endif