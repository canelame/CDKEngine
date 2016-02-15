#ifndef __H_GUI_INTERFACE__
#define __H_GUI_INTERFACE__
/**
@author Alejandro Canela Mendez
GUI interface for the engine
*/
#include <memory>
#include "node.h"
#include "ImGui\imgui.h"
class GuInterface{

public:
  GuInterface();
  /**
  @brief Initialize GUi
  */
  void init();
  /**
  @brief update();
  */
  void update();
  /**
  @brief Draw Scene node
  */
  void draw(std::shared_ptr<Node> node);
  /**
  */
  static GuInterface& instance();
private:
  std::vector<bool> selected_nodes_;
  static GuInterface *instance_;
  bool node_parent_selected = false;
  /**
  */
  void nodePanel( Node &node);
  void mainMenu();
  void loadNode(Node &node);
  void transformPanel(Node &node);  
  std::shared_ptr<Node> select_node_;
  /**
  
  */
  void setStyle(ImGuiStyle &col_element);
};
#endif
