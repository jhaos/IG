// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 2, 10 );
   cubo     = new Cubo();
   cono = new Cono(4, 16);
   punto_rot = new Esfera(15,20);
   pelota_esf = new Esfera(15, 20);
   

}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
bool f = false;
void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
         // altura 1: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
         // inicialmente es 1.0 (media de los valores extremos)
         ag_varilla_1 = -30*sin( 0.5*(2.0*M_PI*valor_na) );
         
         break ;
      case 1:
         // altura 2: oscila entre 1.1 y 1.9, a 0.8 oscilaciones por segundo
         ag_varilla_2 = 45*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 2:
         // angulo en grados de rotacion 1 (cubo rojoaa)
         // crece linealmente a 150 grados por segundo, inicialmente es 20 grados
         ag_varilla_3 = -60*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 3:
         // ángulo en grados de rotacion 2 (cubo azul)
         // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         // (inicialmente es -7.5 grados)
         ag_varilla_4 = -45 + 30*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 4:
        cambio_altura = sin( 2.0*(1.0*M_PI*valor_na) );
        break;
      case 5:
        rotacion_y = 150.0*valor_na ;
        break;
      case 6:
        translado_z_pelota = 180*valor_na ;;
        break;  
      
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );
   assert( cilindro != nullptr );
   assert( cono != nullptr );
   assert( punto_rot != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;

   // dibujar objetos


      altura_suelo = 0.05;
      ancho_largo = 0.5;
    

    glPushMatrix();
        glRotatef(rotacion_y, 0, 1, 0);
        glTranslatef(2, 0,0);
        
        glPushMatrix();
            if (cambio_altura > 0.00 ){
                glTranslatef(0, cambio_altura, 0);
            }

            glTranslatef(-0.25, 0.6, 0);
            superficie();
            lampara();
        
        glPopMatrix();

        glPushMatrix();
            //glScalef(0.3, aplastada, 0.3);        
            pelota();      
        glPopMatrix();
    glPopMatrix();
}
// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es una columna (cilindro) de altura = 'altura', con un cubo encima,
// rotado entorno a Y un ángulo en grados = 'ag_rotacion'


void GrafoParam::superficie(){
      glColor3f(0.1, 0.8, 0.3);
      glPushMatrix();
      glScalef(0.5, 0.05, 0.5);
      cilindro->draw(modo_vis, usar_diferido,f,f,f,0);
      glPopMatrix();

}

void GrafoParam::pelota(){
    glColor3f(0.3, 0.6, 0.2);
    glPushMatrix();
        glTranslatef(0, 0.3, 0);
        glRotatef(translado_z_pelota, 1, 0, 0);
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0, 0, 0);
        pelota_esf->draw(modo_vis, usar_diferido,f,f,f,0);
    glPopMatrix();
}

void GrafoParam::lampara(){
    
    //Parte 1,2,3,4
    glPushMatrix();
    //Parte 1,2,3
        glPushMatrix();
    //Parte 1 y 2
            glPushMatrix();
    //parte 1   
                glColor3f(0.1, 0.2, 0.8);
                glPushMatrix(); 
                    glTranslatef(0,0.05,0);
                    glRotatef(ag_varilla_1, 0,0,1);
                    glTranslatef(0,0.0,0);
                    varillaEsfera();
                glPopMatrix();
//Parte 2

                glPushMatrix();
                    glRotatef(ag_varilla_1-ag_varilla_1/16, 0,0,1);
                    glTranslatef(0,0.554,0);
                    glRotatef(ag_varilla_2, 0,0,1);
                    glTranslatef(0,0.0,0);
                    varillaEsfera();
                glPopMatrix();
      //fin parte 2
            glPopMatrix();
     //fin parte 1 y 2
     //Parte 3
            glPushMatrix();
        
                glRotatef(ag_varilla_1-ag_varilla_1/16, 0,0,1);
                glTranslatef(0,0.554,0);
                glRotatef(ag_varilla_2, 0,0,1);
                glTranslatef(0,0.554,0);
                glRotatef(ag_varilla_3, 0,0,1);
                glTranslatef(0,0,0);
                varillaEsfera();

            glPopMatrix();
      //Fin parte 3
        glPopMatrix();
     //Fin parte 1,2,3
      
     //Inicio parte 4
        glPushMatrix();
            glRotatef(ag_varilla_1-ag_varilla_1/16,0,0,1);
            glTranslatef(0,0.554, 0);
            glRotatef(ag_varilla_2,0,0,1);
            glTranslatef(0,0.554, 0);
            glRotatef(ag_varilla_3,0,0,1);
            glTranslatef(0,0.554, 0);
            glRotatef(ag_varilla_4,0,0,1);
            glTranslatef(0,0,0);
            cabeza();
      
        glPopMatrix();  
    glPopMatrix();
     //Final parte 1,2,3,4
}

void GrafoParam::varillaEsfera(){
    glPushMatrix();
            glTranslatef(0.0, 0.26,0.0);
            glScalef(0.05,0.5,0.05);
            cubo->draw(modo_vis, usar_diferido,f,f,f,0);
      glPopMatrix();

      glPushMatrix();
            glScalef(0.05, 0.05, 0.05);
            punto_rot->draw(modo_vis, usar_diferido,f,f,f,0);
    glPopMatrix();
}

void GrafoParam::cabeza (){
      glColor3f(0.5, 0.2, 0.8);
      glPushMatrix();
        glTranslatef(0,0.75,0);
        glRotatef(180,0,0,1);
        glTranslatef(0,0,0);
        glScalef(1, 1, 1); 
        cono->draw(modo_vis, usar_diferido,f,f,f,0);
      glPopMatrix();

      glPushMatrix();
            
            glScalef(0.05, 0.05, 0.05);
            punto_rot->draw(modo_vis, usar_diferido,f,f,f,0);
      glPopMatrix();
}