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

#include "Vector3d.h"

#include "Solid.h"
#include "Cube.h"
#include "Paddle.h"
#include "Sphere.h"
#include "Scene.h"
#include "Brick.h"
#include "Camera.h"
#include "Ball.h"

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=1.0f;

// XZ position of the camera
float x=10.0f, z=35.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;




//vdfvrgvgeabavadv S N O W M A N

double t=0.0;
double dt=1.0/30;
GLdouble pitch=0.0f;
shared_ptr<Paddle> paddle;
vector<shared_ptr<Brick>> bricks;
shared_ptr<Ball> ball;

bool pause = false;
Vector3Dd ballVel;


int ji=0, jd=0, punto =0;

int mx=-1,my=-1;        // Previous mouse coordinates
//int rotangles[2] = {0}; // Panning angles

Scene e;
Camera cam;

void computePos(float deltaMove) {
    
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void displayMe(void){
    if (deltaMove)
        computePos(deltaMove);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    
    
    
    if (pause) {
        // Set the camera
        gluLookAt(    x, z, 0.0f,
                  x+lx, 0.0+lz,  0.0f,
                  0.0f, 0.0f,  -1.0f);
    } else {
        cam.render();
    }
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
        cout << "Pulse 'Z' para lanzar la Ball" << endl;
    } else if(jd==7){
        ji=0;
        jd=0;
        cout << "Jugador Derecha es el ganador" << endl;
        cout << "Jugador Izquierda=> " << ji << " || " << jd << "<= Jugador Derecha" << endl;
        cout << "Pulse 'Z' para lanzar la Ball" << endl;
    }
    
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


void keyPressed(unsigned char key,int x,int y){
    switch(key){
        case 'p': case 'P':
            pause = !pause;
            if (pause) {
                // Change to pause camera
                ballVel = e.ball->getVel();
                e.ball->setVel(Vector3Dd(0,0,0));
            } else {
                // Go back to game camera
                e.ball->setVel(ballVel);
            }
            break;
        case 32:
            if(ball->waitingForStart){
                ball->waitingForStart = false;
                ball->setVel(Vector3Dd(-0.3, 0, -0.3));
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

void keyReleased(unsigned char key,int x,int y){
    switch(key){
        case 27:
            exit(0);
            break;
    }
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT :
            paddle->setVel(Vector3Dd(1,0,0)*-1);
            if (ball->waitingForStart) {
                ball->setVel(Vector3Dd(1,0,0)*-1);
            }
            
            break;
        case GLUT_KEY_RIGHT :
            paddle->setVel(Vector3Dd(1,0,0)*1);
            if (ball->waitingForStart) {
                ball->setVel(Vector3Dd(1,0,0)*1);;
            }
            break;
        case GLUT_KEY_UP : deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
            
    }
}

void releaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            paddle->setVel(Vector3Dd(0,0,0));
            if (ball->waitingForStart) {
                ball->setVel(Vector3Dd(0,0,0));;
            }
            break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}
void mouseMove(int x, int y) {
    
    // this will only be true when the left button is down
    if (xOrigin >= 0) {
        
        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.01f;
        
        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y) {
    
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        
        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            xOrigin = x;
        }
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
    int brickRows = 1; // From 1 to 5
    cout << "Type the number of rows you want for your bricks (1 to 5 only)" << endl;
    cin >> brickRows;
    
    
    cam.setRot(Vector3Dd(0, 0, 90));
    cam.setPos(Vector3Dd(0,35,0));
    
    ball = make_shared<Ball> ();
    ball->setPos(Vector3Dd(0,0,15));
    ball->setVel(Vector3Dd(0,0,0));
    ball->setCol(Vector3Dd(200.0/255.0, 200.0/255.0, 200.0/255.0));
    ball->setF(Vector3Dd(0,-0.98,0));
    ball->setM(1);
    ball->setR(.6);
    e.ball = ball;
    
    paddle = make_shared<Paddle> ();
    paddle->setPos(Vector3Dd(0,0,17));
    paddle->setVel(Vector3Dd(0,0,0));
    paddle->setCol(Vector3Dd(200.0/255.0, 200.0/255.0, 200.0/255.0));
    paddle->setF(Vector3Dd(0,-0.98,0));
    paddle->setM(1);
    paddle->setS(1);
    e.paddle = paddle;
    
    for (int i=0; i<11; i++) {
        for (int j=0; j<brickRows; j++) {
            shared_ptr<Brick> brick = make_shared<Brick> ();
            bricks.push_back(brick);
            brick->setPos(Vector3Dd(-30+(i*6),0,-17 + (j*3)));
            brick->setVel(Vector3Dd(0,0,0));
            
            if (j==0){
                brick->setCol(Vector3Dd(29.0/255.0, 194.0/255.0, 66.0/255.0));
            } else if (j==1){
                brick->setCol(Vector3Dd(255.0/255.0, 182.0/255.0, 0.0));
            } else if (j==2){
                brick->setCol(Vector3Dd(247.0/255.0, 0.0, 30.0/255.0));
            } else if (j==3){
                brick->setCol(Vector3Dd(166.0/255.0, 36.0/255.0, 152.0/255.0));
            } else if (j==4){
                brick->setCol(Vector3Dd(0.0, 158.0/255.0, 226.0/255.0));
            }
            brick->setF(Vector3Dd(0,-0.98,0));
            brick->setM(1);
            brick->setS(1);
            e.add(brick);
        }
    }
    
    
    
    
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(680,400);
    glutInitWindowPosition(300,300);
    glutCreateWindow("3D Breakout");
    init();
    glutDisplayFunc(displayMe);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyReleased);
    
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutMainLoop();
    
    
    return 0;
}

