//
//  Paddle.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Paddle_h
#define Paddle_h


#include <iostream>
#include <cmath>


#include "Vector3D.h"
#include "Solido.h"
#include "Cubo.h"

class Paleta: public Cubo{
    
public:
    
    Paleta():Cubo(){};
    Paleta(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double s):Cubo(p, v, c, f, m, s){};
    Paleta(const Paleta &c): Cubo(c){};
    virtual spSolido clone();
    inline void render();
    inline void update(double dt);
private:
};

spSolido Paleta::clone(){
    shared_ptr<Paleta> e=make_shared<Paleta>(*this);
    //return new Esfera(*this);
    return e;
}


void Paleta::render(){
    glPushMatrix();
    glColor3f(col.getX(),col.getY(),col.getZ());
    glTranslatef(pos.getX(),pos.getY(),pos.getZ());
    glScalef(2,.5,5);
    glutSolidCube(s);
    glPopMatrix();
}

//Checar colisiones con las orillas superior e inferior de la pantalla
void Paleta::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    //cout<<"Paleta-real"<< pos << endl;
    if(pos.getZ()>17.3){
        vel=Vector3Dd(0,0,0);
        pos.setZ(pos.getZ()-.1);
    }
    if(pos.getZ()<-17.3){
        vel=Vector3Dd(0,0,0);
        pos.setZ(pos.getZ()+.1);
    }
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}


#endif /* Paddle_h */
