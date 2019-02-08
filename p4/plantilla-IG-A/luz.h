#include "aux.h"
#include "malla.h"


class luz{
    public:
    luz(GLenum indice_luz, Tupla4f pos_luz, Tupla4f ambiental,
        Tupla4f difusa, Tupla4f especular);
    void activar();
    void desactivar();


    protected:
    GLenum indice_luz;
    Tupla4f pos_luz;
    Tupla4f ambiental;
    Tupla4f difusa;
    Tupla4f especular;
};