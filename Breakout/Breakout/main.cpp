//
//  main.cpp
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/23/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>



// angle for rotating triangle
float angle = 0.0f;
float angle2 = 0.0f;




void renderScene(void)
{
    
    // Clear Color and Depth Buffers
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    
    gluLookAt(    0.0f, 2.0f,  3.0f,
              0.0f, 0.25f,  0.0f,
              0.0f, 10.0f,  0.0f);

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch(key){
        case 'q':
            break;
        case 27:
            exit(0);
            break;
    }
}

void processSpecialKeys(int key, int xx, int yy)
{

    switch (key) {
        case GLUT_KEY_LEFT :
            
            break;
        case GLUT_KEY_RIGHT :
            
            break;
        case GLUT_KEY_UP :
            
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            
            glutPostRedisplay();
            break;
    }
}

void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    gluPerspective(70.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char **argv)
{
    
    // init GLUT and create window
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(720, 720);
    glutCreateWindow("Lighthouse3D - GLUT Tutorial");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}
