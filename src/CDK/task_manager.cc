#include "CDK/task_manager.h"
//DISPLAY_LIST IMPLEMENTATION

std::mutex TaskManager::mutex_;
std::condition_variable TaskManager::cond_variable_;
bool stop_;
bool TaskManager::stop_;
TaskManager::TaskListT_ TaskManager::task_list_;

void TaskManager::mainThreadLoop(){
	while (true)
	{
		std::unique_lock<std::mutex> lck(TaskManager::mutex_);
    cond_variable_.wait(lck,[&]() {
      return !(task_list_.size() == 0 && !stop_); });
  
		
		std::shared_ptr<Task> t =task_list_.front();
    task_list_.erase(task_list_.begin());
    t->runTask();
    if(!task_list_.empty())printf("Task finished\n");

   }
}

void TaskManager::init(){

	num_cores_ = std::thread::hardware_concurrency();
	for (int i = 0; i < num_cores_;  i++){
		list_thread_.push_back(std::thread(TaskManager::mainThreadLoop));
	}

}

   void TaskManager::addTask(TaskT_ t){
	   std::unique_lock<std::mutex> lock(mutex_);
   
	   task_list_.push_back(t);
	   cond_variable_.notify_all();
   }

   TaskManager::~TaskManager(){
	   for (int i = 0; i < num_cores_; i++) {
		   list_thread_[i].join();
	   }
	   stop_ = true;
   }

	 ///////////////TASK IMPLEMENTATIONS//////////////////
	 /////////////////////////////////////////////////////

	 //UPDATE_DISPLAY_LIST_TASK
	 UpdateDisplay::UpdateDisplay(std::shared_ptr<DisplayList> &dl){
		 dl_ = dl;
	 }
	 void UpdateDisplay::runTask()const{
		 dl_->update();
	 }
	 

	 //READ_FILE_TASK
	 ReadFile::ReadFile(const char* file_name, std::string &out_file){
		 name_ = file_name;
		 runTask();
		 out_file = data_;
	 };
	 void ReadFile::runTask()const{
		 std::stringstream temp_vertex_data;
		 std::stringstream temp_fragment_data;
		 std::string line;
		 printf("Reading file task\n");
		 std::ifstream file_V(name_);
		 if (file_V.is_open()){
			 temp_vertex_data << file_V.rdbuf();
			 file_V.close();
			 line = temp_vertex_data.str();
			 data_ = line;
		 }


	 }

	 //OTHERS TASKS
	 //....