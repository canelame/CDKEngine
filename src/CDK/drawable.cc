#include "CDK/drawable.h"
struct Drawable::Data{
  std::shared_ptr<Geometry> drawable_geometry_ ;
	std::shared_ptr<Material> drawable_material_;
  std::shared_ptr<Material::MaterialSettings> material_settings_;

};



Drawable::Drawable(){
  data_ = new Data;
  data_->material_settings_ = std::make_shared<Material::MaterialSettings>();
}

std::shared_ptr<Material::MaterialSettings> Drawable::getMaterialSettings(){ return data_->material_settings_; }
void Drawable::setGeometry( std::shared_ptr<Geometry> geo){
	data_->drawable_geometry_=geo;
  
}
void Drawable::setMaterial( std::shared_ptr<Material>mat){
	data_->drawable_material_=mat;
}


std::shared_ptr<Geometry> Drawable::geometry(){ return data_->drawable_geometry_; }
std::shared_ptr<Material> Drawable::material(){ return data_->drawable_material_; }
void Drawable::setMaterialSettings(std::shared_ptr<Material::MaterialSettings>mat_s){
  data_->material_settings_ = mat_s;

}