//
//  main.cpp
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/23/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <GLUT/glut.h>
//#include <GL/glew.h>
///////////////////- Otras Librerías -/////////////////
//#include <OpenGL/gl3.h>
#include <OpenGl/glu.h>
#include <vector>
///////////////////- Otras Librerías -/////////////////

#include <OpenGL/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <iostream>

using namespace std;

#include "Vector3D.h"

#include "Solido.h"
#include "Cubo.h"
#include "Paleta.h"
#include "Esfera.h"
#include "Escena.h"
#include "Cilindro.h"
#include "Camara.h"
#include "Pared.h"
#include "Toroide.h"
#include "Modelo.h"
#include "Pelota.h"

double t=0.0;
double dt=1.0/30;
GLdouble pitch=0.0f;
shared_ptr<Paleta> c;
shared_ptr<Paleta> c1;
shared_ptr<Pelota> f;
int ji=0, jd=0, punto =0;

int mx=-1,my=-1;        // Previous mouse coordinates
//int rotangles[2] = {0}; // Panning angles

Escena e;
Camara cam;


void displayMe(void){
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cam.render();
    GLfloat lightpos[]={5.0,15.0,5.0,0.0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    e.render();
    glutSwapBuffers();
}

void idle(){
    if(ji==7){
        ji=0;
        jd=0;
        cout << "Jugador Izquierda es el ganador" << endl;
        cout << "Jugador Izquierda=> " << ji << " || " << jd << "<= Jugador Derecha" << endl;
        cout << "Pulse 'Z' para lanzar la pelota" << endl;
    } else if(jd==7){
        ji=0;
        jd=0;
        cout << "Jugador Derecha es el ganador" << endl;
        cout << "Jugador Izquierda=> " << ji << " || " << jd << "<= Jugador Derecha" << endl;
        cout << "Pulse 'Z' para lanzar la pelota" << endl;
    }
    punto=f->colision(c, true);
    f->colision(c1, false);
    if(punto==1){
        ji++;
        cout << "Jugador Izquierda=> " << ji << " || " << jd << "<= Jugador Derecha" << endl;
    } else if(punto==2){
        jd++;
        cout << "Jugador Izquierda=> " << ji << " || " << jd << "<= Jugador Derecha" << endl;
    }
    
    
    
    t+=dt;
    e.update(dt);
    displayMe();
}
double getRand(double max, double min = 0) {
    srand(10);
    double n = max - min;
    int ir = rand() % 1000;
    return min + (double)ir / 1000 * n;
}

void keyPressed(unsigned char key,int x,int y){
    srand(time(NULL));
    double t1 = rand() % 2;
    bool b=(f->getPos().getX()==0);
    //double t1 = getRand(1);
    switch(key){
        case GLUT_KEY_UP:
        case 'O':
        case 'o':
            c->setVel(Vector3Dd(0,0,5)*-1);
            break;
        case GLUT_KEY_DOWN:
        case 'L':
        case 'l':
            c->setVel(Vector3Dd(0,0,5)*1);
            break;
        case 'W':
        case 'w':
            c1->setVel(Vector3Dd(0,0,5)*-1);
            break;
        case 'S':
        case 's':
            c1->setVel(Vector3Dd(0,0,5)*1);
            break;
        case 'Z':
        case 'z':
            if(b){
                if(t1 == 1){
                    f->setVel(Vector3Dd(-2,0,-2));
                } else{
                    f->setVel(Vector3Dd(2,0,2));
                }
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

void keyReleased(unsigned char key,int x,int y){
    switch(key){
        case GLUT_KEY_UP:
        case 'O':
        case 'o':
            c->setVel(Vector3Dd(0,0,0));
            break;
        case GLUT_KEY_DOWN:
        case 'L':
        case 'l':
            c->setVel(Vector3Dd(0,0,0));
            break;
        case 'W':
        case 'w':
            c1->setVel(Vector3Dd(0,0,0));
            break;
        case 'S':
        case 's':
            c1->setVel(Vector3Dd(0,0,0));
            break;
        case 27:
            exit(0);
            break;
    }
}
void mouseMoved(int x, int y)
{
    if (mx>=0 && my>=0) {
        Vector3Dd r;
        r=cam.getRot()+Vector3Dd(y-my,x-mx,0);
        cout << r << endl;
        cam.setRot(r);
    }
    mx = x;
    my = y;
    
}

void mousePress(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mx = x;
        my = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mx = -1;
        my = -1;
    }
}
void init(void){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0,0.0,0.0,0.0);
}
void reshape(int width,int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);
    glMatrixMode(GL_MODELVIEW);
    
}


int main(int argc, char** argv) {
    cout << "Jugador izquierda (Teclas W y S) - Jugador derecha (Teclas O y L)" << endl;
    cout << "Jugador Izquierda=> " << ji << " || " << jd << "<= Jugador Derecha" << endl;
    cout << "Pulse 'Z' para lanzar la pelota" << endl;
    cam.setRot(Vector3Dd(0, 0, 90));
    cam.setPos(Vector3Dd(0,35,0));
    
    
    shared_ptr<Toroide> tor;
    shared_ptr<Pared> p;
    
    f= make_shared<Pelota> ();
    f->setPos(Vector3Dd(0,0,0));
    f->setVel(Vector3Dd(0,0, 0));
    f->setCol(Vector3Dd(1,0,1));
    f->setF(Vector3Dd(0,-0.98,0));
    f->setM(1);
    f->setR(.6);
    
    e.add(f);
    
    /* f= make_shared<Esfera> ();
     f->setPos(Vector3Dd(0,0,17));
     f->setVel(Vector3Dd(-3,0, 5));
     f->setCol(Vector3Dd(1,0,1));
     f->setF(Vector3Dd(0,-0.98,0));
     f->setM(1);
     f->setR(.6);
     e.add(f);
     
     f= make_shared<Esfera> ();
     f->setPos(Vector3Dd(0,0,-17));
     f->setVel(Vector3Dd(4,0, 5));
     f->setCol(Vector3Dd(1,0,1));
     f->setF(Vector3Dd(0,-0.98,0));
     f->setM(1);
     f->setR(.6);
     e.add(f);*/
    
    
    c= make_shared<Paleta> ();
    c->setPos(Vector3Dd(30,0,0));
    c->setVel(Vector3Dd(0,0,0));
    c->setCol(Vector3Dd(1,0,0));
    c->setF(Vector3Dd(0,-0.98,0));
    c->setM(1);
    c->setS(1);
    e.add(c);
    
    c1= make_shared<Paleta> ();
    c1->setPos(Vector3Dd(-30,0,0));
    c1->setVel(Vector3Dd(0,0,0));
    c1->setCol(Vector3Dd(0,0,1));
    c1->setF(Vector3Dd(0,-0.98,0));
    c1->setM(1);
    c1->setS(1);
    e.add(c1);
    
    
    
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(680,400);
    glutInitWindowPosition(300,300);
    glutCreateWindow("Ping-Pong");
    init();
    glutDisplayFunc(displayMe);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyReleased);
    //glutMotionFunc(&mouseMoved);
    //glutMouseFunc(&mousePress);
    glutMainLoop();
    
    
    return 0;
}

