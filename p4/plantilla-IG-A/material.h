#include "aux.h"


class Material{
    private:
        Tupla4f ambiental;
        Tupla4f difusa;
        Tupla4f especular;
        float brillo;
    public:
        Material(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo);
        void activar();
        void desactivar();
};