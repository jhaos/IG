#include "aux.h"
#include "ply_reader.h"
#include "malla.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

   
// Visualización en modo inmediato con 'glDrawElements'
void ObjMallaIndexada::modoTextura(int num){
  
  if (textura!=nullptr){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    textura->montar_textura();
    textura->dibujar(num);
    textura->liberar();
  }
  
}


void ObjMallaIndexada::draw_ModoInmediato(bool luz_activa, bool smooth, int n_material)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...
    
    glEnableClientState( GL_VERTEX_ARRAY );

    if (luz_activa){
      cout << "luz activa "<< luz_activa << endl;
      glEnableClientState( GL_NORMAL_ARRAY );
      glEnable(GL_LIGHTING);
      if (n_material == 0)
        mat->activar();
      else if (n_material == 1)
        cyan->activar();
      else if (n_material == 2)
        croma->activar();
      
      glNormalPointer( GL_FLOAT, 0, normal_vertices.data() );
      
    }

    if (smooth)
      glShadeModel(GL_SMOOTH);
    else 
      glShadeModel(GL_FLAT);
    
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
    glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
    
    if(luz_activa){
      glDisable(GL_LIGHTING);
      glDisableClientState( GL_NORMAL_ARRAY );
    }
    glDisableClientState( GL_VERTEX_ARRAY );
    
    
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

  if (id_vbo_vertices == 0){
    id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, 3*vertices.size()*sizeof(float), vertices.data());
  }

  if (id_vbo_triangulos == 0){
    id_vbo_triangulos = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*triangulos.size()*sizeof(int), triangulos.data());
  }

//offset, formato y habilitar la tabla
  glBindBuffer (GL_ARRAY_BUFFER, id_vbo_vertices); //Para activar el VBO de vertices
  glVertexPointer(3, GL_FLOAT, 0 ,0); //especificamos el formato y el offset para que no haya separacion
  glBindBuffer(GL_ARRAY_BUFFER, 0); //desactiva vbo de vvertices
  glEnableClientState(GL_VERTEX_ARRAY); //habilita la tabla de vertices


  //visualizar los triangulos con gldrawelements
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_triangulos); //activar el vbo de triangulos
  glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //desactivamos vbo

  glDisableClientState(GL_VERTEX_ARRAY); //desactivamos el array de vertices.s
}


void ObjMallaIndexada::modoAjedrez(){

    calcularParImpar();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    
    glColor3f(0.0, 0.0, 0.0);
    glDrawElements (GL_TRIANGLES, pares.size()*3, GL_UNSIGNED_INT, pares.data());


    glColor3f(0.6, 0.6, 0.6);
    glDrawElements (GL_TRIANGLES, impares.size()*3, GL_UNSIGNED_INT, impares.data());
    
    glDisableClientState( GL_VERTEX_ARRAY );
    
}

GLuint ObjMallaIndexada::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram){
         GLuint id_vbo;  //identifica el VBO
         glGenBuffers (1, &id_vbo); //creacion del vbo nunca poner a cero el identificador
         glBindBuffer (tipo_vbo, id_vbo); //activar el vbo a partir del id que asignamos en genbuffers
         
         glBufferData (tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);//Realiza transferencia de datos
         glBindBuffer (tipo_vbo, 0); //poniendo el id en cero conseguimos desactivarlo
         
         return id_vbo; //devuelve el id      
   }



// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int modo_actual, const bool diferido, bool luz, bool text, bool smooth, int n_material)
{
  
   // completar .....(práctica 1)
  
  calcular_normales();

  if (diferido){
    switch(modo_actual){
     case 0:
        glPolygonMode(GL_FRONT, GL_FILL);
        cout << "cambio a modo relleno con modo actual " << modo_actual << endl;
        draw_ModoDiferido();
        cout << "cambio a modo diferido" << endl;
        break;
      case 1:
        glPointSize(3.0);
        glPolygonMode(GL_FRONT, GL_POINT);
        cout << "cambio a modo puntos con modo actual " << modo_actual << endl;
        draw_ModoDiferido();
        cout << "cambio a modo diferido" << endl;
        break;
      case 2:
        glPolygonMode(GL_FRONT, GL_LINE);
        cout << "cambio a modo linea con modo actual " << modo_actual << endl;
        draw_ModoDiferido();
        cout << "cambio a modo diferido" << endl;
        break;
      default:
        cout << "modo "<< modo_actual << " incorrecto" << endl;
        break;
    }
  }else if (!diferido && !text){
    switch(modo_actual){
     case 0:
        glPolygonMode(GL_FRONT, GL_FILL);
        cout << "cambio a modo relleno con modo actual " << modo_actual << endl;
        draw_ModoInmediato(luz, smooth, n_material);
        cout << "cambio a modo inmediato " << endl;
        break;
      case 1:
        glPointSize(3.0);
        glPolygonMode(GL_FRONT, GL_POINT);
        cout << "cambio a modo puntos con modo actual " << modo_actual << endl;
        draw_ModoInmediato(luz, smooth, n_material);
        cout << "cambio a modo inmediato " << endl;
        break;
      case 2:
        glPolygonMode(GL_FRONT, GL_LINE);
        cout << "cambio a modo linea con modo actual " << modo_actual << endl;
        draw_ModoInmediato(luz, smooth, n_material);
        cout << "cambio a modo inmediato " << endl;
        break;
      case 3:
        modoAjedrez();
        cout << "cambio a modo ajedrez con modo inmediato " << endl;
      default:
        cout << "modo "<< modo_actual << " incorrecto" << endl;
        break;
    }

  
  }
  
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{

  int i0, i1, i2;
  Tupla3f a, b, c;
  int contador = 0;
  normal_vertices.assign(vertices.size(), Tupla3f(0.0,0.0,0.0));

  for (int i = 0; i < triangulos.size(); ++i){
    i0 = triangulos[i][0];
    i1 = triangulos[i][1];
    i2 = triangulos[i][2];

    a = vertices[i1] - vertices[i0];
    b = vertices[i2] - vertices[i0];

    c = a.cross(b);
    normal_triangulos.push_back(c);

  } 
  
  for ( int i = 0 ; i < triangulos.size() ; i++){

        normal_vertices[triangulos[i][0]] = normal_vertices[triangulos[i][0]] + normal_triangulos[i];
        normal_vertices[triangulos[i][1]] = normal_vertices[triangulos[i][1]] + normal_triangulos[i];
        normal_vertices[triangulos[i][2]] = normal_vertices[triangulos[i][2]] + normal_triangulos[i];  
  }

  for (int i = 0; i < normal_vertices.size(); ++i){
    normal_vertices[i] = normal_vertices[i].normalized();
  }

}
   // completar .....(práctica 2)


void ObjMallaIndexada::calcularParImpar(){
    

    for (int i = 0; i < triangulos.size(); ++i){
      if ((i%2)==0){
        pares.push_back(triangulos[i]);
      }else{
        impares.push_back(triangulos[i]);
      }
    }

}

void ObjRevolucion::RecorridoPuntos(const vector<Tupla3f> & perfil_vertices, const int num_vueltas){
  float porcentaje;
  int cont = 0;
  Tupla3f vert;
   for (int i = 0; i < num_vueltas; ++i){
      for (int j = 0; j < perfil_vertices.size(); ++j){
          float x =  cos((2*M_PI*i)/num_vueltas)*perfil_vertices[j][0] + sin((2*M_PI*i)/num_vueltas)*perfil_vertices[j][2];
          float y = perfil_vertices[j][1];
          float z = -sin((2*M_PI*i)/num_vueltas)*perfil_vertices[j][0] + cos((2*M_PI*i)/num_vueltas)*perfil_vertices[j][2];
          vert = {x, y, z};
        vertices.push_back(vert);
      }
       cont++;
    }

}



void ObjRevolucion::RecorridoTriangulos (const vector<Tupla3f> & perfil_vertices, const int num_vueltas){
    
    for (int i = 0; i < num_vueltas; ++i){
      for (int j = 0; j < perfil_vertices.size()-1; ++j){
        int a = perfil_vertices.size()*i + j;
        int b = perfil_vertices.size()*((i+1)%num_vueltas) + j;
        
        Tupla3i triangulo_1 = {a, b, b+1};
        Tupla3i triangulo_2 = {a, b+1, a +1};
        triangulos.push_back(triangulo_1);
        triangulos.push_back(triangulo_2);
        
      }
    }
}
void ObjRevolucion::crearMalla (const vector<Tupla3f> & perfil_vertices, const int num_vueltas, const bool esfera){
    vertices.clear();

    RecorridoPuntos(perfil_vertices, num_vueltas);

    triangulos.clear();

    RecorridoTriangulos(perfil_vertices, num_vueltas);
    if (!esfera){
      sacarTapas(perfil_vertices, num_vueltas);
    }
    

}


void ObjRevolucion::tapaSur(int tam_perfil_vertices, int num_vueltas){
  Tupla3i triangulo_tapa_sur;
  long unsigned int unidad_2 = 2;
  for (int i = 0; i < num_vueltas; ++i){
    
    if ((i+1) == num_vueltas){
      triangulo_tapa_sur = {i*tam_perfil_vertices,vertices.size()-unidad_2, 0};
    }else{
      triangulo_tapa_sur = { i*tam_perfil_vertices, vertices.size()-unidad_2,(i+1)*tam_perfil_vertices};
    }
    triangulos.push_back(triangulo_tapa_sur);

  }
}

void ObjRevolucion::tapaNorte(int tam_perfil_vertices, int num_vueltas){
  Tupla3i triangulo_tapa_norte;
  long unsigned int unidad = 1;
  for (int i = 0; i < num_vueltas; ++i){
    
    if ((i+1) == num_vueltas){
      triangulo_tapa_norte = {vertices.size()-unidad, (i+1)*tam_perfil_vertices-1, tam_perfil_vertices-1};
    }else{
      triangulo_tapa_norte = {vertices.size()-unidad,  (i+1)*tam_perfil_vertices-1,(i+2)*tam_perfil_vertices-1};
    }
    triangulos.push_back(triangulo_tapa_norte);

  }
}

void ObjRevolucion::sacarTapas (const vector<Tupla3f> & perfil_vertices, const int num_vueltas){
  Tupla3f vertice_sur = perfil_vertices[0];
  vertice_sur[0] = 0;
  Tupla3f vertice_norte = perfil_vertices[perfil_vertices.size()-1];
  vertice_norte[0] = 0;
  vertices.push_back(vertice_sur);
  vertices.push_back(vertice_norte);
  tapaSur(perfil_vertices.size(), num_vueltas);
  tapaNorte(perfil_vertices.size(), num_vueltas);
}


// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 },  // 7
                 /* { 0, 0, 1.0 }, //8 arriba
                  { 0, 0.0, -1.0 }*/   //9 abajo YUNKE
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { 
     
     
                  { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 },//a partir de aqui triangulos del yunke
                  
                 /*{0, 2, 9}, {2, 6, 9},
                 {6, 4, 9}, {4, 0, 9},
                 {1, 5, 8}, {5, 7, 8},    //YUNKEE
                 {7, 3, 8}, {3, 1, 8}*/
                } ;
    
}




// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Tetraedro::Tetraedro(){

    vertices = {{-0.6, -0.6, -0.6}, //0
                {0.6, 0.6, 0.6}, //1
                {-0.6, 0.6, 0.6}, //1
                {0.6, 0.6,-0.6 } //2
    };

    triangulos = {{0, 1, 2},
                  {0, 2, 3},
                  {0, 3, 1},
                  {1, 2, 3}

    };

  

}



Cuadro::Cuadro(){

    vertices = {{-0.5, 0.5,0.0},
                {-0.5,0.0,0.0},
                {0.5, 0.0, 0.0},
                {0.5,0.5,0.0}
                };

    triangulos = {{0,1,2},
                  {2,3,0}};

    vertice_cuadro = { 0, 0,
                       5, 0,
                       5, 5,
                       0, 5};

    vertice_texturas = {0.0,1.0,
			                  1.0,1.0,
			                  1.0,0.0,
			                  0.0,0.0};
    textura = new Textura(vertice_cuadro, vertice_texturas);
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
   
}

ObjRevolucion::ObjRevolucion(){
  ;
}


Cilindro::Cilindro(const int num_vertices_perfil, const int num_instancias_perfil){

  float distancia_puntos = RADIO/num_vertices_perfil;
  float acumulado = 0;
  vector<Tupla3f> perfil;
  
  for (int i = 0; i <= num_vertices_perfil; ++i){
    float x = 1.0;
    float y = acumulado;
    float z = 0;
    Tupla3f punto = Tupla3f(x,y,z);
    perfil.push_back(punto);
    acumulado+=distancia_puntos;
  }
  
  crearMalla(perfil, num_instancias_perfil, false);
}

Cono::Cono(const int num_vertices_perfil, const int num_instancias_perfil){
  float distancia_puntos = RADIO/(num_vertices_perfil);
  float acumulado = 0 - distancia_puntos;
  float acumulado_x = 1.0;
  vector<Tupla3f> perfil;

  for (int i = 0; i < num_vertices_perfil; ++i){
    float x = acumulado_x-distancia_puntos;
    float y = acumulado+distancia_puntos;
    float z = 0;

    Tupla3f punto = Tupla3f(x,y,z);
    perfil.push_back(punto);
    acumulado+=distancia_puntos;
    acumulado_x-=distancia_puntos;
    
  }
  
  crearMalla(perfil, num_instancias_perfil, false);
}




Esfera::Esfera(const int num_vertices_perfil, const int num_instancias_perfil){
  float distancia_puntos = RADIO/num_vertices_perfil;
  vector<Tupla3f> perfil;


  for (int i = 0; i < num_vertices_perfil; ++i){

    float alfa = -(M_PI/2) + (i*M_PI/(num_vertices_perfil+1));
    float y = RADIO*sin(alfa);
    float x = RADIO*cos(alfa); //tambien x = sqrt(1-y*y);

    Tupla3f punto = {x, y, 0};
    perfil.push_back(punto);
  }
    Tupla3f punto = {0,1,0};
    perfil.push_back(punto);
  
  crearMalla(perfil, num_instancias_perfil, true);

}

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil )
{
  vector<Tupla3f> vertices_malla;
  ply::read_vertices(nombre_ply_perfil, vertices_malla);

  crearMalla(vertices_malla, 20, false);
  
   // completar ......(práctica 2)
}

