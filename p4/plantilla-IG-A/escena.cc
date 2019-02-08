

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
    ply = new ObjPLY("plys/big_dodge.ply");
    rev = new ObjRevolucion("plys/peon.ply");
    cilindro = new Cilindro(10, 20);
    cono = new Cono(10, 20);
    esfera = new Esfera (30,20);
    jerarquico = new ObjJerarquico();
    Tupla4f blanco = Tupla4f(1,1,1,1);
    Tupla4f pos = Tupla4f(1,0,0,0);
    rot_luz = 0;
    Tupla4f mag = Tupla4f(0.9, 0.0, 0.9, 1);
    Tupla4f no_mag = Tupla4f(0.0, 0.0, 0.0, 1);
    pos_mag = Tupla4f(0, 0,1,1);
    l = new luz(GL_LIGHT0, pos, blanco, blanco, blanco);
    l1 = new luz(GL_LIGHT1, pos_mag, no_mag, mag, mag);
    activar = false;
    act_luz = false;
    smooth = false;
    n_material = 0;
    activar_movil = false;
    
    num_cuadro = 4;
    num_box = 24;
    cuadro = new Cuadro();
    num_objetos = 8; // se usa al pulsar la tecla 'O' (rotar objeto actual)
    num_modo = 4;     // cambia entre puntos, relleno y linea
    num_modo_dif_inm = 2; // para rotar el modo inmediato o diferido
    anim_activadas = false;
    menu();
}

  void Escena::menu(){
    cout << endl;
    cout << endl;
    cout << "Menú de teclas " << endl << endl;
    cout << "Pulse o para cambiar de objeto "<<endl;
    cout << "Pulse q para salir "<<endl;
    cout << "Pulse m para cambiar de modo, relleno, puntos, lineas y ajedrez" << endl;
    cout << "Pulse v para entrar en modo diferido" << endl;  
    cout << "Pulse l para activar luces" << endl;
    cout << "Pulse k para desactivar luces" << endl;
    cout << "Pulse f para activar luz blanca fija" << endl;  
    cout << "Pulse g para desactivar luz blanca fija" << endl;  
    cout << "Pulse h para activar luz móvil" << endl; 
    cout << "Pulse j para desactivar luz móvil" << endl; 
    cout << "Pulse j para desactivar luz móvil" << endl;
    cout << "Pulse 1 para activar modo suave"  << endl;
    cout << "Pulse 2 para activar modo plano"  << endl;
    cout << "Pulse 3 para activar material"  << endl;
    cout << endl;
 
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
   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'
   if (activar_movil){
      glPushMatrix();
            glRotatef(rot_luz, 0, 1, 0);
            cout << "Modo luz" << endl;
            l1->activar();
      glPopMatrix();
   }else
      l1->desactivar();
   
   
   if (activar)
      l->activar();
   else
      l->desactivar();
   switch( objeto_actual )
   {
      case 0:
           if ( cubo != nullptr ) cubo->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ;  
      break ;
      case 1:
           if ( tetraedro != nullptr ) tetraedro->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ;  
        break;
      case 2:
           if ( rev != nullptr ) rev->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ; 
        break;
      case 3:
           if ( cilindro != nullptr ) cilindro->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ;  
        break;
      case 4:
           if ( cono != nullptr ) cono->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ;  
        break;
      case 5:
        if ( esfera != nullptr ) esfera->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ;  
        break;
      case 6:
           if ( ply != nullptr ) ply->draw(modo_actual, (bool)modo_dif_inm, act_luz,false, smooth, n_material) ;  
        break;
      case 7:
          
          if ( cuadro != nullptr ) cuadro->modoTextura(num_cuadro)  ;
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

void Escena::mgeDesocupado(){
  jerarquico->actualizarEstado();
  glutPostRedisplay();
}

void Escena::conmutarAnimaciones(){

  if (objeto_actual == 7){
    anim_activadas = !anim_activadas;
    if (anim_activadas){
      jerarquico->inicioAnimaciones();
      glutIdleFunc(funcion_desocupado);
    }else{
      glutIdleFunc(nullptr);
    }
  }else {
    std::cout << "No es jerarquico" << std::endl;
  }
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
   
   if (tecla == 'z'){
        cout << "decrementa parametro " << endl;
        jerarquico->decrementaParamAct();
   }else{

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
        case 'A' :
           // activar siguiente objeto
          conmutarAnimaciones();
          cout << "conmutar Animaciones" << endl;
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
        case 'P':
          cout << "siguiente parametro " << endl;
          jerarquico->siguienteParametro();
          break;
        case 'Z':
          cout << "incrementa parametro " << endl;
          jerarquico->incrementaParamAct();
          break;
        case '>':
          cout << "acelerar " << endl;
          jerarquico->acelerar();
          break;
        case '<':
          cout << "decelerar " << endl;
          jerarquico->decelerar();
          break;
        case 'F':
          cout << "Modo luz" << endl;
          activar = true;
          break;
        case 'G':
          cout << "Modo luz" << endl;
          activar = false;
          break;
        case 'H':
          valor_na += 2;
          rot_luz = 360.0*0.05*valor_na;
          activar_movil = true;
          break;
        case 'J':
          cout << "Modo luz" << endl;
          activar_movil = false;
          break;
        case 'L':
          cout << "Modo luz" << endl;
          act_luz = true;
          break;
        case 'K':
          cout << "Modo luz" << endl;
          act_luz = false;
          break;
        case '1':
          cout << "Modo Suave" << endl;
          smooth = true;
          break;
        case '2':
          cout << "Modo Plano" << endl;
          smooth = false;
          break;
        case '3':
          cout << "Cambio de material" << endl;
          n_material++;
          n_material = n_material % 3;
          break;
        default:
          cout << "tecla sin uso" << endl;
        break;
    }
   }
   menu();
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_y++ ;
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
