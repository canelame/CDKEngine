#include "CDK/gui_interface.h"
#include "CDK/light.h"
#include "ImGui\imgui_impl_glfw_gl3.h"

GuInterface* GuInterface::instance_ = NULL;

GuInterface::GuInterface(){
  for (int i = 0; i < 3; i++){
    n_amb_light[i] = 0.0f;
    n_diff_light[i] = 0.0f;
    n_pos_light[i] = 0.0f;
    n_spec_light[i] = 0.0f;
  }
}
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
  mainMenu(*node.get());
  nodePanel(*node.get());

  if (select_node_ != nullptr){
    transformPanel(*select_node_.get());
  }
  ImGui::Render();
}

static bool show_menu_addLight = false;
void GuInterface::mainMenu(Node &node){
 
  ImGuiStyle &style = ImGui::GetStyle();
  setStyle(style);
  if (ImGui::BeginMainMenuBar()){
    if (ImGui::BeginMenu("Menu")){
      if (ImGui::MenuItem("Open")){
        printf("Menu open\n");
      }
      ImGui::EndMenu();
    }
    
    if (ImGui::MenuItem("Add Light")){
      show_menu_addLight = true;

    }

    ImGui::EndMainMenuBar();
  }
  if (show_menu_addLight){
    addLight(node);
  }
}
void GuInterface::setStyle(ImGuiStyle &elemnt){

 // elemnt.FramePadding = ImVec2(0.0f, 15.0f);
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
void GuInterface::addLight(Node &node){
  
  
  int current_item = 0;
  const char*items[] = { "Directional Light","Point Light" };
  bool exit = false;

    ImGui::Begin("NewLight");
  //ImGui::SetWindowSize(ImVec2(300, 300));
  ImGui::Text("Light position");
  ImGui::InputFloat3("", n_pos_light);
  ImGui::Text("Light diffuse");
  ImGui::ColorEdit3("", n_diff_light);
  ImGui::Text("Light specular");
  ImGui::ColorEdit3("", n_spec_light);
  ImGui::Text("Light ambient");
  ImGui::ColorEdit3("", n_amb_light);
  ImGui::ListBox("Light type", &current_item, items, 2,2);

  if (ImGui::Button("Accept")){
    std::shared_ptr<Light> t_light = std::make_shared<Light>();
    t_light->setPosition(vec3(n_pos_light[0], n_pos_light[1], n_pos_light[2]));
    t_light->setAmbientColor(vec3(n_amb_light[0], n_amb_light[1], n_amb_light[2]));
    t_light->setSpecularColor(vec3(n_spec_light[0], n_spec_light[1], n_spec_light[2]));
    t_light->setDifusseColor(vec3(n_diff_light[0], n_diff_light[1], n_diff_light[2]));
    t_light->setTypeLight(Light::T_DIRECTION_LIGHT);
    node.addLight(std::move(t_light));
    show_menu_addLight = false;
  }ImGui::SameLine();
  if (ImGui::Button("Exits")){
    show_menu_addLight = false;
  }
  ImGui::End();
  
  //t_light->setTypeLight
 // node.addLight()

}
void GuInterface::transformPanel(Node &node){

    ImGui::Begin("TRANSFORM:");
    ImGui::Text(node.getName());
    ImGui::SetWindowPos(ImVec2(600.0, 50.0));
    //Position
    vec3 pos_node = node.position();
    float n_pos[3] = { pos_node.x, pos_node.y, pos_node.z };
    if (ImGui::SliderFloat3("Position:", n_pos, 0.0, 1000.0, "%1.0f")){
      node.setPosition(vec3(n_pos[0], n_pos[1], n_pos[2]));
    }
    //Scale
    vec3 sclae_node = node.scale();
    float n_scale[3] = { sclae_node.x, sclae_node.y, sclae_node.z };
    if (ImGui::SliderFloat3("Scale:", n_scale, 0.0, 1000.0, "%1.0f")){
     node.setScale(vec3(n_scale[0], n_scale[1], n_scale[2]));
    }
    vec3 rotate_node = node.rotation();
    float n_rotate[3] = { rotate_node.x, rotate_node.y, rotate_node.z };
    if (ImGui::SliderFloat3("Rotation:", n_rotate, 0.0, 1000.0, "%1.0f")){
      node.setRotation(vec3(n_rotate[0], n_rotate[1], n_rotate[2]));
    }

    ImGui::End();
  
}