//
//  Brick.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Brick_h
#define Brick_h


#include <iostream>
#include <cmath>


#include "Vector3d.h"
#include "Solid.h"
#include "Cube.h"

class Brick: public Cube{
    
public:
    
    Brick():Cube(){};
    Brick(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double s):Cube(p, v, c, f, m, s){};
    Brick(const Brick &c): Cube(c){};
    virtual spSolid clone();
    inline void render();
    inline void update(double dt);
private:
};

spSolid Brick::clone(){
    shared_ptr<Brick> e=make_shared<Brick>(*this);
    //return new Esfera(*this);
    return e;
}


void Brick::render(){
    glPushMatrix();
    glColor3f(col.getX(),col.getY(),col.getZ());
    glTranslatef(pos.getX(),pos.getY(),pos.getZ());
    glScalef(5,.5,2);
    glutSolidCube(s);
    glPopMatrix();
}

//Checar colisiones con las orillas superior e inferior de la pantalla
void Brick::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    //cout<<"Brick-real"<< pos << endl;
    if(pos.getX()>30){
        vel=Vector3Dd(0,0,0);
        pos.setX(pos.getX()-.1);
    }
    if(pos.getX()<-30){
        vel=Vector3Dd(0,0,0);
        pos.setX(pos.getX()+.1);
    }
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}


#endif /* Brick_h */
