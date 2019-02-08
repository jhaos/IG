// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 6 ; // número de parámetros o grados de libertad
                                   // de este modelo
typedef int ModoVis;


class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const ModoVis p_modo_vis, const bool p_usar_diferido );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void varillaEsfera();

   void pelota();
                        
   void superficie ();

   void lampara();

   void cabeza();

   

   // objetos tipo malla indexada (nodos terminales)

   Cilindro * cilindro = nullptr ;
   Cubo *     cubo     = nullptr ;
   Cono * cono = nullptr;
   Esfera * punto_rot = nullptr;
   Esfera * pelota_esf = nullptr;

   // parámetros de la llamada actual (o última) a 'draw'
   ModoVis modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   float altura_1,       // altura de la primera columna
         ag_rotacion_1,  // ángulo en grados de rotación (1)
         altura_2,       // altura de la segunda columna
         ag_rotacion_2,
         ag_varilla_1,
         ag_varilla_2,
         ag_varilla_3,
         ag_varilla_4,
         cambio_altura,
         ancho_largo,
         altura_suelo,
         rotacion_y,
         rotacion_z,
         translado_z_pelota,
         aplastada; // ángulo en grados de rotación (2)
      
 
} ;

#endif
