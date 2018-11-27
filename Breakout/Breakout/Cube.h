//
//  Cube.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Cube_h
#define Cube_h

#include <iostream>
#include <cmath>


#include "Vector3d.h"
#include "Solid.h"

class Cube: public Solid{
    
public:
    
    Cube();
    Cube(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double s);
    Cube(const Cube &c);
    virtual spSolid clone();
    inline virtual int collision(spSolid s);
    inline double getS();
    inline void setS(double s);
    inline virtual void render();
    inline virtual void update(double dt);
protected:
    double s;
};

Cube:: Cube(): Solid(){
    this->s = .4;
}

Cube:: Cube(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double s): Solid(p, v, c, f, m){
    this->s = s;
}

Cube:: Cube(const Cube &c): Solid(c){
    this->s = c.s;
}

spSolid Cube::clone(){
    shared_ptr<Cube> e=make_shared<Cube>(*this);
    //return new Esfera(*this);
    return e;
}

int Cube::collision(spSolid s){
    return 0;
}

double Cube::getS(){
    return s;
}

void Cube::setS(double s){
    this->s = s;
}



void Cube::render(){
    glPushMatrix();
    glColor3f(col.getX(),col.getY(),col.getZ());
    glTranslatef(pos.getX(),pos.getY(),pos.getZ());
    glutSolidCube(s);
    glPopMatrix();
}

void Cube::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    /* cout<<"Cube-real"<< pos << endl;
     if(pos.getZ()>17.3){
     vel=Vector3Dd(0,0,0);
     pos.setZ(pos.getZ()-.1);
     }
     if(pos.getZ()<-17.3){
     vel=Vector3Dd(0,0,0);
     pos.setZ(pos.getZ()+.1);
     }*/
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}



#endif /* Cube_h */
