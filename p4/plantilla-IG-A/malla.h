// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED
#include "aux.h"
#include "material.h"
#include "textura.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:
   //crear un VBO
   
   
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool luz_activa, bool smooth, int n_material);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   
   // está funcTupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brilloión llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo, const bool diferido, bool luz, bool text, bool smooth, int n_material) ;

   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   void modoAjedrez();

   void calcularParImpar();

   void modoTextura(int num);

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   std::vector<Tupla3f> normal_triangulos;
   std::vector<Tupla3f> normal_vertices;
   std::vector<Tupla3i> pares;
   std::vector<Tupla3i> impares;
   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   GLuint id_vbo_vertices = 0;
   GLuint id_vbo_triangulos = 0;
   GLuint id_vbo_pares = 0;
   GLuint id_vbo_impares = 0;
   bool colores_rellenos = false;
   
   std::vector<GLfloat> vertice_cuadro;
   std::vector<GLfloat> vertice_texturas;
   Textura *textura = nullptr;

   Tupla4f mat_ambiental = {0.24725, 0.1995, 0.0745, 1};
   Tupla4f mat_difusa = {0.75164, 0.60648, 0.22648, 1};
   Tupla4f mat_especular = {0.628281, 0.555802, 0.366065, 1};
   float mat_brillo = 0.4*128;
   Material * mat = new Material(mat_ambiental, mat_difusa, mat_especular, mat_brillo);
   Material * cyan = new Material(Tupla4f(0.0, 0.1, 0.06,1), Tupla4f(0.0, 0.50980392, 0.50980392,1), Tupla4f(0.50196078, 0.50196078, 0.50196078,1), 0.25*128);
   Material * croma = new Material(Tupla4f(0.25,0.25,0.25,1), Tupla4f(0.4, 0.4, 0.4,1), Tupla4f(0.774597, 0.774597, 0.774597,1), 0.6*128);
   // completar: tabla de colores, tabla de normales de vértices
} ;

// *****************************************************************************0.24725, 0.1995, 0.0745
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo() ;

} ;

class Cuadro : public ObjMallaIndexada{
      public:
      Cuadro();
      
};



class Tetraedro : public ObjMallaIndexada {
      public:
      Tetraedro();
};


// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      ObjRevolucion();
      ObjRevolucion( const std::string & nombre_ply_perfil );
   protected:
      const float RADIO = 1.0;
      void crearMalla (const std::vector<Tupla3f> & perfil_vertices, const int num_vueltas, const bool esfera);
      void RecorridoTriangulos (const std::vector<Tupla3f> & perfil_vertices, const int num_vueltas);
      void RecorridoPuntos(const std::vector<Tupla3f> & perfil_vertices, const int num_vueltas);
      void sacarTapas (const std::vector<Tupla3f> & perfil_vertices, const int num_vueltas);
      void tapaSur(int tam_perfil_vertices, int num_vueltas);
      void tapaNorte(int tam_perfil_vertices, int num_vueltas);
      
} ;





class Cono : public ObjRevolucion{
      public:
      Cono(const int num_vertices_perfil, const int num_instancias_perfil);
};

class Cilindro : public ObjRevolucion{
      public:
      Cilindro(const int num_vertices_perfil, const int num_instancias_perfil);
};


class Esfera : public ObjRevolucion{
      public:
      Esfera(const int num_vertices_perfil, const int num_instancias_perfil);
};

#endif
