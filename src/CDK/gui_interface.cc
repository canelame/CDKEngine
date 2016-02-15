#include "CDK/gui_interface.h"

#include "ImGui\imgui_impl_glfw_gl3.h"

GuInterface* GuInterface::instance_ = NULL;

GuInterface::GuInterface(){}
/**
*/
GuInterface& GuInterface::instance(){
  if (instance_ == NULL)instance_ = new GuInterface();
  return *instance_;
}
void GuInterface::init(){}
void GuInterface::update(){
  ImGui_ImplGlfwGL3_NewFrame();
}

void GuInterface::draw(std::shared_ptr<Node>node){
  mainMenu();
  nodePanel(*node.get());

  if (select_node_ != nullptr){
    transformPanel(*select_node_.get());
  }
    
  
     

  ImGui::Render();
}
void GuInterface::mainMenu(){
 
  ImGuiStyle &style = ImGui::GetStyle();
  setStyle(style);
  if (ImGui::BeginMainMenuBar()){
    if (ImGui::BeginMenu("Menu")){
      if (ImGui::MenuItem("Open")){
        printf("Menu open\n");
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

}
void GuInterface::setStyle(ImGuiStyle &elemnt){

  elemnt.FramePadding = ImVec2(0.0f, 15.0f);
  //elemnt.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2, 1.0, 0.0, 0.8);
  elemnt.Colors[0] = ImVec4(1.0, 1.0, 0.0, 1.0);
  ImFontAtlas* atlas = ImGui::GetIO().Fonts;
  ImFont * font = atlas->Fonts[0];
  font->Scale = 1.2;
}
void GuInterface::nodePanel( Node &node){
  const int total_nodes = node.size();
  ImGui::Begin("Hirarchy", 0, 0);
  ImGui::SetWindowPos(ImVec2(0.0, 50.0));
  ImGuiStyle &style = ImGui::GetStyle();
  style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0, 1.0, 0.0, 1.0);
  
  if (ImGui::TreeNode("Scene")){
    loadNode(node);
    ImGui::TreePop();
  }
  

  ImGui::End();

}
  /*ImGui::SetWindowSize(ImVec2(200, 100), 0);

  ImGui::bar
  ImGui::Begin("Window");
  ImGui::Text("Camera Mocement");
 // ImGui::SliderFloat3("Position cam", position, 0, 100);
 // ImGui::SliderFloat3("Scale object", size, 0, 100);
 // ImGui::SliderFloat3("Rotation object", rotation, 0, 100);
  ImGui::End();
}*/


void GuInterface::loadNode(Node &node){

  if (node.getParent() == nullptr){
    if (ImGui::TreeNode(node.getName())){

      for (int i = 0; i < node.size(); i++){


        if (ImGui::Selectable(node.childAt(i).get()->getName())){
          select_node_ = std::make_shared<Node>(*node.childAt(i).get());
        }
        else{

        }

      }
      ImGui::TreePop();
    }
  }
  for (int i = 0; i < node.size(); i++){
        loadNode(*node.childAt(i).get());
      
   // ImGui::TreePop();
  }

}

void GuInterface::transformPanel(Node &node){

    ImGui::Begin("TRANSFORM:");
    ImGui::Text(node.getName());
    ImGui::SetWindowPos(ImVec2(975, 50.0));
    //Position
    vec3 pos_node = node.position();
    float n_pos[3] = { pos_node.x, pos_node.y, pos_node.z };
    ImGui::SliderFloat3("Position:", n_pos, 0.0, 1000.0, "%1.0f");
    node.setPosition(vec3(n_pos[0], n_pos[1], n_pos[2]));
    //Scale
    vec3 sclae_node = node.scale();
    float n_scale[3] = { sclae_node.x, sclae_node.y, sclae_node.z };
    ImGui::SliderFloat3("Scale:", n_scale, 0.0, 1000.0, "%1.0f");
    node.setScale(vec3(n_scale[0], n_scale[1], n_scale[2]));
    ImGui::End();
  
}