#ifndef __H_TASK__
#define __H_TASK__
class Task{
	/**
	* @author Alejandro Canela Mendez 2015.
	* @brief Interface of Task.
	*/
public:
	/**
	* @brief Virtual methor, had to be reimplemented in each class that its derived of Task.
	*/
  virtual void runTask()const=0;

private:
  int id_;
};
#endif 

#ifndef __H_UPDATE_LIST__
#define __H_UPDATE_LIST__
#include "display_list.h"
	/**
	* @author Alejandro Canela Mendez 2015.
	* @brief Create a task to update the dispay list.
	*
	*/
class UpdateDisplay : public Task {
public:
	/**
	*	@brief Constructor of the task UpdateDisplay
	* @param dl The display list to update
	*/
	UpdateDisplay(std::shared_ptr<DisplayList> &dl);
	/**
	* @brief Execute the task
	*/
	void runTask()const;
private:
  std::shared_ptr<DisplayList> dl_;
};
#endif

#ifndef __H_READ_FILE_TASK__
#define __H_READ_FILE_TASK__
	/**
	* 
	* @author Alejandro Canela Mendez 2015.
	* @brief Creates a task to read files
	*
	*/
class ReadFile : public Task{
public:
	/**
	* @brief Constructor of the task ReadFile
	* @param file_name The file to read.
	* @param out_file Returns the content of the file.
	*/
	ReadFile(const char* file_name, std::string &out_file);
	/**
		@brief Execute the task.
	*/
	void ReadFile::runTask()const;
private:
  const char* name_;
  mutable std::string data_;
};

#endif

#ifndef __H_TASK_MANAGER__
#define __H_TASK_MANAGER__
#include "display_list.h"
#include "geometry.h"
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
/**
* @author Alejandro Canela Mendez 2015.
* @brief Implemention of simple task manager, this is usefull for run several 
* process at same time.
* 
*/
class TaskManager {
	/* Redefinition of types for manage list of task*/
  typedef std::shared_ptr<Task> TaskT_;
  typedef std::vector<TaskT_> TaskListT_;
public:
	TaskManager() {};
	~TaskManager();
	/**
	* @brief Add task to the list.
	* @param t . The task to run.
	*/
  void addTask(TaskT_ t);
	/**
	* @brief Init threads, the number of threads is equal to processor cores.
	*/
  void init();

private:
	//Needed variables to manage the threads
	static void mainThreadLoop();
	static std::mutex mutex_;
	static  std::condition_variable cond_variable_;
	static bool stop_;
	int num_cores_;
	std::vector<std::thread> list_thread_;
	static TaskListT_ task_list_;
};


#endif