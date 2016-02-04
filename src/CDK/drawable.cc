#include "CDK/drawable.h"
struct Drawable::Data{
	std::shared_ptr<Geometry> drawable_geometry_;
	std::shared_ptr<Material> drawable_material_;

};



Drawable::Drawable(){
	data_ = new Data;

}

void Drawable::setGeometry(std::shared_ptr<Geometry>geo){
	data_->drawable_geometry_=geo;
  
}
void Drawable::setMaterial(std::shared_ptr<Material>mat){
	data_->drawable_material_=mat;
}


std::shared_ptr<Geometry> Drawable::geometry(){ return data_->drawable_geometry_; }
std::shared_ptr<Material> Drawable::material(){ return data_->drawable_material_; }