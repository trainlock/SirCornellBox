#include "Material.h"

Material::Material(){}

Material::Material(ColorDbl _color, float _p, float _refIdx){
	this->color = _color;
	this->p = _p;
	this->refractionIndex = _refIdx;
}


Material::~Material(){}

ColorDbl Material::getColor(){
	return this->color;
}

float Material::getBRDF(){
	return this->p / M_PI;
}

float Material::getRefraction(){
	return this->refractionIndex;
}
