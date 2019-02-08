

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    ply = new ObjPLY("plys/ant.ply");
    rev = new ObjRevolucion("plys/peon.ply");
    cilindro = new Cilindro(10, 20);
    cono = new Cono(10, 20);
    esfera = new Esfera (50,20);

    // .......completar: ...
    // .....

    num_objetos = 7 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
    num_modo = 3;     // cambia entre puntos, relleno y linea
    num_modo_dif_inm = 3; // para rotar el modo inmediato o diferido
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	
  redimensionar(UI_window_width, UI_window_height);
  
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************



void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)
    //glColor3f(0.5,0.5,0.5);
    glShadeModel(GL_FLAT);
   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch(modo_actual){
     case 0:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        cout << "cambio a modo relleno con modo actual " << modo_actual << endl;
        break;
      case 1:
        glPointSize(3.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        cout << "cambio a modo puntos con modo actual " << modo_actual << endl;
        break;
      case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        cout << "cambio a modo linea con modo actual " << modo_actual << endl;
        break;
      default:
        cout << "modo "<< modo_actual << " incorrecto" << endl;
        break;
   }

   switch( objeto_actual )
   {
      case 0:
        if (modo_actual !=3){
           if ( cubo != nullptr ) cubo->draw(modo_dif_inm) ;  
        }else{
          if ( cubo != nullptr ) cubo->draw(0) ;
        }
      break ;
      case 1:
           if ( tetraedro != nullptr ) tetraedro->draw(modo_dif_inm) ;  
        break;
      case 2:
           if ( rev != nullptr ) rev->draw(modo_dif_inm) ;  
        break;
      case 3:
           if ( cilindro != nullptr ) cilindro->draw(modo_dif_inm) ;  
        break;
      case 4:
           if ( cono != nullptr ) cono->draw(modo_dif_inm) ;  
        break;
      case 5:
        if ( esfera != nullptr ) esfera->draw(modo_dif_inm) ;  
        break;
      case 6:
           if ( ply != nullptr ) ply->draw(modo_dif_inm) ;  
        break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }

  // cout << num_modo << endl;
   
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();
	dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   

   switch( toupper(tecla) )
   {
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
         break ;
      case 'M' :
      //activar el sigiente modo
        modo_actual = (modo_actual + 1) % num_modo;
        cout << "modo actual == " << modo_actual << endl ;
        break;
      case 'V':
        modo_dif_inm = (modo_dif_inm + 1) % num_modo_dif_inm;
        cout << "modo dif/inm == " << modo_dif_inm << endl;
        break;
      default:
        cout << "tecla sin uso" << endl;
        break;
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane, wx = ratio_xy*wy;
  glFrustum(-wx, +wx, -wy, +wy, Front_plane, Back_plane);
   }
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth;
   Height = newHeight;
   change_projection( float(Width)/float(Height) );
   glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_x, 0.0, 1.0, 0.0 );
}
