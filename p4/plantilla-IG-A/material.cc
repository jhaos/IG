#include "material.h"

Material::Material(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo){
    this->ambiental = ambiental;
    this->difusa = difusa;
    this->especular = especular;
    this->brillo = brillo;
}

void Material::activar(){
    glEnable(GL_LIGHTING);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambiental);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
        glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
        glMaterialf(GL_FRONT, GL_SHININESS, brillo);
}

void Material::desactivar(){
    glDisable(GL_LIGHTING);
}