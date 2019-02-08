#include "luz.h"

luz::luz(GLenum indice, Tupla4f pos, Tupla4f amb,
        Tupla4f dif, Tupla4f esp){
        
        indice_luz = indice;
        pos_luz = pos;
        ambiental = amb;
        difusa = dif;
        especular = esp;

}

void luz::activar(){
    //glEnable(GL_LIGHTING);
    glEnable(indice_luz);
    glLightfv(indice_luz, GL_AMBIENT, ambiental);
    glLightfv(indice_luz, GL_DIFFUSE, difusa);
    glLightfv(indice_luz, GL_SPECULAR, especular);
    glLightfv(indice_luz, GL_POSITION, pos_luz);
}

void luz::desactivar(){
    glDisable(indice_luz);
}   