#include "Material.h"

Material::Material(){}

Material::Material(ColorDbl _color, float _p, float _refIdx, reflectionType _type) {
	this->color = _color;
	this->p = _p;
	this->refractionIndex = _refIdx;
	this->type = _type;
	this->emission = 0.0f;
}

Material::Material(ColorDbl _color, float _p, float _refIdx, reflectionType _type, float _emission){
	this->color = _color;
	this->p = _p;
	this->refractionIndex = _refIdx;
	this->type = _type;
	this->emission = _emission;
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

reflectionType Material::getType()
{
	return type;
}
