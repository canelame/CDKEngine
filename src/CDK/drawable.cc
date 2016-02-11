#include "CDK/drawable.h"
struct Drawable::Data{
	std::shared_ptr<Geometry> drawable_geometry_;
	std::shared_ptr<Material> drawable_material_;

};



Drawable::Drawable(){


}

void Drawable::setGeometry(const Geometry&geo){
	data_->drawable_geometry_=std::make_shared<Geometry>(geo);
  
}
void Drawable::setMaterial(const Material&mat){
	data_->drawable_material_=std::make_shared<Material>(mat);
}


std::shared_ptr<Geometry> Drawable::geometry(){ return data_->drawable_geometry_; }
std::shared_ptr<Material> Drawable::material(){ return data_->drawable_material_; }