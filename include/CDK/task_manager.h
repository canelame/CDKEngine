#ifndef __H_TASK__
#define __H_TASK__
#include <queue>
#include "types.h"
class Task{
	/**
	* @author Alejandro Canela Mendez 2015.
	* @brief Interface of Task.
	*/
public:
	/**
	* @brief Virtual methor, had to be reimplemented in each class that its derived of Task.
	*/
	Task();
  virtual void runTask()=0;
	virtual ~Task();
	bool getLocked();
	void lock();
	void unlock();
  void setId(int32 id);
  int getId();
   bool finished_=false;
private:
  int32 id_;
	mutable	bool is_locked_;

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
  UpdateDisplay(DisplayList *dl,std::shared_ptr<Node> n,Camera*cam);
	/**
	* @brief Execute the task
	*/
	void runTask();
  void loadNode(std::shared_ptr<Node>node );
private:
 std::shared_ptr<Node> nod_;
  Camera * cam_;
DisplayList* dl_;
};
#endif

#ifndef __H_READ_FILE_TASK__
#define __H_READ_FILE_TASK__
#include <memory>
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
	ReadFile(const char* file_name, std::shared_ptr<Material> m);
	/**
		@brief Execute the task.
	*/
	void ReadFile::runTask();
private:
  const char* name_;
  std::shared_ptr<Material> mat_;
   std::string data_;
};

#endif

#ifndef __H_READ_TEXTURE_TASK__
#define __H_READ_TEXTURE_TASK__
class ReadTexture : public Task{
public:
  /**
  * @brief Constructor of the task ReadFile
  * @param file_name The file to read.
  * @param out_file Returns the content of the file.
  */
  ReadTexture(std::shared_ptr<Texture> t,const char*file_name,const char*type);
  /**
  @brief Execute the task.
  */
  void runTask();

  ~ReadTexture(){};
private:
  std::shared_ptr<Texture> texture_;
  const char* name_;
   const char*type_;
};

#endif

#ifndef __H_TASK_MANAGER__
#define __H_TASK_MANAGER__

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
  typedef std::deque<TaskT_> TaskListT_;
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
  void waitTask(Task &t);
  unsigned int totalTasks();
  unsigned int runingTasks();
  std::vector<TaskT_> run_tasks_list_;
private:
	//Needed variables to manage the threads
	 void mainThreadLoop();
  std::mutex mutex_;
  std::condition_variable cond_variable_;
  bool stop_;
	int num_cores_;
	std::vector<std::thread> list_thread_;

	 TaskListT_ task_list_;

};


#endif

#ifndef __H_TASK_HANDLE__
#define __H_TASK_HANDLE__

class TaskHandle{


  int id_;

};

#endif