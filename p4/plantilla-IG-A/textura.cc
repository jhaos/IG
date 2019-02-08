#include "textura.h"

Textura::Textura( vector<GLfloat> vertice_cuadro, vector<GLfloat> vertices_text){
    vertices = vertice_cuadro;
    vertices_textura = vertices_text;

}



void Textura::montar_textura(){
    imagen.load("./logo.jpg");
    
    for (long y = 0; y < imagen.height(); ++y){
        for (long x = 0; x < imagen.width(); ++x){
            unsigned char *red = imagen.data(x, y, 0, 0);
	        unsigned char *green = imagen.data(x, y, 0, 1);
	        unsigned char *blue = imagen.data(x, y, 0, 2);
	        data.push_back(*red);
	        data.push_back(*green);
	        data.push_back(*blue);
        }
    }
   
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

}

void Textura::dibujar(int num){
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    if (num == 4)
        glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    else if (num == 24)
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());

        
    glTexCoordPointer(2, GL_FLOAT, 0, vertices_textura.data());

    glDrawArrays(GL_QUADS, 0, num);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    
}
void Textura::liberar(){
    glDeleteTextures(1, &id);
}