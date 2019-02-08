#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include "aux.h"
// NECESARIO PARA CARGAR LAS IMÁGENES DE DISCO
#define cimg_use_jpeg
#include "CImg.h"
using namespace cimg_library;
using namespace std;


class Textura{
    protected:
        GLuint id;
        vector<GLfloat> vertices;
        vector<GLfloat> vertices_textura;
        CImg<unsigned char> imagen;
        vector<unsigned char> data;
    public:
        Textura( vector<GLfloat> vertice_cuadro, vector<GLfloat> vertices_text);
        void montar_textura();
        void dibujar(int num);
        void liberar();
};