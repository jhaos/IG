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
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo) ;

   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   void modoAjedrez();

   void calcularParImpar();


   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   std::vector<Tupla3i> pares;
   std::vector<Tupla3i> impares;
   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   GLuint id_vbo_vertices = 0;
   GLuint id_vbo_triangulos = 0;
   GLuint id_vbo_pares = 0;
   GLuint id_vbo_impares = 0;

   // completar: tabla de colores, tabla de normales de vértices
} ;

// *****************************************************************************
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
