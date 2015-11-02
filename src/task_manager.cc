#include "task_manager.h"

std::mutex TaskManager::mutex_;
std::condition_variable TaskManager::cond_variable_;
bool stop_;
bool TaskManager::stop_;
TaskManager::TaskListT_ TaskManager::task_list_;

  void TaskManager::mainThreadLoop(){
   while (!stop_)
   {
     std::unique_lock<std::mutex> lck(TaskManager::mutex_);
     cond_variable_.wait(lck);
     if (TaskManager::task_list_.size()!=0){
       //task_list_.begin()->get()->runTask();
       printf("Running Task update display list");
       task_list_.pop_back();
       cond_variable_.notify_all();
     }

   }
}

   void TaskManager::init(){
    
     num_cores_ = std::thread::hardware_concurrency();
    printf("Num Cores:%d", num_cores_);
    for (int i = 0; i < num_cores_; i++){
      list_thread_.push_back(std::thread(TaskManager::mainThreadLoop));

     
    }
  }